#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Base {

	class MeshGenerator
	{
	public:
		// Usage: Draw with DrawType::POINTS and do not use indices
		static VertexPtr Generate2DPoint(const DataUse use = DataUse::STATIC_DRAW);
		// Usage: Draw with DrawType::DrawType::LINES and do not use indices
		static VertexPtr Generate2DLine(const DataUse use = DataUse::STATIC_DRAW);
		// Usage filled: Draw with DrawType::TRIANGLES and use indices
		// Usage unfilled: Draw with DrawType::LINE_LOOP and use indices
		static VertexPtr Generate2DRect(const DataUse use = DataUse::STATIC_DRAW, const bool filled = true);
		// Usage filled: Draw with DrawType::TRIANGLE_FAN and do not use indices
		// Usage unfilled: Draw with DrawType::LINE_LOOP and do not use indices
		static VertexPtr Generate2DCircle(const unsigned int nsegments = 20, const DataUse use = DataUse::STATIC_DRAW, const bool filled = true);
		// Usage filled: Draw with DrawType::TRIANGLES and do not use indices
		// Usage unfilled: Draw with DrawType::LINE_LOOP and do not use indices
		static VertexPtr Generate2DTriangle(const DataUse use = DataUse::STATIC_DRAW);

		// Usage: Draw with DrawType::POINTS and do not use indices
		static VertexPtr Generate3DPoint(const DataUse use = DataUse::STATIC_DRAW);
		// Usage: Draw with DrawType::DrawType::LINES and do not use indices
		static VertexPtr Generate3DLine(const DataUse use = DataUse::STATIC_DRAW);
		// Usage filled: Draw with DrawType::TRIANGLES and use indices
		// Usage unfilled: Draw with DrawType::LINE_LOOP and use indices
		static VertexPtr Generate3DRect(const DataUse use = DataUse::STATIC_DRAW, const bool filled = true);
		// Usage filled: Draw with DrawType::TRIANGLE_FAN and do not use indices
		// Usage unfilled: Draw with DrawType::LINE_LOOP and do not use indices
		static VertexPtr Generate3DCircle(const unsigned int nsegments = 20, const DataUse use = DataUse::STATIC_DRAW, const bool filled = true);
		// Usage filled: Draw with DrawType::TRIANGLES and do not use indices
		// Usage unfilled: Draw with DrawType::LINE_LOOP and do not use indices
		static VertexPtr Generate3DTriangle(const DataUse use = DataUse::STATIC_DRAW);
		// Usage filled: Draw with DrawType::TRIANGLES_STRIP and use indices
		// Usage unfilled: Draw with DrawType::LINES and use indices
		static VertexPtr Generate3DSphere(const DataUse use = DataUse::STATIC_DRAW, const int nsegments = 20, const bool filled = true);
		// Usage filled: Draw with DrawType::TRIANGLES_STRIP and use indices
		// Usage unfilled: Draw with DrawType::LINES and use indices
		static VertexPtr Generate3DCube(const DataUse use = DataUse::STATIC_DRAW, const bool filled = true);
	};
}}

