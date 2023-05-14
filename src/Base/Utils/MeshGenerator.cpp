#include <BuildCraft.hpp>
#include "MeshGenerator.hpp"

namespace BuildCraft {
namespace Base {

	VertexPtr MeshGenerator::Generate2DPoint(const DataUse use)
	{
		float verticesPoint[] =
		{
			0.0f, 0.0f
		};

		VertexElementDescriptor element(VertexType::FLOAT, 2);

		VertexDescriptor desc({{{element}, verticesPoint, use}}, 1);

		return VertexPtr(new Vertex(desc));
	}

	VertexPtr MeshGenerator::Generate2DLine(const DataUse use)
	{
		float verticesLine[] =
		{
			1.0f, 1.0f,
			2.0f, 2.0f,
		};

		VertexElementDescriptor element(VertexType::FLOAT, 2);

		VertexDescriptor desc({{{element}, verticesLine, use}}, 2);

		return VertexPtr(new Vertex(desc));
	}

	VertexPtr MeshGenerator::Generate2DRect(const DataUse use, const bool filled)
	{
		float verticesRect[] =
		{
				1.0f,  1.0f,
				1.0f, -1.0f,
			-1.0f, -1.0f,
			-1.0f,  1.0f,
		};

		unsigned int indicesRect[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		unsigned int indicesUnfilledRect[] =
		{
			0, 1, 2, 3
		};

		VertexElementDescriptor element(VertexType::FLOAT, 2);

		VertexDescriptor desc({{{element}, verticesRect, use}}, 4);
		
		if(filled)
		{
			IndexedVertexDescriptor idesc(indicesRect, 6, use);

			return VertexPtr(new Vertex(desc, idesc));
		}
		else
		{
			IndexedVertexDescriptor idesc(indicesUnfilledRect, 4, use);

			return VertexPtr(new Vertex(desc, idesc));
		}
	}

	VertexPtr MeshGenerator::Generate2DCircle(const unsigned int nsegments, const DataUse use, const bool filled)
	{
		if(filled)
		{
			float* verticesCircle = new float[(nsegments+1) * 2]();

			verticesCircle[0] = 0.0f;
			verticesCircle[1] = 0.0f;

			for(int i = 1; i < nsegments+1; i++)
			{
				float theta = 2.0f * glm::pi<float>() * float(i) / float(nsegments-1);

				verticesCircle[i * 2] = cosf(theta);
				verticesCircle[(i * 2) + 1] = sinf(theta);
			}

			VertexElementDescriptor element(VertexType::FLOAT, 2);

			VertexDescriptor desc({{{element}, verticesCircle, use}}, nsegments + 1);

			VertexPtr arr = VertexPtr(new Vertex(desc));

			delete[] verticesCircle;

			return arr;
		}
		else
		{
			float* verticesCircle = new float[(nsegments) * 2]();

			for(int i = 0; i < nsegments; i++)
			{
				float theta = 2.0f * glm::pi<float>() * float(i) / float(nsegments);

				verticesCircle[i * 2] = cosf(theta);
				verticesCircle[(i * 2) + 1] = sinf(theta);
			}

			VertexElementDescriptor element(VertexType::FLOAT, 2);

			VertexDescriptor desc({{{element}, verticesCircle, use}}, nsegments);

			VertexPtr arr = VertexPtr(new Vertex(desc));

			delete[] verticesCircle;

			return arr;
		}
	}

	VertexPtr MeshGenerator::Generate2DTriangle(const DataUse use)
	{
		float verticeTriBase[] =
		{
			-0.5f, -0.5f,
				0.5f, -0.5f,
				0.0f,  0.5f,
		};

		VertexElementDescriptor element(VertexType::FLOAT, 2);

		VertexDescriptor desc({{{element}, verticeTriBase, use}}, 3);

		return VertexPtr(new Vertex(desc));
	}

	VertexPtr MeshGenerator::Generate3DPoint(const DataUse use)
	{
		float verticesPoint[] =
		{
			0.0f, 0.0f, 0.0f
		};

		VertexElementDescriptor element(VertexType::FLOAT, 3);

		VertexDescriptor desc({{{element}, verticesPoint, use}}, 1);

		return VertexPtr(new Vertex(desc));
	}

	VertexPtr MeshGenerator::Generate3DLine(const DataUse use)
	{
		float verticesLine[] =
		{
			1.0f, 1.0f, 1.0f,
			2.0f, 2.0f, 1.0f
		};

		VertexElementDescriptor element(VertexType::FLOAT, 3);

		VertexDescriptor desc({{{element}, verticesLine, use}}, 2);
	
		return VertexPtr(new Vertex(desc));
	}

	VertexPtr MeshGenerator::Generate3DRect(const DataUse use, const bool filled)
	{
		float verticesRect[] =
		{
				0.5f,  0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		unsigned int indicesRect[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		unsigned int indicesUnfilledRect[] =
		{
			0, 1, 2, 3
		};

		VertexElementDescriptor element(VertexType::FLOAT, 3);

		VertexDescriptor desc({{{element}, verticesRect, use}}, 4);

		if(filled)
		{
			IndexedVertexDescriptor idesc(indicesRect, 6, use);

			return VertexPtr(new Vertex(desc, idesc));
		}
		else
		{
			IndexedVertexDescriptor idesc(indicesUnfilledRect, 4, use);

			return VertexPtr(new Vertex(desc, idesc));
		}
	}

	VertexPtr MeshGenerator::Generate3DCircle(const unsigned int nsegments, const DataUse use, const bool filled)
	{
		if(filled)
		{
			float* verticesCircle = new float[(nsegments + 1) * 3]();

			verticesCircle[0] = 0.0f;
			verticesCircle[1] = 0.0f;
			verticesCircle[2] = 0.0f;

			for(int i = 1; i < nsegments + 1; i++)
			{
				float theta = 2.0f * glm::pi<float>() * float(i) / float(nsegments - 1);

				verticesCircle[i * 3] = cosf(theta) * 0.5f;
				verticesCircle[(i * 3) + 1] = sinf(theta) * 0.5f;
				verticesCircle[(i * 3) + 2] = 0;
			}

			VertexElementDescriptor element(VertexType::FLOAT, 3);

			VertexDescriptor desc({{{element}, verticesCircle, use}}, nsegments + 1);

			VertexPtr arr = VertexPtr(new Vertex(desc));

			delete[] verticesCircle;

			return arr;
		}
		else
		{
			float* verticesCircle = new float[(nsegments) * 3]();

			for(int i = 0; i < nsegments; i++)
			{
				float theta = 2.0f * glm::pi<float>() * float(i) / float(nsegments);

				verticesCircle[i * 3] = cosf(theta) * 0.5f;
				verticesCircle[(i * 3) + 1] = sinf(theta) * 0.5f;
				verticesCircle[(i * 3) + 2] = 0;
			}

			VertexElementDescriptor element(VertexType::FLOAT, 3);

			VertexDescriptor desc({{{element}, verticesCircle, use}}, nsegments);

			VertexPtr arr = VertexPtr(new Vertex(desc));

			delete[] verticesCircle;

			return arr;
		}
	}

	VertexPtr MeshGenerator::Generate3DTriangle(const DataUse use)
	{
		float trianglesVert[] =
		{
			0.0f, 1.0f, 0.0f,
			-0.5f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f,
		};

		VertexElementDescriptor element(VertexType::FLOAT, 3);

		VertexDescriptor desc({{{element}, trianglesVert, use}}, 3);

		return VertexPtr(new Vertex(desc));
	}

	VertexPtr MeshGenerator::Generate3DSphere(const DataUse use, const int n_segments, const bool filled)
	{
		if(filled)
		{
			std::vector<float> vert;
			std::vector<unsigned int> indices;

			for(unsigned int y = 0; y <= n_segments; ++y)
			{
				for(unsigned int x = 0; x <= n_segments; ++x)
				{
					float xSegment = (float)x / (float)n_segments;
					float ySegment = (float)y / (float)n_segments;

					float xPos = std::cos(xSegment * glm::pi<float>() * 2.0f) * std::sin(ySegment * glm::pi<float>());
					float yPos = std::cos(ySegment * glm::pi<float>());
					float zPos = std::sin(xSegment * glm::pi<float>() * 2.0f) * std::sin(ySegment * glm::pi<float>());

					vert.push_back(xPos*0.5f);
					vert.push_back(yPos*0.5f);
					vert.push_back(zPos*0.5f);
				}
			}

			for(int y = 0; y < n_segments; ++y)
			{
				for(int x = 0; x < n_segments; ++x)
				{
					indices.push_back((y + 1) * (n_segments + 1) + x);
					indices.push_back(y * (n_segments + 1) + x);
					indices.push_back(y * (n_segments + 1) + x + 1);

					indices.push_back((y + 1) * (n_segments + 1) + x);
					indices.push_back(y * (n_segments + 1) + x + 1);
					indices.push_back((y + 1) * (n_segments + 1) + x + 1);
				}
			}

			VertexElementDescriptor element(VertexType::FLOAT, 3);

			VertexDescriptor desc({{{element}, &vert[0], use}}, (unsigned int)vert.size() / 3);

			IndexedVertexDescriptor idesc(&indices[0], (unsigned int)indices.size(), use);

			return VertexPtr(new Vertex(desc, idesc));
		}
		else
		{
			float* verticesCircle = new float[(n_segments*3) * 3];

			std::vector<unsigned int> indices;

			for(int i = 0; i < n_segments; i++)
			{
				float theta = 2.0f * glm::pi<float>() * float(i) / float(n_segments);

				verticesCircle[i * 3] = cosf(theta) * 0.5f;
				verticesCircle[(i * 3) + 1] = sinf(theta) * 0.5f;
				verticesCircle[(i * 3) + 2] = 0;

				indices.push_back(i);
				indices.push_back(i+1);
			}

			indices[indices.size()-1] = 0;

			for(int i = n_segments; i < n_segments*2; i++)
			{
				float theta = 2.0f * glm::pi<float>() * float(i) / float(n_segments);

				verticesCircle[i * 3] = cosf(theta) * 0.5f;
				verticesCircle[(i * 3) + 2] = sinf(theta) * 0.5f;
				verticesCircle[(i * 3) + 1] = 0;

				indices.push_back(i);
				indices.push_back(i + 1);
			}

			indices[indices.size() - 1] = n_segments;

			for(int i = n_segments*2; i < n_segments*3; i++)
			{
				float theta = 2.0f * glm::pi<float>() * float(i) / float(n_segments);

				verticesCircle[i * 3 + 1] = cosf(theta) * 0.5f;
				verticesCircle[(i * 3) + 2] = sinf(theta) * 0.5f;
				verticesCircle[(i * 3)] = 0;

				indices.push_back(i);
				indices.push_back(i + 1);
			}

			indices[indices.size() - 1] = n_segments*2;

			VertexElementDescriptor element(VertexType::FLOAT, 3);

			VertexDescriptor desc({{{element}, verticesCircle, use}}, (unsigned int)n_segments * 3);

			IndexedVertexDescriptor idesc(&indices[0], indices.size(), DataUse::STATIC_DRAW);

			VertexPtr arr = VertexPtr(new Vertex(desc, idesc));

			delete[] verticesCircle;

			return arr;
		}
	}

	VertexPtr MeshGenerator::Generate3DCube(const DataUse use, const bool filled)
	{
		float cubeVertices[] =
		{
			-0.5, -0.5, 0.5,
			0.5, -0.5, 0.5,
			-0.5, 0.5, 0.5,
			0.5, 0.5, 0.5,
			-0.5, -0.5, -0.5,
			0.5, -0.5, -0.5,
			-0.5,  0.5, -0.5,
			0.5,  0.5, -0.5,
		};

		unsigned int cubeIndices[] =
		{
			0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
		};

		unsigned int cubeUnfilledIndices[] =
		{
			0, 1, 0, 2, 0, 4, 4, 5, 5, 7, 2, 3, 3, 7, 3, 1, 1, 5, 7, 6, 4, 6, 6, 2
		};

		VertexElementDescriptor element(VertexType::FLOAT, 3);

		VertexDescriptor desc({{{element}, cubeVertices, use}}, 10);

		if(filled)
		{
			IndexedVertexDescriptor idesc(cubeIndices, 14, use);

			return VertexPtr(new Vertex(desc, idesc));
		}
		else
		{
			IndexedVertexDescriptor idesc(cubeUnfilledIndices, 24, use);

			return VertexPtr(new Vertex(desc, idesc));
		}
	}
}}