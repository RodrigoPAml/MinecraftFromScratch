#include <BuildCraft.hpp>
#include "Chunk.hpp"

namespace BuildCraft {
namespace Core
{
	Chunk::Chunk(glm::vec<2, int> id)
	{
		this->id = id;
		this->blocks = new Block[CHUNK_X * CHUNK_Y * CHUNK_Z];
		this->heights = new unsigned int[CHUNK_X * CHUNK_Z];

		for (int i = 0; i < CHUNK_X * CHUNK_Z; i++)
		{
			this->heights[i] = 0;
		}
	}

	Chunk::~Chunk()
	{
		if(this->blocks != nullptr)
		{
			delete[] this->blocks;
		}

		if(this->heights != nullptr)
		{
			delete[] this->heights;
		}
	}

	Base::VertexPtr Chunk::GetVertex() const
	{
		return this->chunkVertex;
	}

	glm::vec<2, int> Chunk::GetId() const
	{
		return this->id;
	}

	void Chunk::SetId(glm::vec<2, int> id)
	{
		this->id = id;
	}

	bool Chunk::GetIsCompletedGenerated() const
	{
		return this->isCompletedGenerated;
	}

	void Chunk::AddBlock(unsigned int x, unsigned int y, unsigned int z, int u, int v)
	{
		if (x > CHUNK_X-1 ||
			y > CHUNK_Y-1 ||
			z > CHUNK_Z-1)
		{
			return;
		}

		unsigned int index = TerrainGenerator::CalculateIndex(x, y, z);
		unsigned int index2 = x + (CHUNK_Z * z);

		this->blocks[index] = Block(v, u);

		if(this->heights[index2] < y)
		{
			this->heights[index2] = y;
		}

		if(maxHeight < y)
		{
			maxHeight = y;
		}
	}

	void Chunk::UpdateMaxHeightAt(unsigned int x, unsigned int z)
	{
		unsigned int index2 = x + (CHUNK_Z * z);
		this->heights[index2] = 0;

		for(int y = CHUNK_Y-1; y > 0; y--)
		{
			unsigned int index = TerrainGenerator::CalculateIndex(x, y, z);

			if(!Block::isEmpty(blocks[index]))
			{
				this->heights[index2] = y;
				break;
			}
		}

	}

	int Chunk::GetMaxHeightAt(unsigned int x, unsigned z)
	{
		if (x > CHUNK_X - 1 ||
			z > CHUNK_Z - 1)
		{
			return 0;
		}

		return this->heights[x + (CHUNK_Z * z)];
	}

	int Chunk::GetMaxHeight()
	{
		return this->maxHeight;
	}

	glm::vec3 Chunk::GetBoundingBoxMin()
	{
		glm::vec3 bounds;

		bounds.x = this->id.x * CHUNK_X;
		bounds.z = this->id.y * CHUNK_Z;
		bounds.y = 1;

		return bounds;
	}

	glm::vec3 Chunk::GetBoundingBoxMax()
	{
		glm::vec3 bounds;

		bounds.x = (this->id.x + 1) * CHUNK_X;
		bounds.z = (this->id.y + 1) * CHUNK_Z;

		bounds.y = this->GetMaxHeight();

		return bounds;
	}
}}