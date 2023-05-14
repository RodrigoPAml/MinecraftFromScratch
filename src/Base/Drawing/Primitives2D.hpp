#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Base {

	class Primitives2D
	{
	private:
		static VertexPtr rectMesh, rectUnfilledMesh, circleMesh, circleUnfilledMesh, pointMesh, lineMesh, triangleMesh;

		static ShaderPtr shader;

		static bool isInitialized_;

		static void Setup(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec3& color);
	public:
		static void Initialize(const int circleSegments = 40);

		static bool isInitialized();

		static void DrawRectangle(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec3& color, const bool filled = true);

		static void DrawCircle(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec3& color, const bool filled = true);

		static void DrawTriangle(const glm::vec2& pos1, const glm::vec2& pos2, const glm::vec2& pos3, const glm::vec3& color, const bool filled = true);

		static void DrawPoint(const glm::vec2& position, const glm::vec3& color);

		static void DrawLine(const glm::vec2& pos1, const glm::vec2& pos2, const glm::vec3& color);

		static void Release();
	};
}}
