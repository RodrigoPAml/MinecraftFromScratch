#include <BuildCraft.hpp>
#include "Primitives2D.hpp"

namespace BuildCraft {
namespace Base {

	VertexPtr Primitives2D::rectMesh = nullptr;
	VertexPtr Primitives2D::rectUnfilledMesh = nullptr;
	VertexPtr Primitives2D::circleMesh = nullptr;
	VertexPtr Primitives2D::circleUnfilledMesh = nullptr;
	VertexPtr Primitives2D::pointMesh = nullptr;
	VertexPtr Primitives2D::lineMesh = nullptr;
	VertexPtr Primitives2D::triangleMesh = nullptr;

	ShaderPtr Primitives2D::shader;

	bool Primitives2D::isInitialized_ = false;

	void Primitives2D::Setup(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec3& color)
	{
		const Camera2DPtr cam = Camera2D::GetCurrentCamera();

		if(cam == nullptr)
		{
			return;
		}

		glm::mat4 model(glm::mat4(1.0f));

		model = glm::translate(model, glm::vec3(position, 0.0f));
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(size.x / 2, size.y / 2, 1.0f));

		shader->Active();
		shader->SetMat4("model", model);
		shader->SetMat4("projection", cam->GetProjectionMatrix());
		shader->SetVec3("color", color);
	}

	void Primitives2D::Initialize(const int circleSegments)
	{
		if(isInitialized_) return;

		isInitialized_ = true;

		const std::string vertShader = Path::GetCurrent(3) + "\\res\\shaders\\system\\2DShape.vert";
		const std::string fragShader = Path::GetCurrent(3) + "\\res\\shaders\\system\\2DShape.frag";

		shader = ShaderPtr(new Shader(vertShader, fragShader, "", true));

		rectMesh = MeshGenerator::Generate2DRect();
		rectUnfilledMesh = MeshGenerator::Generate2DRect(DataUse::STATIC_DRAW, false);
		pointMesh = MeshGenerator::Generate2DPoint(DataUse::DYNAMIC_DRAW);
		triangleMesh = MeshGenerator::Generate2DTriangle(DataUse::DYNAMIC_DRAW);
		lineMesh = MeshGenerator::Generate2DLine(DataUse::DYNAMIC_DRAW);
		circleMesh = MeshGenerator::Generate2DCircle(circleSegments);
		circleUnfilledMesh = MeshGenerator::Generate2DCircle(circleSegments, DataUse::STATIC_DRAW, false);

		#if DEBUG_LEVEL > 0
		Debug::cout << "[Primitives2D]: Initialized";
		Debug::Log();
		#endif
	}

	bool Primitives2D::isInitialized()
	{
		return isInitialized_;
	}

	void Primitives2D::DrawRectangle(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec3& color, const bool filled)
	{
		Setup(position, size, rotation, color);

		if(filled)
		{
			rectMesh->Active();

			Command::DrawIndexedVertex(DrawType::TRIANGLES);
		}
		else
		{
			Primitives2D::rectUnfilledMesh->Active();

			Command::DrawIndexedVertex(DrawType::LINE_LOOP);
		}
	}

	void Primitives2D::DrawCircle(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec3& color, const bool filled)
	{
		Setup(position, size, rotation, color);

		if(filled)
		{
			circleMesh->Active();

			Command::DrawVertex(DrawType::TRIANGLE_FAN);
		}
		else
		{
			circleUnfilledMesh->Active();

			Command::DrawVertex(DrawType::LINE_LOOP);
		}
		
	}

	void Primitives2D::DrawTriangle(const glm::vec2& pos1, const glm::vec2& pos2, const glm::vec2& pos3, const glm::vec3& color, const bool filled)
	{
		float v[6] = {pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y};

		triangleMesh->Active();
		triangleMesh->ModifyData(0, 0, 6 * sizeof(float), &v);

		Setup({1,1}, {2,2}, 0, color);

		if(filled)
		{
			Command::DrawVertex(DrawType::TRIANGLES);
		}
		else
		{
			Command::DrawVertex(DrawType::LINE_LOOP);
		}
	}

	void Primitives2D::DrawPoint(const glm::vec2& position, const glm::vec3& color)
	{
		Setup(position, {1,1}, 0, color);

		pointMesh->Active();

		Command::DrawVertex(DrawType::POINTS);
	}

	void Primitives2D::DrawLine(const glm::vec2& pos1, const glm::vec2& pos2, const glm::vec3& color)
	{
		float v[4] = {pos1.x, pos1.y, pos2.x, pos2.y};

		lineMesh->Active();
		lineMesh->ModifyData(0, 0, 4 * sizeof(float), v);

		Setup({1,1}, {2,2}, 0, color);

		Command::DrawVertex(DrawType::LINES);
	}

	void Primitives2D::Release()
	{
		if(isInitialized_)
		{
			isInitialized_ = false;

			circleMesh.~shared_ptr();
			lineMesh.~shared_ptr();
			pointMesh.~shared_ptr();
			rectMesh.~shared_ptr();
			triangleMesh.~shared_ptr();
			circleUnfilledMesh.~shared_ptr();
			rectUnfilledMesh.~shared_ptr();
			shader.~shared_ptr();

			shader = nullptr;
			circleMesh = nullptr;
			lineMesh = nullptr;
			pointMesh = nullptr;
			rectMesh = nullptr;
			triangleMesh = nullptr;
			circleUnfilledMesh = nullptr;
			rectUnfilledMesh = nullptr;

			#if DEBUG_LEVEL > 0
			Debug::cout << "[Primitives2D]: Released";
			Debug::Log();
			#endif
		}
	}
}}
