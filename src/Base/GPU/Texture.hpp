#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Base {

	enum class TextureInternalFormat
	{
		DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
		DEPTH_STENCIL = GL_DEPTH_STENCIL,
		R = GL_RED,
		RG = GL_RG,
		RGB = GL_RGB,
		RGBA = GL_RGBA,
		R8 = GL_R8,
		R8_SNORM = GL_R8_SNORM,
		R16 = GL_R16,
		R16_SNORM = GL_R16_SNORM,
		RG8 = GL_RG8,
		RG8_SNORM = GL_RG8_SNORM,
		RG16 = GL_RG16,
		RG16_SNORM = GL_RG16_SNORM,
		R3_G3_B2 = GL_R3_G3_B2,
		RGB4 = GL_RGB4,
		RGB5 = GL_RGB5,
		RGB8_SNORM = GL_RGB8_SNORM,
		RGB10 = GL_RGB10,
		RGB12 = GL_RGB12,
		RGB16_SNORM = GL_RGB16_SNORM,
		RGBA2 = GL_RGBA2,
		RGBA4 = GL_RGBA4,
		RGB5_A1 = GL_RGB5_A1,
		RGBA8 = GL_RGBA8,
		RGBA8_SNORM = GL_RGBA8_SNORM,
		RGB10_A2 = GL_RGB10_A2,
		RGB10_A2UI = GL_RGB10_A2UI,
		RGBA12 = GL_RGBA12,
		RGBA16 = GL_RGBA16,
		SRGB8 = GL_SRGB8,
		SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,
		R16F = GL_R16F,
		RG16F = GL_RG16F,
		RGB16F = GL_RGB16F,
		RGBA16F = GL_RGBA16F,
		R32F = GL_R32F,
		RG32F = GL_RG32F,
		RGB32F = GL_RGB32F,
		RGBA32F = GL_RGBA32F,
		R11F_G11F_B10F = GL_R11F_G11F_B10F,
		RGB9_E5 = GL_RGB9_E5,
		R8I = GL_R8I,
		R8UI = GL_R8UI,
		R16I = GL_R16I,
		R16UI = GL_R16UI,
		R32I = GL_R32I,
		R32UI = GL_R32UI,
		RG8I = GL_RG8I,
		RG8UI = GL_RG8UI,
		RG16I = GL_RG16I,
		RG16UI = GL_RG16UI,
		RG32I = GL_RG32I,
		RG32UI = GL_RG32UI,
		RGB8I = GL_RGB8I,
		RGB8UI = GL_RGB8UI,
		RGB16I = GL_RGB16I,
		RGB16UI = GL_RGB16UI,
		RGB32I = GL_RGB32I,
		RGB32UI = GL_RGB32UI,
		RGBA8I = GL_RGBA8I,
		RGBA8UI = GL_RGBA8UI,
		RGBA16I = GL_RGBA16I,
		RGBA16UI = GL_RGBA16UI,
		RGBA32I = GL_RGBA32I,
		RGBA32UI = GL_RGBA32UI,
		COMPRESSED_RED = GL_COMPRESSED_RED,
		COMPRESSED_RG = GL_COMPRESSED_RG,
		COMPRESSED_RGB = GL_COMPRESSED_RGB,
		COMPRESSED_RGBA = GL_COMPRESSED_RGBA,
		COMPRESSED_SRGB = GL_COMPRESSED_SRGB,
		COMPRESSED_SRGB_ALPHA = GL_COMPRESSED_SRGB_ALPHA,
		COMPRESSED_RED_RGTC1 = GL_COMPRESSED_RED_RGTC1,
		COMPRESSED_SIGNED_RED_RGTC1 = GL_COMPRESSED_SIGNED_RED_RGTC1,
		COMPRESSED_RG_RGTC2 = GL_COMPRESSED_RG_RGTC2,
		COMPRESSED_SIGNED_RG_RGTC2 = GL_COMPRESSED_SIGNED_RG_RGTC2,
	};

	enum class TextureFormat
	{
		R = GL_RED,
		RG = GL_RG,
		RGB = GL_RGB,
		BGR = GL_BGR,
		RGBA = GL_RGBA,
		BGRA = GL_BGRA,
		RED_INTEGER = GL_RED_INTEGER,
		RG_INTEGER = GL_RG_INTEGER,
		RGB_INTEGER = GL_RGB_INTEGER,
		BGR_INTEGER = GL_BGR_INTEGER,
		RGBA_INTEGER = GL_RGBA_INTEGER,
		BGRA_INTEGER = GL_BGRA_INTEGER,
		STENCIL_INDEX = GL_STENCIL_INDEX,
		DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
		DEPTH_STENCIL = GL_DEPTH_STENCIL,
	};

	enum class TexturePixelFormat
	{
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
		BYTE = GL_BYTE,
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		SHORT = GL_SHORT,
		UNSIGNED_INT = GL_UNSIGNED_INT,
		INT = GL_INT,
		HALF_FLOAT = GL_HALF_FLOAT,
		FLOAT = GL_FLOAT,
		UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
		UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,
		UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
		UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
		UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
		UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
		UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
		UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
		UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
		UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
		UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
		UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
	};

	enum class MinifyingFilter
	{
		ONLY_NEAREST = GL_NEAREST,
		ONLY_LINEAR = GL_LINEAR,
		NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
	};

	enum class MagnificationFilter
	{
		NEAREST = GL_NEAREST,
		LINEAR = GL_LINEAR
	};

	enum class TextureWrap
	{
		CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		REPEATED = GL_REPEAT,
		MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE
	};

	struct TextureQuality
	{
		MinifyingFilter minFilter;
		MagnificationFilter magFilter;
		TextureWrap twt, tws;

		glm::vec3 borderColor;

		unsigned int ansiotropicFilter = 2;

		TextureQuality()
		{
			this->minFilter = MinifyingFilter::LINEAR_MIPMAP_NEAREST;
			this->magFilter = MagnificationFilter::NEAREST;
			this->twt = TextureWrap::REPEATED;
			this->tws = TextureWrap::REPEATED;
			this->borderColor = {0,0,0};
			this->ansiotropicFilter = 4;
		}

		TextureQuality(const MinifyingFilter minFilter, const MagnificationFilter magFilter, const TextureWrap twt, const TextureWrap tws, const unsigned int ansiotropicFilter, const glm::vec3& borderColor = {0,0,0})
		{
			this->minFilter = minFilter;
			this->magFilter = magFilter;
			this->twt = twt;
			this->tws = tws;
			this->ansiotropicFilter = ansiotropicFilter;
			this->borderColor = borderColor;
		}
	};

	struct TextureInfo
	{
		TextureQuality quality = TextureQuality();

		TextureInternalFormat internalFormat = TextureInternalFormat::RGB;

		TextureFormat format = TextureFormat::RGB;

		TexturePixelFormat pixelFormat = TexturePixelFormat::FLOAT;

		glm::vec<2, int> size = {0, 0};

		void* data = nullptr;

		TextureInfo() = default;

		TextureInfo(void* data, const glm::vec<2, int>& size, const TextureFormat format, const TextureInternalFormat internalFormat, const TexturePixelFormat pixelFormat, const TextureQuality& quality = TextureQuality())
		{
			this->data = data;
			this->format = format;
			this->internalFormat = internalFormat;
			this->pixelFormat = pixelFormat;
			this->size = size;
			this->quality = quality;
		}
	};

	struct ReadableTexture
	{
		unsigned char* image = nullptr;

		TextureFormat format;

		glm::vec<2, int> size;

		std::string path = "";

		~ReadableTexture()
		{
			if(image != nullptr)
			{
				#if DEBUG_LEVEL > 0
				Debug::cout << "[ReadableTexture]: Deleted (" << path << ")";
				Debug::Log();
				#endif

				delete[] image;
			}
		}
	};

	typedef std::shared_ptr<ReadableTexture> ReadableTexturePtr;

	class Texture
	{
		friend class Framebuffer;
		friend class GUI;
	private:
		unsigned int ID;

		TextureInfo info;

		std::string path;
	public:
		Texture();
		~Texture();

		Texture(const std::string& path, const TextureQuality& quality = TextureQuality());
		Texture(const TextureInfo& info);

		bool isValid() const;

		void ActiveTexture(const unsigned int slot) const;

		bool isInBounds(const glm::vec<2, unsigned int>& start, const glm::vec<2, unsigned int>& size) const;
		void Modify(const glm::vec<2, unsigned int>& start, const glm::vec<2, unsigned int>& size, void* data) const;

		TextureInfo GetTextureInfo() const;
	
		std::string GetPath() const;
		void SetPath(const std::string& path);

		static void DisableTextureUnit(const unsigned int slot);
		static unsigned int GetMaxTextureUnits();

		static ReadableTexturePtr OpenTexture(const std::string& path);
	};

	typedef std::shared_ptr<Texture> TexturePtr;
}}
