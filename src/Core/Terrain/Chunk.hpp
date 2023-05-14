#pragma once
#include <BuildCraft.hpp>

#define CHUNK_X 16
#define CHUNK_Z 16
#define CHUNK_Y 256

#define CHUNK_GROUND 64
#define CHUNK_TERRAIN 128
#define CHUNK_SKY 256

#define BLOCK_ATLAS_X 32.0f
#define BLOCK_ATLAS_Y 16.0f

namespace BuildCraft {
namespace Core {

    /// <summary>
    /// Represents a chunk of the terrain
    /// </summary>
    class Chunk
    {
        friend class TerrainGenerator;
    private:
        // Chunk blocks
        Block* blocks = nullptr;

        // Chunk height map
        unsigned int* heights = nullptr;
        unsigned int maxHeight = 0;

        // Position of the chunk in the map
        glm::vec<2, int> id;

        // Vertex memory GPU
        Base::VertexPtr chunkVertex = nullptr;

        // If its completed generated, because distant things have less details
        bool isCompletedGenerated = false;
    public:
        Chunk(glm::vec<2, int> id);
        ~Chunk();

        // GPU memory mesh info
        Base::VertexPtr GetVertex() const;

        // Identifier
        glm::vec<2, int> GetId() const;
        void SetId(glm::vec<2, int> id);

        // If the chunks is completed generated
        bool GetIsCompletedGenerated() const;

        // Add a block into the chunk
        void AddBlock(unsigned int x, unsigned int y, unsigned int z, int u, int v);
        
        // Max height info
        void UpdateMaxHeightAt(unsigned int x, unsigned int z);
        int GetMaxHeightAt(unsigned int x, unsigned z);
        int GetMaxHeight();

        /// Bouding box info
        glm::vec3 GetBoundingBoxMin();
        glm::vec3 GetBoundingBoxMax();
    };

    typedef std::shared_ptr<Chunk> ChunkPtr;
}}

