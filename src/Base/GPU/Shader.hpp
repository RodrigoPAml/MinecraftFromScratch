#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Base {

	class Shader
	{
	private:
		static unsigned int currentID;

		unsigned int ID;

		static bool CheckError(unsigned int shader, std::string type);
	public:
		Shader(const std::string& verticeShader, const std::string& fragmentShader, const std::string& geometryShader, const bool fromFile = false);
		Shader();
		~Shader();

		bool isValid() const;
		void Active() const;

		static void ClearCurrentShader();

		void SetBool(const std::string& label, bool value) const;
		void SetInt(const std::string& label, int value) const;
		void SetFloat(const std::string& label, float value) const;
		void SetVec2(const std::string& label, const glm::vec2& value) const;
		void SetXY(const std::string& label, float x, float y) const;
		void SetVec3(const std::string& label, const glm::vec3& value) const;
		void SetXYZ(const std::string& label, float x, float y, float z) const;
		void SetVec4(const std::string& label, const glm::vec4& value) const;
		void SetXYZW(const std::string& label, float x, float y, float z, float w) const;
		void SetMat2(const std::string& label, const glm::mat2& mat) const;
		void SetMat3(const std::string& label, const glm::mat3& mat) const;
		void SetMat4(const std::string& label, const glm::mat4& mat) const;
	};

	typedef std::shared_ptr<Shader> ShaderPtr;
}}