#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {	
namespace Base {

	enum class DrawType
	{
		POINTS = GL_POINTS,
		LINES = GL_LINES,
		LINE_LOOP = GL_LINE_LOOP,
		LINE_STRIP = GL_LINE_STRIP,
		TRIANGLES = GL_TRIANGLES,
		TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
		TRIANGLE_FAN = GL_TRIANGLE_FAN,
		LINE_ADJACENCY = GL_LINES_ADJACENCY,
		LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
		TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
		TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	};

	enum class PolygonMode
	{
		POINT = GL_POINT,
		LINE = GL_LINE,
		FILL = GL_FILL,
	};

	class Command
	{
	public:
		static void DrawVertex(const DrawType drawType);
		static void DrawIndexedVertex(const DrawType drawType);

		static void SetPolygonDrawMode(const PolygonMode mode);

		static void EnableDepthTesting();
		static void DisableDepthTesting();

		static void EnableCullingFace();
		static void DisableCullingFace();

		static void SetPrimitivePointSize(const float size);
		static void SetPrimitiveLineSize(const float size);

		static void EnableVSync();
		static void DisableVSync();

		static void EnableBlending();
		static void DisableBlending();
	};
}}
