#include <BuildCraft.hpp>
#include "TextureRenderer.hpp"

namespace BuildCraft {
namespace Base {

	ShaderPtr TextureRenderer::shader = nullptr;

	VertexPtr TextureRenderer::mesh = nullptr;

	bool TextureRenderer::initiliazed_ = false;

	void TextureRenderer::Initialize()
	{
		if(initiliazed_)
			return;

		initiliazed_ = true;

		const std::string vertShader = Path::GetCurrent(3) + "\\res\\shaders\\system\\textureRender.vert";
		const std::string fragShader = Path::GetCurrent(3) + "\\res\\shaders\\system\\textureRender.frag";

		shader = ShaderPtr(new Shader(vertShader, fragShader, "", true));

		float vertices[] =
		{
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};

		const VertexElementDescriptor element(VertexType::FLOAT, 4, false);

		const VertexDescriptor desc({{{element}, vertices, DataUse::STATIC_DRAW}}, 6);

		mesh = VertexPtr(new Vertex(desc));

		#if DEBUG_LEVEL > 0
		Debug::cout << "[TextureRenderer]: Initialized";
		Debug::Log();
		#endif
	}

	bool TextureRenderer::IsInitialized()
	{
		return initiliazed_;
	}

	void TextureRenderer::Release()
	{
		if(initiliazed_)
		{
			mesh.~shared_ptr();
			shader.~shared_ptr();

			mesh = nullptr;
			shader = nullptr;

			initiliazed_ = false;

			#if DEBUG_LEVEL > 0
			Debug::cout << "[TextureRenderer]: Released";
			Debug::Log();
			#endif
		}
	}

	void TextureRenderer::Draw(const TexturePtr texture, const glm::vec2& position,const glm::vec2& size, const float rotation)
	{
		const Camera2DPtr cam = Camera2D::GetCurrentCamera();

		if(cam != nullptr && texture != nullptr && texture->isValid())
		{
			shader->Active();

			glm::mat4 model(glm::mat4(1.0f));

			model = glm::translate(model, glm::vec3(position, 0.0f));
			model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
			model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(size, 1.0f));

			texture->ActiveTexture(0);

			shader->SetMat4("model", model);
			shader->SetMat4("projection", cam->GetProjectionMatrix());
			shader->SetInt("image", 0);

			mesh->Active();

			Command::DrawVertex(DrawType::TRIANGLES);
		}
	}
}}

