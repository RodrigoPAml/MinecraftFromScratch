#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Core
{
	/// <summary>
	/// This class renders the terrain (chunk by chunk)
	/// </summary>
	class TerrainRenderer
	{
	private:
		// The shader used to draw
		Base::ShaderPtr shader = nullptr;

		// Texture atlas
		Base::TexturePtr texture = nullptr;
	public:
		TerrainRenderer();

		// Activate and setup variables of the shader
		void SetupShader();

		// Draw call to render chunk
		void RenderChunk(ChunkPtr chunk);
	};
}}