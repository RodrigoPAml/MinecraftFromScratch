#include "BuildCraft.hpp"
#include "TerrainRenderer.hpp"

namespace BuildCraft {
namespace Core
{
	TerrainRenderer::TerrainRenderer()
	{
		std::string vertFile = Base::Path::GetCurrent(3) + "\\res\\shaders\\terrain\\terrain.vert";
		std::string fragFile = Base::Path::GetCurrent(3) + "\\res\\shaders\\terrain\\terrain.frag";
		std::string textureFile = Base::Path::GetCurrent(3) + "\\res\\texture\\atlas.jpg";

		this->shader = Base::ShaderPtr(new Base::Shader(vertFile, fragFile, "", true));

		Base::TextureQuality quality;
		quality.ansiotropicFilter = 4;
		quality.magFilter = Base::MagnificationFilter::LINEAR;
		quality.minFilter = Base::MinifyingFilter::LINEAR_MIPMAP_LINEAR;
			
		this->texture = Base::TexturePtr(new Base::Texture(textureFile));
	}

	void TerrainRenderer::SetupShader()
	{
		Base::Camera3DPtr cam3d = Base::Camera3D::GetCurrentCamera();

		this->shader->Active();
		this->shader->SetMat4("view", cam3d->GetViewMatrix());
		this->shader->SetMat4("projection", cam3d->GetProjectionMatrix());

		this->texture->ActiveTexture(1);
		this->shader->SetInt("tex", 1);
	}

	void TerrainRenderer::RenderChunk(ChunkPtr chunk)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(chunk->GetId().x * CHUNK_X, 0.0f, chunk->GetId().y * CHUNK_Z));
			
		this->shader->SetMat4("model", model);

		chunk->GetVertex()->Active();

		Base::Command::DrawIndexedVertex(Base::DrawType::TRIANGLES);
	}
}}