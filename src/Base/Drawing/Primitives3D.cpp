#include <BuildCraft.hpp>
#include "Primitives3D.hpp"

namespace BuildCraft {
namespace Base {

	VertexPtr Primitives3D::meshCube = nullptr;
	VertexPtr Primitives3D::meshUnfilledCube = nullptr;
	VertexPtr Primitives3D::meshSphere = nullptr;
	VertexPtr Primitives3D::meshUnfilledSphere = nullptr;
	VertexPtr Primitives3D::meshLine = nullptr;
	VertexPtr Primitives3D::meshPoint = nullptr;
	VertexPtr Primitives3D::meshRect = nullptr;
	VertexPtr Primitives3D::meshUnfilledRect = nullptr;
	VertexPtr Primitives3D::meshCircle = nullptr;
	VertexPtr Primitives3D::meshUnfilledCircle = nullptr;
	VertexPtr Primitives3D::meshTriangle = nullptr;

	ShaderPtr Primitives3D::shader = nullptr;

	bool Primitives3D::Initialized_ = false;

	bool Primitives3D::Setup(const glm::vec3& position, const glm::vec3& size, const glm::vec3&eulerAngles, const glm::vec3& color)
	{
		const Camera3DPtr cam = Camera3D::GetCurrentCamera();

		if(cam == nullptr)
		{
			return false;
		}

		glm::mat4 model(glm::mat4(1.0f));

		model = glm::translate(model, position);

		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.5f * size.z));

		model = glm::rotate(model, glm::radians(eulerAngles.x), {1.0f, 0.0f, 0.0f});
		model = glm::rotate(model, glm::radians(eulerAngles.y), {0.0f, 1.0f, 0.0f});
		model = glm::rotate(model, glm::radians(eulerAngles.z), {0.0f, 0.0f, 1.0f});

		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, -0.5f * size.z));

		model = glm::scale(model, size);

		shader->Active();
		shader->SetMat4("model", model);
		shader->SetMat4("projection", cam->GetProjectionMatrix());
		shader->SetMat4("view", cam->GetViewMatrix());
		shader->SetVec3("color", color);

		return true;
	}

	void Primitives3D::Initialize(const int circleSegments)
	{
		if(Initialized_) return;

		Initialized_ = true;

		const std::string vertShader = Path::GetCurrent(3) + "\\res\\shaders\\system\\3DShape.vert";
		const std::string fragShader = Path::GetCurrent(3) + "\\res\\shaders\\system\\3DShape.frag";

		shader = ShaderPtr(new Shader(vertShader, fragShader, "", true));

		meshPoint = MeshGenerator::Generate3DPoint();
		meshLine = MeshGenerator::Generate3DLine();
		meshCube = MeshGenerator::Generate3DCube();
		meshUnfilledCube = MeshGenerator::Generate3DCube(DataUse::STATIC_DRAW, false);
		meshRect = MeshGenerator::Generate3DRect();
		meshUnfilledRect = MeshGenerator::Generate3DRect(DataUse::STATIC_DRAW, false);
		meshSphere = MeshGenerator::Generate3DSphere(DataUse::STATIC_DRAW, circleSegments);
		meshUnfilledSphere = MeshGenerator::Generate3DSphere(DataUse::STATIC_DRAW, circleSegments, false);
		meshTriangle = MeshGenerator::Generate3DTriangle();
		meshCircle = MeshGenerator::Generate3DCircle(circleSegments);
		meshUnfilledCircle = MeshGenerator::Generate3DCircle(circleSegments, DataUse::STATIC_DRAW, false);

		#if DEBUG_LEVEL > 0
		Debug::cout << "[Primitives3D]: Initialized";
		Debug::Log();
		#endif
	}

	bool Primitives3D::IsInitialized()
	{
		return Initialized_;
	}

	void Primitives3D::DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec3& color, const bool filled)
	{
		Setup(position, size, eulerAngles, color);

		if(filled)
		{
			meshCube->Active();

			Command::DrawIndexedVertex(DrawType::TRIANGLE_STRIP);
		}
		else
		{
			meshUnfilledCube->Active();

			Command::DrawIndexedVertex(DrawType::LINES);
		}
	}

	void Primitives3D::DrawSphere(const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec3& color, const bool filled)
	{
		Setup(position, size, eulerAngles, color);

		if(filled)
		{
			meshSphere->Active();
			Command::DrawIndexedVertex(DrawType::TRIANGLE_STRIP);
		}
		else
		{
			meshUnfilledSphere->Active();
			Command::DrawIndexedVertex(DrawType::LINES);
		}
	}

	void Primitives3D::DrawPoint(const glm::vec3& position, const glm::vec3& color)
	{
		Setup(position, {1,1,1}, {0,0,0}, color);

		meshPoint->Active();

		Command::DrawVertex(DrawType::POINTS);
	}

	void Primitives3D::DrawLine(const glm::vec3& pos1, const glm::vec3& pos2, const glm::vec3& color)
	{
		float v[6] = {pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z};

		meshLine->Active();
		meshLine->ModifyData(0, 0, 6 * sizeof(float), v);

		Setup({0,0,0}, {1,1,1}, {0,0,0}, color);

		Command::DrawVertex(DrawType::LINES);
	}

	void Primitives3D::DrawRect(const glm::vec3& position, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec3& color, const bool filled)
	{
		Setup(position, size, eulerAngles, color);

		if(filled)
		{
			meshRect->Active();

			Command::DrawIndexedVertex(DrawType::TRIANGLES);
		}
		else
		{
			meshUnfilledRect->Active();

			Command::DrawIndexedVertex(DrawType::LINE_LOOP);
		}
	}

	void Primitives3D::DrawTriangle(const glm::vec3&pos1, const glm::vec3&pos2, const glm::vec3&pos3, const glm::vec3&color, const bool filled)
	{
		float v[9] = {pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z , pos3.x, pos3.y, pos3.z};

		meshTriangle->Active();
		meshTriangle->ModifyData(0, 0, 9 * sizeof(float), v);

		Setup({0,0,0}, {1,1,1}, {0,0,0}, color);

		if(filled)
		{
			Command::DrawVertex(DrawType::TRIANGLES);
		}
		else
		{
			Command::DrawVertex(DrawType::LINE_LOOP);
		}
	}

	void Primitives3D::DrawCircle(const glm::vec3& pos, const glm::vec3& size, const glm::vec3& eulerAngles, const glm::vec3& color, const bool filled)
	{
		Setup(pos, size, eulerAngles, color);

		if(filled)
		{
			meshCircle->Active();

			Command::DrawVertex(DrawType::TRIANGLE_FAN);
		}
		else
		{
			meshUnfilledCircle->Active();

			Command::DrawVertex(DrawType::LINE_LOOP);
		}
	}

	void Primitives3D::DrawMeshTest(VertexPtr mesh, glm::vec3 position, glm::vec3 color, DrawType type, bool indexed)
	{
		Setup(position, {1, 1, 1}, {0, 0, 0 }, color);

		mesh->Active();

		if(indexed)
		{
			Command::DrawIndexedVertex(type);
		}
		else
		{
			Command::DrawVertex(type);
		}
	}

	void Primitives3D::Release()
	{
		if(!Initialized_) return;

		Initialized_ = false;

		meshCube.~shared_ptr();
		meshLine.~shared_ptr();
		meshPoint.~shared_ptr();
		meshRect.~shared_ptr();
		meshSphere.~shared_ptr();
		meshTriangle.~shared_ptr();
		meshCircle.~shared_ptr();
		meshUnfilledCube.~shared_ptr();
		meshUnfilledSphere.~shared_ptr();
		meshUnfilledRect.~shared_ptr();
		meshUnfilledCircle.~shared_ptr();
		shader.~shared_ptr();

		meshCube = nullptr;
		meshLine = nullptr;
		meshPoint = nullptr;
		meshRect = nullptr;
		meshSphere = nullptr;
		meshTriangle = nullptr;
		meshCircle = nullptr;
		meshUnfilledCube = nullptr;
		meshUnfilledSphere = nullptr;
		meshUnfilledRect = nullptr;
		meshUnfilledCircle = nullptr;
		shader = nullptr;

		#if DEBUG_LEVEL > 0
		Debug::cout << "[Primitives3D]: Released";
		Debug::Log();
		#endif
	}
}}