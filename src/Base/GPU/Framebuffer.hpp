#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Base {

	enum class ClearMode
	{
		DEPTH = GL_DEPTH_BUFFER_BIT,
		STENCIL = GL_STENCIL_BUFFER_BIT,
		COLOR = GL_COLOR_BUFFER_BIT,
	};

	enum class RenderBufferType
	{
		DONT_USE,
		DEPTH_ATTACHMENT,
		STENCIL_ATTACHEMT,
		DEPTH_STENCIL_ATTACHMENT
	};

	enum class RenderBufferFormat
	{
		DEPTH_COMPONENT16 = GL_DEPTH_COMPONENT16,
		DEPTH_COMPONENT24 = GL_DEPTH_COMPONENT24,
		DEPTH_COMPONENT32F = GL_DEPTH_COMPONENT32F,
		DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8,
		DEPTH32F_STENCIL8 = GL_DEPTH32F_STENCIL8,
		STENCIL_INDEX8 = GL_STENCIL_INDEX8,
	};

	struct RenderBufferAttachment
	{
		RenderBufferType type = RenderBufferType::DONT_USE;

		RenderBufferFormat format = RenderBufferFormat::DEPTH32F_STENCIL8;

		glm::vec2 size = {0,0};

		RenderBufferAttachment() = default;

		RenderBufferAttachment(const RenderBufferType type, const RenderBufferFormat format, const glm::vec2& size)
		{
			this->type = type;
			this->format = format;
			this->size = size;
		}
	};

	struct DepthAttachment
	{
		TexturePtr texture = nullptr;

		DepthAttachment() = default;

		DepthAttachment(const TexturePtr texture)
		{
			this->texture = texture;
		}
	};

	struct FramebufferConfig
	{
		std::vector<TexturePtr> textureAttachments;

		RenderBufferAttachment renderBufferAttachment;

		DepthAttachment depthAttachment;

		FramebufferConfig() = default;

		FramebufferConfig(const std::vector<TexturePtr>& textureAttachments, const RenderBufferAttachment renderBufferAttachment, const DepthAttachment depthAttachment)
		{
			this->textureAttachments = textureAttachments;
			this->renderBufferAttachment = renderBufferAttachment;
			this->depthAttachment = depthAttachment;
		}
	};

	class Framebuffer
	{
	private:
		static unsigned int ClearModeSum;

		unsigned int fbID, rboID;

		std::vector<TexturePtr> textures;
	public:
		Framebuffer();
		Framebuffer(const FramebufferConfig& config);
		~Framebuffer();

		bool isValid() const;

		void Active() const;

		unsigned int GetNumberOfTexturesAttachments() const;

		TexturePtr GetTextureAt(const unsigned int index) const;

		static void ActiveDefault();
		static void SwitchViewPort(const glm::vec2& pos, const glm::vec2& size);
		static void SetClearModes(const std::set<ClearMode>& clearModes);
		static void ClearCurrentFrameBuffer(const glm::vec4& color);
	};

	typedef std::shared_ptr<Framebuffer> FramebufferPtr;
}}
