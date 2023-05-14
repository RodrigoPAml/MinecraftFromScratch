#pragma once

#include <BuildCraft.hpp>

// If defined will print any logs in the console
#define DEBUG_COUT

// Define if a Debug::cout will be considered in compilation. Should use 1,2,3 (Low, Medium, High) notifications importance.
// Only print if DEBUG_COUT is defined
#define DEBUG_LEVEL 1

// If will GLFW debug errors with callback error.
#define DEBUG_GLFW_CALLBACK

// Enable callback for erros/warnings for OpenGL
// Only print if DEBUG_COUT is defined
//#define DEBUG_CALLBACK_LEVEL_NOTIFICATION
//#define DEBUG_CALLBACK_LEVEL_LOW
//#define DEBUG_CALLBACK_LEVEL_MEDIUM
//#define DEBUG_CALLBACK_LEVEL_HIGH

#if defined(DEBUG_CALLBACK_LEVEL_NOTIFICATION) || defined(DEBUG_CALLBACK_LEVEL_LOW) || defined(DEBUG_CALLBACK_LEVEL_MEDIUM) || defined(DEBUG_CALLBACK_LEVEL_HIGH)
#define DEBUG_CALLBACK_ENABLE 
#endif

namespace BuildCraft {
namespace Base {

	enum class GLFWError
	{
		NO_ERROR = GLFW_NO_ERROR,
		API_UNAVAILABLE = GLFW_API_UNAVAILABLE,
		FORMAT_UNAVAILABLE = GLFW_FORMAT_UNAVAILABLE,
		INVALID_ENUM = GLFW_INVALID_ENUM,
		INVALID_VALUE = GLFW_INVALID_VALUE,
		NO_CURRENT_CONTEXT = GLFW_NO_CURRENT_CONTEXT,
		NOT_INITIALIZED = GLFW_NOT_INITIALIZED,
		OUT_OF_MEMORY = GLFW_OUT_OF_MEMORY,
		PLATFORM_ERROR = GLFW_PLATFORM_ERROR,
		VERSION_UNAVAILABLE = GLFW_VERSION_UNAVAILABLE
	};

	enum class OpenGLError
	{
		NO_ERROR = GL_NO_ERROR,
		INVALID_ENUM = GL_INVALID_ENUM,
		INVALID_VALUE = GL_INVALID_VALUE,
		INVALID_OPERATION = GL_INVALID_OPERATION,
		STACK_OVERFLOW = GL_STACK_OVERFLOW,
		STACK_UNDERFLOW = GL_STACK_UNDERFLOW,
		OUT_OF_MEMORY = GL_OUT_OF_MEMORY,
		INVALID_FRAMEBUFFER_OPERATION = GL_INVALID_FRAMEBUFFER_OPERATION,
		CONTEXT_LOST = GL_CONTEXT_LOST,
		TABLE_TOO_LARGE = GL_TABLE_TOO_LARGE,
	};

	enum class OpenGLErrorSource
	{
		SOURCE_API = GL_DEBUG_SOURCE_API,
		SOURCE_WINDOW_SYSTEM = GL_DEBUG_SOURCE_WINDOW_SYSTEM,
		SOURCE_SHADER_COMPILER = GL_DEBUG_SOURCE_SHADER_COMPILER,
		SOURCE_THIRD_PARTY = GL_DEBUG_SOURCE_THIRD_PARTY,
		SOURCE_APPLICATION = GL_DEBUG_SOURCE_APPLICATION,
		SOURCE_OTHER = GL_DEBUG_SOURCE_OTHER
	};

	enum class OpenGLErrorType
	{
		TYPE_ERROR = GL_DEBUG_TYPE_ERROR,
		TYPE_DEPRECATED_BEHAVIOR = GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR,
		TYPE_UNDEFINED_BEHAVIOR = GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR,
		TYPE_PORTABILITY = GL_DEBUG_TYPE_PORTABILITY,
		TYPE_PERFORMANCE = GL_DEBUG_TYPE_PERFORMANCE,
		TYPE_MARKER = GL_DEBUG_TYPE_MARKER,
		TYPE_PUSH_GROUP = GL_DEBUG_TYPE_PUSH_GROUP,
		TYPE_POP_GROUP = GL_DEBUG_TYPE_POP_GROUP,
		TYPE_OTHER = GL_DEBUG_TYPE_OTHER
	};

	enum class OpenGLErrorSeverity
	{
		SEVERITY_HIGH = GL_DEBUG_SEVERITY_HIGH,
		SEVERITY_MEDIUM = GL_DEBUG_SEVERITY_MEDIUM,
		SEVERITY_LOW = GL_DEBUG_SEVERITY_LOW,
		SEVERITY_NOTIFICATION = GL_DEBUG_SEVERITY_NOTIFICATION,
	};

	class Debug
	{
	private:
		static std::vector<std::string> logs;
	public:
		static std::ostringstream cout;

		static void Log();

		static void ClearLogs();

		static std::vector<std::string> GetLogs(const int numberOfLogs);

		static std::string ErrorToString(const OpenGLError error);

		static std::string ErrorToString(const GLFWError error);

		static std::string ErrorToString(const OpenGLErrorSource error);

		static std::string ErrorToString(const OpenGLErrorType error);

		static std::string ErrorToString(const OpenGLErrorSeverity error);

		static GLFWError GetGLFWError(std::string& errorMsg);

		static OpenGLError GetOpenGLError();
	};
}}