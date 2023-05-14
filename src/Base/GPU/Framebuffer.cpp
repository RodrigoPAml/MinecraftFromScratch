#include <BuildCraft.hpp>
#include "Framebuffer.hpp"

namespace BuildCraft {
namespace Base {

	unsigned int Framebuffer::ClearModeSum = (unsigned int)ClearMode::COLOR;

	Framebuffer::Framebuffer()
	{
		this->fbID = 0;
		this->rboID = 0;
	}

	Framebuffer::Framebuffer(const FramebufferConfig& config)
	{
		this->fbID = 0;
		this->rboID = 0;

		if(config.textureAttachments.empty())
		{
			return;
		}

		for(const TexturePtr texture : config.textureAttachments)
		{
			if(!texture->isValid())
			{
				return;
			}
		}

		glGenFramebuffers(1, &this->fbID);
		glBindFramebuffer(GL_FRAMEBUFFER, this->fbID);

		GLenum attach = GL_COLOR_ATTACHMENT0;

		unsigned int* attachments = new unsigned int[config.textureAttachments.size()]();

		for(auto i = 0; i < config.textureAttachments.size(); i++)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, attach, GL_TEXTURE_2D, config.textureAttachments[i]->ID, 0);

			attachments[i] = attach;

			attach++;

			this->textures.push_back(config.textureAttachments[i]);
		}

		if(config.depthAttachment.texture != nullptr)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, config.depthAttachment.texture->ID, 0);
		}

		if(config.textureAttachments.size() > 0)
		{
			glDrawBuffers(config.textureAttachments.size(), attachments);
		}

		delete[] attachments;

		if(config.renderBufferAttachment.type == RenderBufferType::DEPTH_STENCIL_ATTACHMENT)
		{
			glGenRenderbuffers(1, &this->rboID);
			glBindRenderbuffer(GL_RENDERBUFFER, this->rboID);
			glRenderbufferStorage(GL_RENDERBUFFER, (GLenum)config.renderBufferAttachment.format, config.renderBufferAttachment.size.x, config.renderBufferAttachment.size.y);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rboID);
		}
		else if(config.renderBufferAttachment.type == RenderBufferType::DEPTH_ATTACHMENT)
		{
			glGenRenderbuffers(1, &this->rboID);
			glBindRenderbuffer(GL_RENDERBUFFER, this->rboID);
			glRenderbufferStorage(GL_RENDERBUFFER, (GLenum)config.renderBufferAttachment.format, config.renderBufferAttachment.size.x, config.renderBufferAttachment.size.y);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->rboID);
		}
		else if(config.renderBufferAttachment.type == RenderBufferType::STENCIL_ATTACHEMT)
		{
			glGenRenderbuffers(1, &this->rboID);
			glBindRenderbuffer(GL_RENDERBUFFER, this->rboID);
			glRenderbufferStorage(GL_RENDERBUFFER, (GLenum)config.renderBufferAttachment.format, config.renderBufferAttachment.size.x, config.renderBufferAttachment.size.y);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rboID);
		}

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			#if DEBUG_LEVEL > 0
			Debug::cout << "[Framebuffer]: Failed to create (FbID = " << this->fbID << ", RboID = " << this->rboID << ")";
			Debug::Log();
			#endif

			glDeleteFramebuffers(1, &this->fbID);
			glDeleteRenderbuffers(1, &this->rboID);

			this->fbID = 0;
			this->rboID = 0;
			this->textures.clear();
		}

		#if DEBUG_LEVEL > 0
		Debug::cout << "[Framebuffer]: Created (FbID = " << this->fbID << ", RboID = " << this->rboID << ")";
		Debug::Log();
		#endif

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	Framebuffer::~Framebuffer()
	{
		if(this->isValid())
		{
			#if DEBUG_LEVEL > 0
			Debug::cout << "[Framebuffer]: Deleted (FbID = " << this->fbID << ", RboID = " << this->rboID << ")";
			Debug::Log();
			#endif

			glDeleteFramebuffers(1, &this->fbID);

			if(this->rboID != 0)
			{
				glDeleteRenderbuffers(1, &this->rboID);
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			this->textures.clear();
		}
	}

	bool Framebuffer::isValid() const
	{
		return(this->fbID != 0);
	}

	void Framebuffer::Active() const
	{
		if(!this->isValid()) return;

		glBindFramebuffer(GL_FRAMEBUFFER, this->fbID);

		#if DEBUG_LEVEL > 1
		Debug::cout << "[Framebuffer]: Activated (FbID = " << this->fbID << ", RboID = " << this->rboID << ")";
		Debug::Log();
		#endif
	}

	unsigned int Framebuffer::GetNumberOfTexturesAttachments() const
	{
		return this->textures.size();
	}

	TexturePtr Framebuffer::GetTextureAt(const unsigned int index) const
	{
		if(index < 0 || index > this->textures.size())
		{
			return nullptr;
		}

		return this->textures[index];
	}

	void Framebuffer::ActiveDefault()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void Framebuffer::SwitchViewPort(const glm::vec2& pos, const glm::vec2& size)
	{
		glViewport(pos.x, pos.y, size.x, size.y);
	}

	void Framebuffer::SetClearModes(const std::set<ClearMode>& clearModes)
	{
		if(clearModes.empty()) return;

		Framebuffer::ClearModeSum = 0;

		for(ClearMode mode : clearModes)
		{
			Framebuffer::ClearModeSum |= (unsigned int)mode;
		}
	}

	void Framebuffer::ClearCurrentFrameBuffer(const glm::vec4& color)
	{
		glClearColor(color.x, color.y, color.z, color.w);

		glClear((GLbitfield)Framebuffer::ClearModeSum);
	}
}}