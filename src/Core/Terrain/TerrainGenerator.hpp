#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Core
{

	/// <summary>
	/// Generates terrain
	/// </summary>
	class TerrainGenerator
	{
	private: 
		// Terrain info in memory
		std::vector<unsigned int> indices;
		std::vector<BlockVertex> vertices;

		// Noises to create terrain
		PerlinNoise noiser;
		PerlinNoise noiser2;

		// Insert faces into the scene
		void InsertFace(const glm::vec3& cubePos, FaceType face, const glm::vec2& textureXY);
		// Insert a tree into the scene
		void InsertTree(ChunkPtr chunk, int blockx, int blocky, int blockz);
	public:
		// Index to access block fast in memory
		static unsigned int CalculateIndex(unsigned int x, unsigned int y, unsigned int z);

		// Update a chunk
		void UpdateChunk(ChunkPtr chunk);

		// Generate new chunks
		ChunkPtr GenerateChunk(int x, int z, bool generateComplete);
	};
}}
