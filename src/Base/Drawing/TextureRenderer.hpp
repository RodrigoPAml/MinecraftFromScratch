#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Base {

	class TextureRenderer
	{
	private:
		static ShaderPtr shader;

		static VertexPtr mesh;

		static bool initiliazed_;
	public:
		static void Initialize();
		static bool IsInitialized();
		static void Release();

		static void Draw(const TexturePtr texture, const glm::vec2& position, const glm::vec2& size, const float rotation);
	};
}}