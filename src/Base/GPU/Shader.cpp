#include <BuildCraft.hpp>
#include "Shader.hpp"

namespace BuildCraft {
namespace Base {

	unsigned int Shader::currentID = 0;

	Shader::Shader()
	{
		this->ID = 0;
	}

	Shader::Shader(const std::string& verticeShader, const std::string& fragmentShader, const std::string& geometryShader, const bool fromFile)
	{
		char* VS = nullptr;
		char* FS = nullptr;
		char* GS = nullptr;

		this->ID = 0;

		if(fromFile)
		{
			std::ifstream vertFile(verticeShader);
			std::ifstream fragmentFile(fragmentShader);
			std::ifstream geometryFile(geometryShader);

			if(!fragmentFile.is_open())
			{
				#if DEBUG_LEVEL > 0
				Debug::cout << "[Shader]: Failed to open fragment file: " << fragmentShader;
				Debug::Log();
				#endif

				return;
			}

			if(!vertFile.is_open())
			{
				#if DEBUG_LEVEL > 0
				Debug::cout << "[Shader]: Failed to open vertice file: " << verticeShader;
				Debug::Log();
				#endif

				return;
			}

			if(!geometryShader.empty() && !geometryFile.is_open())
			{
				#if DEBUG_LEVEL > 0
				Debug::cout << "[Shader]: Failed to open geometry file: " << geometryShader;
				Debug::Log();
				#endif

				return;
			}

			std::stringstream stream, stream2, stream3;

			stream << vertFile.rdbuf();
			VS = new char[stream.str().size() + 1];
			strcpy(VS, stream.str().c_str());
			vertFile.close();

			stream2 << fragmentFile.rdbuf();
			FS = new char[stream2.str().size() + 1];
			strcpy(FS, stream2.str().c_str());
			fragmentFile.close();

			if(!geometryShader.empty())
			{
				stream3 << geometryFile.rdbuf();
				GS = new char[stream3.str().size() + 1];
				strcpy(GS, stream3.str().c_str());
			}

			geometryFile.close();
		}
		else
		{
			if(verticeShader.size() > 0)
			{
				VS = new char[verticeShader.size() + 1];
				strcpy(VS, verticeShader.c_str());
			}

			if(fragmentShader.size() > 0)
			{
				FS = new char[fragmentShader.size() + 1];
				strcpy(FS, fragmentShader.c_str());
			}
			
			if(geometryShader.size() > 0)
			{
				GS = new char[geometryShader.size() + 1];
				strcpy(GS, geometryShader.c_str());
			}		
		}

		unsigned int vertex, fragment, geometry, ID;

		vertex = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertex, 1, &VS, NULL);
		glCompileShader(vertex);

		if(Shader::CheckError(vertex, "VertexData"))
		{
			glDeleteShader(vertex);

			delete[] VS;
			delete[] FS;
			delete[] GS;

			return;
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(fragment, 1, &FS, NULL);
		glCompileShader(fragment);

		if(Shader::CheckError(fragment, "FRAGMENT"))
		{
			glDeleteShader(vertex);
			glDeleteShader(fragment);

			delete[] VS;
			delete[] FS;
			delete[] GS;

			return;
		}

		if(!geometryShader.empty())
		{
			geometry = glCreateShader(GL_GEOMETRY_SHADER);

			glShaderSource(geometry, 1, &GS, NULL);
			glCompileShader(geometry);

			if(Shader::CheckError(geometry, "GEOMETRY"))
			{
				glDeleteShader(vertex);
				glDeleteShader(fragment);
				glDeleteShader(geometry);

				delete[] VS;
				delete[] FS;
				delete[] GS;

				return;
			}
		}

		ID = glCreateProgram();

		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);

		if(!geometryShader.empty())
		{
			glAttachShader(ID, geometry);
		}

		glLinkProgram(ID);

		if(Shader::CheckError(ID, "PROGRAM"))
		{
			glDeleteShader(vertex);
			glDeleteShader(fragment);
			glDeleteShader(geometry);

			glDeleteShader(ID);

			ID = 0;

			delete[] VS;
			delete[] FS;
			delete[] GS;

			return;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		if(!geometryShader.empty())
		{
			glDeleteShader(geometry);
		}

		this->ID = ID;

		delete[] VS;
		delete[] FS;
		delete[] GS;

		#if DEBUG_LEVEL > 0
		Debug::cout << "[Shader]: Created (ID = " << this->ID << ')';
		Debug::Log();
		#endif
	}

	Shader::~Shader()
	{
		if(this->isValid())
		{
			if(currentID == this->ID)
			{
				currentID = 0;
				glUseProgram(0);
			}

			#if DEBUG_LEVEL > 0
			Debug::cout << "[Shader]: Deleted (ID = " << this->ID << ')';
			Debug::Log();
			#endif		

			glDeleteProgram(this->ID);
		}
	}

	bool Shader::isValid() const
	{
		return (this->ID != 0);
	}

	void Shader::Active() const
	{
		if(!this->isValid())
		{
			return;
		}

		if(currentID == this->ID)
		{
			return;
		}

			
		#if DEBUG_LEVEL > 1
		Debug::cout << "[Shader]: Activated (ID = " << this->ID << ')';
		Debug::Log();
		#endif		

		glUseProgram(this->ID);
	}

	void Shader::ClearCurrentShader()
	{
		glUseProgram(0);
	}

	void Shader::SetBool(const std::string& label, bool value) const
	{
		glUniform1i(glGetUniformLocation(this->ID, label.c_str()), (int)value);
	}

	void Shader::SetInt(const std::string& label, int value) const
	{
		glUniform1i(glGetUniformLocation(this->ID, label.c_str()), value);
	}

	void Shader::SetFloat(const std::string& label, float value) const
	{
		glUniform1f(glGetUniformLocation(this->ID, label.c_str()), value);
	}

	void Shader::SetVec2(const std::string& label, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(this->ID, label.c_str()), 1, &value[0]);
	}

	void Shader::SetXY(const std::string& label, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(this->ID, label.c_str()), x, y);
	}

	void Shader::SetVec3(const std::string& label, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(this->ID, label.c_str()), 1, &value[0]);
	}

	void Shader::SetXYZ(const std::string& label, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(this->ID, label.c_str()), x, y, z);
	}

	void Shader::SetVec4(const std::string& label, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(this->ID, label.c_str()), 1, &value[0]);
	}

	void Shader::SetXYZW(const std::string& label, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(this->ID, label.c_str()), x, y, z, w);
	}

	void Shader::SetMat2(const std::string& label, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(this->ID, label.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::SetMat3(const std::string& label, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(this->ID, label.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::SetMat4(const std::string& label, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(this->ID, label.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	bool Shader::CheckError(unsigned int shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];

		if(type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if(!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);

				#if DEBUG_LEVEL > 0
				Debug::cout << "[Shader]: Compilation error of type: " << type << "\n Info: " << infoLog;
				Debug::Log();
				#endif

				return true;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);

			if(!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
					
				#if DEBUG_LEVEL > 0
				Debug::cout << "[Shader]: Linking error of type: " << type << "\n Info: " << infoLog;
				Debug::Log();
				#endif
				return true;
			}
		}

		return false;
	}
}}
