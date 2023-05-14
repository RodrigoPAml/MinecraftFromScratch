#include <BuildCraft.hpp>
#include "Block.hpp"

namespace BuildCraft {
namespace Core
{
	Block::Block()
	{
		this->u = -1;
		this->v = -1;
	}

	Block::Block(int u, int v)
	{
		this->u = u;
		this->v = v;
	}

	bool Block::IsVisible() const
	{
		return this->isVisible;
	}

	void Block::SetVisible(bool value)
	{
		this->isVisible = value;
	}

	glm::vec2 Block::GetUV()
	{
		return { this->u, this->v };
	}

	bool Block::isEmpty(Block& block) 
	{
		if (block.u == -1 && block.v == -1)
		{
			return true;
		}

		if (block.v == 29)
		{
			return true;
		}

		return false;
	}

	bool Block::isFlower(Block& block)
	{
		if(block.v == 29)
		{
			return true;
		}

		return false;
	}
}}