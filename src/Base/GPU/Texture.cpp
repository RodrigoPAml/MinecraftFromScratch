#include <BuildCraft.hpp>
#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace BuildCraft {
namespace Base {

	Texture::Texture()
	{
		this->ID = 0;
	}

	Texture::~Texture()
	{
		if(this->isValid())
		{
			glDeleteTextures(1, &this->ID);

			#if DEBUG_LEVEL > 0
			Debug::cout << "[Texture]: Deleted (ID = " << this->ID << ')';
			Debug::Log();
			#endif
		}
	}

	Texture::Texture(const std::string& path, const TextureQuality& quality)
	{
		stbi_set_flip_vertically_on_load(true);

		this->ID = 0;
		this->path = path;

		int nrComponents;
		GLenum format;

		unsigned char* data = stbi_load(path.c_str(), &this->info.size.x, &this->info.size.y, &nrComponents, 0);

		if(data)
		{
			if(nrComponents == 1)
			{
				this->info.internalFormat = TextureInternalFormat::R;
				this->info.format = TextureFormat::R;
			}
			else if(nrComponents == 3)
			{
				this->info.internalFormat = TextureInternalFormat::RGB;
				this->info.format = TextureFormat::RGB;
			}
			else if(nrComponents == 4)
			{
				this->info.internalFormat = TextureInternalFormat::RGBA;
				this->info.format = TextureFormat::RGBA;
			}
			else
			{
				stbi_image_free(data);

				this->ID = 0;
				this->info = TextureInfo();

				#if DEBUG_LEVEL > 0
				Debug::cout << "[Texture]: Invalid format: " << path;
				Debug::Log();
				#endif

				return;
			}

			this->info.pixelFormat = TexturePixelFormat::UNSIGNED_BYTE;

			glGenTextures(1, &this->ID);
			glBindTexture(GL_TEXTURE_2D, this->ID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)quality.tws);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)quality.twt);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)quality.minFilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)quality.magFilter);

			if(quality.tws == TextureWrap::CLAMP_TO_BORDER || quality.twt == TextureWrap::CLAMP_TO_EDGE)
			{
				float color[] = {quality.borderColor.x, quality.borderColor.y, quality.borderColor.z, 1.0f};
				glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
			}

			if(quality.ansiotropicFilter > 0 && quality.minFilter != MinifyingFilter::ONLY_LINEAR && quality.minFilter != MinifyingFilter::ONLY_NEAREST && glfwExtensionSupported("GL_ARB_texture_filter_anisotropic"))
			{
				GLfloat largest_supported_anisotropy;

				glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);

				if(largest_supported_anisotropy >= quality.ansiotropicFilter)
				{
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, quality.ansiotropicFilter);
				}
				else
				{
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest_supported_anisotropy);
				}
			}

			glTexImage2D(GL_TEXTURE_2D, 0, (GLint)this->info.format, this->info.size.x, this->info.size.y, 0, (GLint)this->info.format, GL_UNSIGNED_BYTE, data);

			if(quality.minFilter != MinifyingFilter::ONLY_LINEAR && quality.minFilter != MinifyingFilter::ONLY_NEAREST) glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);

			this->info.quality = quality;

			#if DEBUG_LEVEL > 0
			Debug::cout << "[Texture]: Created (ID = " << this->ID << ") with " << nrComponents << " components";
			Debug::Log();
			#endif
		}
		else
		{
			this->ID = 0;
			this->info = TextureInfo();

			#if DEBUG_LEVEL > 0
			Debug::cout << "[Texture]: Failed to open " << path;
			Debug::Log();
			#endif
		}
	}

	Texture::Texture(const TextureInfo& info)
	{
		stbi_set_flip_vertically_on_load(true);

		this->ID = 0;
		this->info = info;

		glGenTextures(1, &this->ID);
		glBindTexture(GL_TEXTURE_2D, this->ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)info.quality.tws);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)info.quality.twt);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)info.quality.minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)info.quality.magFilter);

		if(info.quality.tws == TextureWrap::CLAMP_TO_BORDER || info.quality.twt == TextureWrap::CLAMP_TO_EDGE)
		{
			float color[] = {info.quality.borderColor.x, info.quality.borderColor.y, info.quality.borderColor.z, 1.0f};
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
		}

		if(info.quality.ansiotropicFilter > 0 && info.quality.minFilter != MinifyingFilter::ONLY_LINEAR && info.quality.minFilter != MinifyingFilter::ONLY_NEAREST && glfwExtensionSupported("GL_ARB_texture_filter_anisotropic"))
		{
			GLfloat largest_supported_anisotropy;

			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);

			if(largest_supported_anisotropy >= info.quality.ansiotropicFilter)
			{
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, info.quality.ansiotropicFilter);
			}
			else
			{
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest_supported_anisotropy);
			}
		}

		glTexImage2D(GL_TEXTURE_2D, 0, (GLenum)info.internalFormat, info.size.x, info.size.y, 0, (GLenum)info.format, (GLenum)info.pixelFormat, info.data);

		if(info.quality.minFilter != MinifyingFilter::ONLY_LINEAR && info.quality.minFilter != MinifyingFilter::ONLY_NEAREST) glGenerateMipmap(GL_TEXTURE_2D);

		#if DEBUG_LEVEL > 0
		Debug::cout << "[Texture]: Created (ID = " << this->ID << ")";
		Debug::Log();
		#endif
	}


	bool Texture::isValid() const
	{
		return this->ID != 0;
	}

	void Texture::ActiveTexture(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, this->ID);

		#if DEBUG_LEVEL > 1
		Debug::cout << "[Texture]: Actived (ID = " << this->ID << ") on slot " << slot;
		Debug::Log();
		#endif
	}

	bool Texture::isInBounds(const glm::vec<2, unsigned int>& start, const glm::vec<2, unsigned int>& size) const
	{
		if(start.x > this->info.size.x || start.y > this->info.size.y || start.x < 0 || start.y < 0)
		{
			return false;
		}

		if(start.x + size.x > this->info.size.x || start.y + size.y > this->info.size.y || start.x + size.x < 0 || start.y + size.y < 0)
		{
			return false;
		}

		if(start.x >= size.x || start.y >= size.y)
		{
			return false;
		}

		return true;
	}

	void Texture::Modify(const glm::vec<2, unsigned int>& start, const glm::vec<2, unsigned int>& size, void* data) const
	{
		glTexSubImage2D(GL_TEXTURE_2D, 0, start.x, start.y, size.x, size.y, (GLenum)this->info.format, GL_UNSIGNED_BYTE, data);
	}

	TextureInfo Texture::GetTextureInfo() const
	{
		return this->info;
	}

	std::string Texture::GetPath() const
	{
		return this->path;
	}

	void Texture::SetPath(const std::string& path)
	{
		this->path = path;
	}

	void Texture::DisableTextureUnit(const unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glDisable(GL_TEXTURE_2D);
	}

	unsigned int Texture::GetMaxTextureUnits()
	{
		int max = 0;

		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max);

		return (unsigned int)max;
	}

	ReadableTexturePtr Texture::OpenTexture(const std::string& path)
	{
		ReadableTexturePtr te = ReadableTexturePtr(new ReadableTexture());

		int nrComponents = 0;
		unsigned char* data = stbi_load(path.c_str(), &te->size.x, &te->size.y, &nrComponents, 0);

		if(data)
		{
			te->image = data;

			#if DEBUG_LEVEL > 0
			Debug::cout << "[ReadableTexture]: Created (" << path << ")";
			Debug::Log();
			#endif
		}

		if(nrComponents == 1)
		{
			te->format = TextureFormat::R;
		}
		else if(nrComponents == 3)
		{
			te->format = TextureFormat::RGB;
		}
		else if(nrComponents == 4)
		{
			te->format = TextureFormat::RGBA;
		}

		te->path = path;

		return te;
	}
}}
