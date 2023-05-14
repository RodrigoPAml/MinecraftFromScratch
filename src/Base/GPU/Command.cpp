#include <BuildCraft.hpp>
#include "Command.hpp"

namespace BuildCraft {
namespace Base {

	void Command::DrawVertex(const DrawType drawType)
	{
		glDrawArrays((GLenum)drawType, 0, Vertex::CurrVS);
	}

	void Command::DrawIndexedVertex(const DrawType drawType)
	{
		glDrawElements((GLenum)drawType, Vertex::CurrVS, (GLenum)VertexType::UINT, 0);
	}

	void Command::SetPolygonDrawMode(const PolygonMode mode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, (GLenum)mode);
	}

	void Command::EnableDepthTesting()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void Command::DisableDepthTesting()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void Command::EnableCullingFace()
	{
		glEnable(GL_CULL_FACE);
	}

	void Command::DisableCullingFace()
	{
		glDisable(GL_CULL_FACE);
	}

	void Command::SetPrimitivePointSize(const float size)
	{
		glPointSize(size);
	}

	void Command::SetPrimitiveLineSize(const float size)
	{
		glLineWidth(size);
	}

	void Command::EnableVSync()
	{
		glfwSwapInterval(1);
	}

	void Command::DisableVSync()
	{
		glfwSwapInterval(0);
	}

	void Command::EnableBlending()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Command::DisableBlending()
	{
		glDisable(GL_BLEND);
	}
}}