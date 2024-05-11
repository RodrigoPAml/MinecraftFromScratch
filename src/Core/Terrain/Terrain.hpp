#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Core {

	/// <summary>
	/// Class that manage the terrain
	/// </summary>
	class Terrain
	{
	private:
		// Current size of the terrain that appears in the scene (Size X Size)
		int size;

		// Players positions
		glm::vec3 playerPosition;

		// Chunks saved in memory with hash table for fast access
		std::unordered_map<glm::vec<2, int>, ChunkPtr, Vec2Hash> chunks;

		// Terrain generator
		TerrainGenerator gen;
		
		// Terrain renderer
		TerrainRenderer renderer;

		// Ray box tracer
		RayBox rayBox;

		// Interval that the terrains update in seconds
		float timeUpdate = 1;
		
		// The current block been holded
		glm::vec2 currBlock = { 15, 19 };

		// Erase block mode  enabled
		bool eraseMode = false;

		// Walk mode enabled
		bool walkMode = false;

		// Delay to put block or erase it
		bool blockDelay = false;

		// Update terrain
		void UpdateTerrain(int maxCreateIterations, int maxDeleteIterations);

		// Calculate mouse and block colission to show red box 
		void BlockCollision(ChunkPtr chunk);
	public:
		// Size of the terrain (SIZE X SIZE)
		Terrain(int size);

		// Get the height were the player is
		float GetHeight(glm::vec3 playerPos);

		// Draw the terrain
		void DrawTerrain(int maxCreateIterations, int maxDeleteIterations);

		/// Modes
		bool& GetWalkMode();
		bool& GetEraseMode();
	
		// Sets current block from position of the atlas
		void SetCurrentBlock(glm::vec2 block);
	};
}}