#include <BuildCraft.hpp>
#include "Vertex.hpp"

namespace BuildCraft {
namespace Base {

	unsigned int Vertex::CurrVao = 0;
	unsigned int Vertex::CurrVS = 0;

	Vertex::Vertex(const VertexDescriptor& descriptor)
	{
		this->VAO = 0;
		this->IBO = 0;
		this->VBOS = new unsigned int[descriptor.buffers.size()];
		this->descriptor = descriptor;
		this->VS = descriptor.verticesCount;

		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);
		glGenBuffers(descriptor.buffers.size(), this->VBOS);

		for(int i = 0; i < descriptor.buffers.size(); i++)
		{
			int buffer_total_size = 0;

			for(const VertexElementDescriptor element : descriptor.buffers[i].bufferLayout)
			{
				buffer_total_size += GetSizeOfType(element.type) * element.count;
			}

			buffer_total_size = buffer_total_size * descriptor.verticesCount;

			glBindBuffer(GL_ARRAY_BUFFER, VBOS[i]);
			glBufferData(GL_ARRAY_BUFFER, buffer_total_size, descriptor.buffers[i].data, (GLenum)descriptor.buffers[i].use);
		}

		int index = 0;
		for(int i = 0; i < descriptor.buffers.size(); i++)
		{
			glBindBuffer(GL_ARRAY_BUFFER, VBOS[i]);

			int buffer_slice_size = 0, current_offset = 0;

			for(const VertexElementDescriptor element : descriptor.buffers[i].bufferLayout)
			{
				buffer_slice_size += GetSizeOfType(element.type) * element.count;
			}

			for(const VertexElementDescriptor element : descriptor.buffers[i].bufferLayout)
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, element.count, (GLenum)element.type, (GLboolean)element.isNormalized, buffer_slice_size, (void*)current_offset);

				current_offset += element.count * GetSizeOfType(element.type);

				index++;
			}
		}

		Vertex::CurrVao = 0;
		Vertex::CurrVS = 0;

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		#if DEBUG_LEVEL > 0
		Debug::cout << "[Vertex]: Created (VAO = " << this->VAO << ')';
		Debug::Log();
		#endif		
	}

	Vertex::Vertex(const VertexDescriptor& descriptor, const IndexedVertexDescriptor& idescriptor)
	{
		this->VAO = 0;
		this->VBOS = new unsigned int[descriptor.buffers.size()];
		this->descriptor = descriptor;
		this->idescriptor = idescriptor;
		this->VS = idescriptor.count;

		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);
		glGenBuffers(1, &this->IBO);
		glGenBuffers(descriptor.buffers.size(), VBOS);
	
		unsigned int IndiceBufferSize = GetSizeOfType(VertexType::UINT) * idescriptor.count;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndiceBufferSize, idescriptor.indices, (GLenum)idescriptor.use);

		for(int i = 0; i < descriptor.buffers.size(); i++)
		{
			int buffer_total_size = 0;

			for(const VertexElementDescriptor element : descriptor.buffers[i].bufferLayout)
			{
				buffer_total_size += GetSizeOfType(element.type) * element.count;
			}

			buffer_total_size = buffer_total_size * descriptor.verticesCount;

			glBindBuffer(GL_ARRAY_BUFFER, VBOS[i]);
			glBufferData(GL_ARRAY_BUFFER, buffer_total_size, descriptor.buffers[i].data, (GLenum)descriptor.buffers[i].use);
		}

		int index = 0;
		for(int i = 0; i < descriptor.buffers.size(); i++)
		{
			glBindBuffer(GL_ARRAY_BUFFER, VBOS[i]);

			int buffer_slice_size = 0, current_offset = 0;

			for(const VertexElementDescriptor element : descriptor.buffers[i].bufferLayout)
			{
				buffer_slice_size += GetSizeOfType(element.type) * element.count;
			}

			for(const VertexElementDescriptor element : descriptor.buffers[i].bufferLayout)
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, element.count, (GLenum)element.type, (GLboolean)element.isNormalized, buffer_slice_size, (void*)current_offset);

				current_offset += element.count * GetSizeOfType(element.type);

				index++;
			}
		}

		Vertex::CurrVao = 0;
		Vertex::CurrVS = 0;

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		#if DEBUG_LEVEL > 0
		Debug::cout << "[Vertex]: Created indexed (VAO = " << this->VAO << ')';
		Debug::Log();
		#endif		
	}

	Vertex::~Vertex()
	{
		#if DEBUG_LEVEL > 0
		Debug::cout << "[Vertex]: Deleted (VAO = " << this->VAO << ')';
		Debug::Log();
		#endif		

		if(this->VAO == CurrVao)
		{
			glBindVertexArray(0);

			CurrVao = 0;
			CurrVS = 0;
		}

		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(descriptor.buffers.size(), this->VBOS);

		if(this->IBO != 0)
		{
			glDeleteBuffers(1, &this->IBO);
		}

		if(VBOS != nullptr)
		{
			delete[] VBOS;
			VBOS = nullptr;
		}
	}

	VertexDescriptor Vertex::GetDescriptor() const
	{
		return this->descriptor;
	}

	IndexedVertexDescriptor Vertex::GetIndexedDescriptor() const
	{
		return this->idescriptor;
	}

	bool Vertex::isValid() const
	{
		return (this->VAO != 0);
	}

	void Vertex::Active() const
	{
		if(!this->isValid())
		{
			return;
		}

		if(this->VAO == CurrVao)
		{
			return;
		}

		glBindVertexArray(this->VAO);

		#if DEBUG_LEVEL > 1
		Debug::cout << "[Vertex]: Activated (VAO = " << this->VAO << ')';
		Debug::Log();
		#endif		

		CurrVao = this->VAO;
		CurrVS = this->VS;
	}

	void Vertex::ModifyData(const unsigned int buffer, const unsigned int start, const unsigned int tam, void* data) const
	{
		if(!this->isValid())
		{
			return;
		}

		if(buffer < 0 || buffer >= descriptor.buffers.size())
		{
			return;
		}

		glBindBuffer(GL_ARRAY_BUFFER, this->VBOS[buffer]);
		glBufferSubData(GL_ARRAY_BUFFER, start, tam, data);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Vertex::ClearCurrentActive()
	{
		glBindVertexArray(0);

		CurrVao = 0;
		CurrVS = 0;
	}

	unsigned int Vertex::GetSizeOfType(const VertexType type)
	{
		switch(type)
		{
		case VertexType::BYTE:
			return 1;
			break;
		case VertexType::UBYTE:
			return 1;
			break;
		case VertexType::SHORT:
			return 2;
			break;
		case VertexType::USHORT:
			return 2;
			break;
		case VertexType::INT:
			return 4;
			break;
		case VertexType::UINT:
			return 4;
			break;
		case VertexType::HALF_FLOAT:
			return 2;
			break;
		case VertexType::FLOAT:
			return 4;
			break;
		case VertexType::DOUBLE:
			return 8;
			break;
		case VertexType::INT_2_10_10_10_REV:
			return 4;
			break;
		case VertexType::UINT_2_10_10_10_REV:
			return 4;
			break;
		default:
			return 0;
			break;
		}
	}
}}