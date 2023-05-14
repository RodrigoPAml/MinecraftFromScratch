#include <BuildCraft.hpp>
#include "TerrainGenerator.hpp"

namespace BuildCraft {
namespace Core {

    void TerrainGenerator::InsertFace(const glm::vec3& cubePos, FaceType face, const glm::vec2& textureXY)
    {
        glm::vec3 v1;
        glm::vec3 v2;
        glm::vec3 v3;
        glm::vec3 v4;

        glm::vec3 n;

        if(face == FaceType::Bottom)
        {
            v1 = cubePos;
            v2 = cubePos + glm::vec3(0, 0, 1);
            v3 = cubePos + glm::vec3(1, 0, 1);
            v4 = cubePos + glm::vec3(1, 0, 0);

            n = glm::vec3(0.0f, 1.0f, 0.0f);
        }
        else if(face == FaceType::Upper)
        {
            v1 = cubePos + glm::vec3(0, 1, 0);
            v2 = cubePos + glm::vec3(0, 1, 1);
            v3 = cubePos + glm::vec3(1, 1, 1);
            v4 = cubePos + glm::vec3(1, 1, 0);

            n = glm::vec3(0.0f, -1.0f, 0.0f);
        }
        else if(face == FaceType::Right)
        {
            v1 = cubePos + glm::vec3(1, 0, 0);
            v2 = cubePos + glm::vec3(1, 1, 0);
            v3 = cubePos + glm::vec3(1, 1, 1);
            v4 = cubePos + glm::vec3(1, 0, 1);

            n = glm::vec3(1.0f, 0.0f, 0.0f);
        }
        else if(face == FaceType::Left)
        {
            v1 = cubePos;
            v2 = cubePos + glm::vec3(0, 1, 0);
            v3 = cubePos + glm::vec3(0, 1, 1);
            v4 = cubePos + glm::vec3(0, 0, 1);

            n = glm::vec3(-1.0f, 0.0f, 0.0f);
        }
        else if(face == FaceType::Front)
        {
            v1 = cubePos;
            v2 = cubePos + glm::vec3(0, 1, 0);
            v3 = cubePos + glm::vec3(1, 1, 0);
            v4 = cubePos + glm::vec3(1, 0, 0);

            n = glm::vec3(0.0f, 0.0f, 1.0f);
        }
        else if(face == FaceType::Back)
        {
            v1 = cubePos + glm::vec3(0, 0, 1);
            v2 = cubePos + glm::vec3(0, 1, 1);
            v3 = cubePos + glm::vec3(1, 1, 1);
            v4 = cubePos + glm::vec3(1, 0, 1);

            n = glm::vec3(0.0f, 0.0f, -1.0f);
        }
            
        float uvStartX = ((textureXY.x) * (1.0f/(BLOCK_ATLAS_X))) + 1/512.0f;
        float uvEndX = (textureXY.x+1) * (1.0f/(BLOCK_ATLAS_X)) - 1/512.0f;

        float uvStartY = ((textureXY.y)* (1.0f/(BLOCK_ATLAS_Y))) + 2/256.0f;
        float uvEndY =   ((textureXY.y +1) * (1.0f/(BLOCK_ATLAS_Y))) - 1/256.0f;

        glm::vec2 uv1 = (glm::vec2(uvStartX, uvStartY)); 
        glm::vec2 uv2 = (glm::vec2(uvStartX, uvEndY));
        glm::vec2 uv3 = (glm::vec2(uvEndX, uvEndY));
        glm::vec2 uv4 = (glm::vec2(uvEndX, uvStartY));

        BlockVertex b1 = BlockVertex(v1, n, uv1);
        BlockVertex b2 = BlockVertex(v2, n, uv2);
        BlockVertex b3 = BlockVertex(v3, n, uv3);
        BlockVertex b4 = BlockVertex(v4, n, uv4);

        int i1 = this->vertices.size();
        this->indices.push_back(i1);
        this->vertices.push_back(b1);

        int i2 = this->vertices.size();
        indices.push_back(i2);
        this->vertices.push_back(b2);
            
        int i3 = this->vertices.size();
        indices.push_back(i3);
        this->vertices.push_back(b3);

        indices.push_back(i3);

        int i4 = this->vertices.size();
        indices.push_back(i4);
        this->vertices.push_back(b4);

        indices.push_back(i1);
    }

    void TerrainGenerator::InsertTree(ChunkPtr chunk, int blockx, int blocky, int blockz)
    {
        int top = 3 + rand() % 3;

        for(int y = 0; y <= top; y++)
        {
            chunk->AddBlock(blockx, blocky+y, blockz, 28, 3);
        }

        for(int x = -3; x <= 3; x++)
        {
            for(int z = -3; z <= 3; z++)
            {
                for (int y = 0; y <= 3; y++)
                {
                    if(!(rand()%4 == 1))
                        chunk->AddBlock(blockx + x, blocky+ top + y, blockz + z, 26, 7);
                }
            }
        }
    }
     
    unsigned int TerrainGenerator::CalculateIndex(unsigned int x, unsigned int y, unsigned int z)
	{
        return x * CHUNK_Y * CHUNK_Z + y * CHUNK_Z + z;
	}

    void TerrainGenerator::UpdateChunk(ChunkPtr chunk)
    {
        for(int x = 0; x < CHUNK_X; x++)
        {
            for(int y = 0; y < CHUNK_Y; y++)
            {
                for(int z = 0; z < CHUNK_Z; z++)
                {
                    Block& block = chunk->blocks[TerrainGenerator::CalculateIndex(x, y, z)];
                    block.SetVisible(false);

                    if (Block::isFlower(block))
                    {
                        this->InsertFace({ x, y, z }, (FaceType)(2 + rand() % 4), block.GetUV());
                        block.SetVisible(true);
                        continue;
                    }

                    if(Block::isEmpty(block)) // vazio
                    {
                        continue;
                    }

                    bool hasBlockUp = (y + 1 < CHUNK_Y) && (!Block::isEmpty(chunk->blocks[TerrainGenerator::CalculateIndex(x, y + 1, z)]));
                    bool hasBlockDown = (y - 1 >= 0) && (!Block::isEmpty(chunk->blocks[TerrainGenerator::CalculateIndex(x, y - 1, z)]));

                    bool hasBlockLeft = (x - 1 >= 0) && (!Block::isEmpty(chunk->blocks[TerrainGenerator::CalculateIndex(x - 1, y, z)]));
                    bool hasBlockRight = (x + 1 < CHUNK_X) && (!Block::isEmpty(chunk->blocks[TerrainGenerator::CalculateIndex(x + 1, y, z)]));

                    bool hasBlockBack = (z - 1 >= 0) && (!Block::isEmpty(chunk->blocks[TerrainGenerator::CalculateIndex(x, y, z - 1)]));
                    bool hasBlockFront = (z + 1 < CHUNK_Z) && (!Block::isEmpty(chunk->blocks[TerrainGenerator::CalculateIndex(x, y, z + 1)]));

                    if(!hasBlockUp)
                    {
                        this->InsertFace({ x, y, z }, FaceType::Upper, block.GetUV());
                        block.SetVisible(true);
                    }
                    if(!hasBlockDown)
                    {
                        this->InsertFace({ x, y, z }, FaceType::Bottom, block.GetUV());
                        block.SetVisible(true);
                    }
                    if(!hasBlockLeft)
                    {
                        this->InsertFace({ x, y, z }, FaceType::Left, block.GetUV());
                        block.SetVisible(true);
                    }
                    if(!hasBlockRight)
                    {
                        this->InsertFace({ x, y, z }, FaceType::Right, block.GetUV());
                        block.SetVisible(true);
                    }
                    if(!hasBlockBack)
                    {
                        this->InsertFace({ x, y, z }, FaceType::Front, block.GetUV());
                        block.SetVisible(true);
                    }
                    if(!hasBlockFront)
                    {
                        this->InsertFace({ x, y, z }, FaceType::Back, block.GetUV());
                        block.SetVisible(true);
                    }
                }
            }
        }

        using namespace BuildCraft::Base;

        VertexDescriptor descriptor;

        VertexBufferDescriptor buffer1;
        buffer1.bufferLayout.push_back(VertexElementDescriptor(VertexType::FLOAT, 3));
        buffer1.bufferLayout.push_back(VertexElementDescriptor(VertexType::FLOAT, 3));
        buffer1.bufferLayout.push_back(VertexElementDescriptor(VertexType::FLOAT, 2));
        buffer1.data = vertices.data();

        descriptor.buffers.push_back(buffer1);
        descriptor.verticesCount = vertices.size();

        IndexedVertexDescriptor idescriptor;
        idescriptor.indices = indices.data();
        idescriptor.count = indices.size();

        chunk->chunkVertex = VertexPtr(new Vertex(descriptor, idescriptor));

        this->indices.clear();
        this->vertices.clear();
    }

    ChunkPtr TerrainGenerator::GenerateChunk(int x, int z, bool generateComplete)
	{
        ChunkPtr chunk = ChunkPtr(new Chunk({x, z}));
        chunk->isCompletedGenerated = generateComplete;

        for(int block_x = 0; block_x < CHUNK_X; block_x++)
        {
            for(int block_z = 0; block_z < CHUNK_Z; block_z++)
            {
                // Generate Ground
                if(generateComplete)
                {
                    for(int block_y = 0; block_y < CHUNK_GROUND; block_y++)
                    {
                        chunk->AddBlock(block_x, block_y, block_z, 15, 19); // Pedra
                    }
                }

                // Generate Terrain
                float y = noiser.GetNoise((CHUNK_X*x) + block_x, (CHUNK_Z*z) + block_z);
                float vy = noiser2.GetNoise(y * 100, (CHUNK_X * x) + block_x * (CHUNK_Z * z) + block_z);
                float vx = noiser2.GetNoise(y * 10000, 1000*(CHUNK_X * x) + block_x * (CHUNK_Z * z) + block_z);

                bool HavePlant = vy > 0.2f;
                bool HaveTree = vx > 0.4f;

                y = (y + 1.0f)/2.0f;

                chunk->AddBlock(block_x, CHUNK_GROUND + y*(CHUNK_TERRAIN - CHUNK_GROUND), block_z, 31, 2);

                if(HavePlant)
                    chunk->AddBlock(block_x, CHUNK_GROUND + y * (CHUNK_TERRAIN - CHUNK_GROUND)+1, block_z, 29, 25);
                if(HaveTree)
                    InsertTree(chunk, block_x, CHUNK_GROUND + y * (CHUNK_TERRAIN - CHUNK_GROUND) + 1, block_z);

                int start = CHUNK_GROUND;

                if(!generateComplete)
                    start = CHUNK_GROUND + (y * (CHUNK_TERRAIN - CHUNK_GROUND)) - 5;

                for(int block_y = start; block_y < CHUNK_GROUND + (y*(CHUNK_TERRAIN - CHUNK_GROUND))-1; block_y++)
                {     
                    chunk->AddBlock(block_x, block_y, block_z, 30, 19);
                }

                // Generate Water
                for(int block_y = start; block_y < CHUNK_Y; block_y++)
                {
                    int index = TerrainGenerator::CalculateIndex(block_x, block_y, block_z);

                    Block block = chunk->blocks[index];

                    if(!Block::isEmpty(block))
                    {
                        continue;
                    }
                    else if(block_y < 90)
                    {
                        chunk->AddBlock(block_x, block_y, block_z, 15, 20);
                    }
                }
            }
        }

        this->UpdateChunk(chunk);

        return chunk;
    }
}}