#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Base {

	enum class VertexType
	{
		BYTE = GL_BYTE,
		UBYTE = GL_UNSIGNED_BYTE,
		SHORT = GL_SHORT,
		USHORT = GL_UNSIGNED_SHORT,
		INT = GL_INT,
		UINT = GL_UNSIGNED_INT,
		HALF_FLOAT = GL_HALF_FLOAT,
		FLOAT = GL_FLOAT,
		DOUBLE = GL_DOUBLE,
		INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
		UINT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
	};

	struct VertexElementDescriptor
	{
		VertexType type = VertexType::FLOAT;

		unsigned int count = 0;

		bool isNormalized = false;

		VertexElementDescriptor() = default;

		VertexElementDescriptor(const VertexType type, const unsigned int count, const bool isNormalized = false)
		{
			this->type = type;
			this->count = count;
			this->isNormalized = isNormalized;
		}
	};

	struct VertexBufferDescriptor
	{
		std::vector<VertexElementDescriptor> bufferLayout = std::vector<VertexElementDescriptor>();

		void* data = nullptr;

		DataUse use = DataUse::STATIC_DRAW;

		VertexBufferDescriptor() = default;

		VertexBufferDescriptor(const std::vector<VertexElementDescriptor>& bufferLayout, void* data, const DataUse use)
		{
			this->bufferLayout = bufferLayout;
			this->data = data;
			this->use = use;
		}
	};

	struct VertexDescriptor
	{
		std::vector<VertexBufferDescriptor> buffers = std::vector<VertexBufferDescriptor>();

		unsigned int verticesCount = 0;

		VertexDescriptor() = default;

		VertexDescriptor(const std::vector<VertexBufferDescriptor>& buffers, const unsigned int verticesCount)
		{
			this->buffers = buffers;
			this->verticesCount = verticesCount;
		}
	};

	struct IndexedVertexDescriptor
	{
		unsigned int* indices = nullptr;

		unsigned int count = 0;

		DataUse use = DataUse::STATIC_DRAW;

		IndexedVertexDescriptor() = default;

		IndexedVertexDescriptor(unsigned int* indices, const unsigned int count, const DataUse use)
		{
			this->indices = indices;
			this->count = count;
			this->use = use;
		}
	};

	class Vertex
	{
		friend class Command;
	private:
		static unsigned int CurrVao, CurrVS; // Current Vao Active and respective number of vertices

		unsigned int VAO; // ID of Vertex Array Object

		unsigned int VS; // The number of vertices (all buffers have the same number of vertices)
							// If use IBO this is the number of indices, and not triangles
							// Value used in draw calls

		unsigned int* VBOS; // IDs of Vertex Buffer Object

		unsigned int IBO; // ID of Index Buffer object

		VertexDescriptor descriptor; // Save the descriptor used to create this Vertex
										// The void* data will not be available if deleted before

		IndexedVertexDescriptor idescriptor; // Save the descriptor used to create the indices of this vertex
												// The unsigned int* data will not be available if deleted before
			
	public:
		Vertex(const VertexDescriptor& descriptor);
		Vertex(const VertexDescriptor& descriptor, const IndexedVertexDescriptor& idescriptor);
		~Vertex();

		VertexDescriptor GetDescriptor() const;
		IndexedVertexDescriptor GetIndexedDescriptor() const;

		bool isValid() const;

		void Active() const;

		void ModifyData(const unsigned int buffer, const unsigned int start, const unsigned int tam, void* data) const;

		static void ClearCurrentActive();

		static unsigned int GetSizeOfType(const VertexType type);
	};

	typedef std::shared_ptr<Vertex> VertexPtr;
}}