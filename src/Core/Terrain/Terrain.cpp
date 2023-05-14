#include "BuildCraft.hpp"
#include "Terrain.hpp"

namespace BuildCraft {
namespace Core {

	void Terrain::UpdateTerrain(int maxCreateIterations, int maxDeleteIterations)
	{
		int chunkX = this->playerPosition.x / CHUNK_X;
		int chunkZ = this->playerPosition.z / CHUNK_Z;

		int initialChunkX = chunkX - size;
		int initialChunkZ = chunkZ - size;

		int endChunkX = chunkX + size;
		int endChunkZ = chunkZ + size;

		// Verifica terrenos que podem ser deletados
		int maxDeleteIter = maxDeleteIterations;

		for (auto it = std::begin(this->chunks); it != std::end(this->chunks);)
		{
			glm::vec<2, int> pos = it->first;

			bool isInside = (pos.x >= initialChunkX && pos.x <= endChunkX && pos.y >= initialChunkZ && pos.y <= endChunkZ);

			if (!isInside)
			{
				it = this->chunks.erase(it);
			}
			else
			{
				it++;
			}

			if (maxDeleteIter == 0)
			{
				break;
			}

			maxDeleteIter--;
		}

		int maxGenerate = maxCreateIterations;

		for (int x = initialChunkX; x <= endChunkX; x++)
		{
			for (int z = initialChunkZ; z <= endChunkZ; z++)
			{
				glm::vec<2, int> xz = glm::vec<2, int>(x, z);

				std::unordered_map<glm::vec<2, int>, ChunkPtr, Vec2Hash>::iterator it = this->chunks.find(xz);

				bool isChunkNextToPlayer = std::abs(chunkX - x) < 2 && std::abs(chunkZ - z) < 2;

				if (it == this->chunks.end()) // Nao encontrou chunk entao cria
				{
					glm::vec<2, int> chunkID = glm::vec<2, int>(x, z);

					if (maxGenerate >= 0)
					{
						this->chunks[chunkID] = gen.GenerateChunk(x, z, isChunkNextToPlayer);
					}

					maxGenerate--;
				}
				else
				{
					if (isChunkNextToPlayer != it->second->GetIsCompletedGenerated()) // Chunk pode ter seu nivel de detalhe aumenta/decrementado
					{
						this->chunks.erase(it);

						glm::vec<2, int> chunkID = glm::vec<2, int>(x, z);

						this->chunks[chunkID] = gen.GenerateChunk(x, z, isChunkNextToPlayer);
					}
				}
			}
		}
	}

	void Terrain::BlockCollision(ChunkPtr chunk)
	{
		glm::vec3 boundingBox[2] = { chunk->GetBoundingBoxMin(), chunk->GetBoundingBoxMax() };
		glm::vec3 centerPos = (boundingBox[0] + boundingBox[1]) / 2.0f;
		centerPos.y = this->GetHeight(this->playerPosition);

		float distancia_novo = glm::distance(Base::Camera3D::GetCurrentCamera()->GetPosition(), centerPos);

		// Se chunk estiver perto entra na possibilidade de colisao mouse
		if (distancia_novo < 50.0f && rayBox.intersect(boundingBox)) 
		{
			glm::vec2 chunkInitialPos = { chunk->GetId().x * CHUNK_X, chunk->GetId().y * CHUNK_Z };

			bool find = false;

			// Verifica blocos da superficies apenas.
			for (int block_x = 0; block_x < CHUNK_X; block_x++)
			{
				if (find)
				{
					break;
				}

				for (int block_z = 0; block_z < CHUNK_Z; block_z++)
				{
					glm::vec3 bounds2[2];

					bounds2[0].x = chunkInitialPos.x + block_x;
					bounds2[1].x = chunkInitialPos.x + block_x + 1;

					int maxy = chunk->GetMaxHeightAt(block_x, block_z);

					bounds2[0].y = maxy + eraseMode;
					bounds2[1].y = maxy + eraseMode + 1;

					bounds2[0].z = chunkInitialPos.y + block_z;
					bounds2[1].z = chunkInitialPos.y + block_z + 1;

					if (rayBox.intersect(bounds2))
					{
						glm::vec3 temp = (bounds2[0] + bounds2[1]);

						Base::Primitives3D::DrawCube(temp / 2.0f, { 1, 1, 1 }, { 0,0,0 }, { 1, 0, 0 }, false);
						find = true;

						if (Base::Mouse::GetMouseButtonState(Base::MouseButton::MOUSE_BUTTON_LEFT) == Base::InputAction::PRESS)
						{
							glm::vec2 block = this->currBlock;

							if (!eraseMode)
							{
								chunk->AddBlock(block_x, maxy, block_z, -1, -1);
								chunk->UpdateMaxHeightAt(block_x, block_z);
							}
							else
							{
								chunk->AddBlock(block_x, maxy + 1, block_z, block.x, block.y);
							}


							gen.UpdateChunk(chunk);
						}

						break;
					}
				}
			}
		}
	}

	Terrain::Terrain(int size)
	{
		this->size = size;
		this->playerPosition = Base::Camera3D::GetCurrentCamera()->GetPosition();
	}

	float Terrain::GetHeight(glm::vec3 playerPos)
	{
		int chunkX = this->playerPosition.x / (CHUNK_X);
		int chunkZ = this->playerPosition.z / (CHUNK_Z);

		glm::vec<2, int> xz = glm::vec<2, int>(chunkX, chunkZ);

		std::unordered_map<glm::vec<2, int>, ChunkPtr, Vec2Hash>::iterator it = this->chunks.find(xz);

		if (it == this->chunks.end())
		{
			return 0.0f;
		}

		glm::vec2 chunkPos = { chunkX * CHUNK_X, chunkZ * CHUNK_Z };

		int bloco_x = -chunkPos.x + playerPos.x;
		int bloco_z = -chunkPos.y + playerPos.z;

		return it->second->GetMaxHeightAt(bloco_x, bloco_z);
	}

	void Terrain::DrawTerrain(int maxCreateIterations, int maxDeleteIterations)
	{
		this->playerPosition = Base::Camera3D::GetCurrentCamera()->GetPosition();

		if (timeUpdate + Base::Time::GetTimestamp() > 1)
		{
			this->UpdateTerrain(maxCreateIterations, maxDeleteIterations);

			timeUpdate = Base::Time::GetTimestamp();
		}

		rayBox.SetOrig(Base::Camera3D::GetCurrentCamera()->GetPosition());
		rayBox.SetDir(Base::Camera3D::GetCurrentCamera()->GetFront());

		for (auto it = std::begin(this->chunks); it != std::end(this->chunks); it++)
		{
			this->BlockCollision(it->second);

			renderer.SetupShader();
			renderer.RenderChunk(it->second);
		}

		Base::Primitives2D::DrawPoint(Base::Window::GetSize() / 2.0f, { 1, 0, 0 });

		if (walkMode)
		{
			float h = GetHeight(playerPosition) + 4.0f;
			auto cam = Base::Camera3D::GetCurrentCamera();
			cam->SetPosition({ cam->GetPosition().x, h, cam->GetPosition().z });
		}
	}
	
	bool& Terrain::GetWalkMode()
	{
		return this->walkMode;
	}
	
	bool& Terrain::GetEraseMode()
	{
		return this->eraseMode;
	}
	
	void Terrain::SetCurrentBlock(glm::vec2 block)
	{
		this->currBlock = block;
	}
}}