#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Base {

	class Primitives3D
	{
	private:
		static VertexPtr meshCube, meshUnfilledCube, meshSphere, meshUnfilledSphere, meshPoint, meshLine, meshRect, meshUnfilledRect, meshCircle, meshUnfilledCircle, meshTriangle;

		static ShaderPtr shader;

		static bool Initialized_;

		static bool Setup(const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec3& color);
	public:
		static void Initialize(const int circleSegments = 20);

		static bool IsInitialized();

		static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec3& color, bool filled = true);

		static void DrawSphere(const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec3& color, bool filled = true);

		static void DrawPoint(const glm::vec3& position, const glm::vec3& color);

		static void DrawLine(const glm::vec3& pos1, const glm::vec3& pos2, const glm::vec3& color);

		static void DrawRect(const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec3& color, bool filled = true);

		static void DrawTriangle(const glm::vec3& pos1, const glm::vec3& pos2, const glm::vec3& pos3, const glm::vec3& color, bool filled = true);

		static void DrawCircle(const glm::vec3& pos, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec3& color, bool filled = true);

		static void DrawMeshTest(VertexPtr mesh, glm::vec3 position, glm::vec3 color, DrawType type, bool indexed);

		static void Release();
	};
}}
