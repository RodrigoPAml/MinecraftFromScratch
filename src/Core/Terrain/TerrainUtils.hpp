#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Core
{
	// With face of the block it is
	enum class FaceType
	{
		Upper,
		Bottom,
		Left,
		Right,
		Front,
		Back
	};

	// The block vertex attributes
	struct BlockVertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;

		BlockVertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& uv)
		{
			this->position = pos;
			this->normal = normal;
			this->uv = uv;
		}
	};
	
	// Hash function
	struct Vec2Hash
	{
		std::size_t operator()(const glm::vec<2, int>& k) const
		{
			using std::hash;
			return ((hash<float>()(k.x) ^ (hash<float>()(k.y) << 1)) >> 1);
		}
	};
}}