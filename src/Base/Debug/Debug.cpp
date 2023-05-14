#include <BuildCraft.hpp>
#include "Debug.hpp"

namespace BuildCraft {
namespace Base {

	std::vector<std::string> Debug::logs;

	std::ostringstream Debug::cout;

	void Debug::Log()
	{
		#ifdef DEBUG_COUT
		std::cout << cout.str() << std::endl;
		#endif

		logs.push_back(cout.str());
		
		if(logs.size() > 200)
		{
			logs.erase(logs.begin(), logs.begin() + 100);
		}

		cout.str("");
	}

	void Debug::ClearLogs()
	{
		logs.clear();
		cout.str("");
	}

	std::vector<std::string> Debug::GetLogs(const int numberOfLogs)
	{
		const int size = std::min(numberOfLogs, (int)logs.size());

		std::vector<std::string> logList;

		for(int i = 0; i < size; i++)
		{
			logList.push_back(logs[i]);
		}

		return logList;
	}

	std::string Debug::ErrorToString(const OpenGLError error)
	{
		switch(error)
		{
		case OpenGLError::NO_ERROR:
			return "NO_ERROR";
			break;
		case OpenGLError::INVALID_ENUM:
			return "INVALID_ENUM";
			break;
		case OpenGLError::INVALID_VALUE:
			return "INVALID_VALUE";
			break;
		case OpenGLError::INVALID_OPERATION:
			return "INVALID_OPERATION";
			break;
		case OpenGLError::STACK_OVERFLOW:
			return "STACK_OVERFLOW";
			break;
		case OpenGLError::STACK_UNDERFLOW:
			return "STACK_UNDERFLOW";
			break;
		case OpenGLError::OUT_OF_MEMORY:
			return "OUT_OF_MEMORY";
			break;
		case OpenGLError::INVALID_FRAMEBUFFER_OPERATION:
			return "INVALID_FRAMEBUFFER_OPERATION";
			break;
		default:
			return "?";
			break;
		}

		return "?";
	}

	std::string Debug::ErrorToString(const GLFWError error)
	{
		switch(error)
		{
		case GLFWError::NO_ERROR:
			return "NO_ERROR";
			break;
		case GLFWError::API_UNAVAILABLE:
			return "API_UNAVAILABLE";
			break;
		case GLFWError::FORMAT_UNAVAILABLE:
			return "FORMAT_UNAVAILABLE";
			break;
		case GLFWError::INVALID_ENUM:
			return "INVALID_ENUM";
			break;
		case GLFWError::INVALID_VALUE:
			return "INVALID_VALUE";
			break;
		case GLFWError::NO_CURRENT_CONTEXT:
			return "NO_CURRENT_CONTEXT";
			break;
		case GLFWError::NOT_INITIALIZED:
			return "NOT_INITIALIZED";
			break;
		case GLFWError::OUT_OF_MEMORY:
			return "OUT_OF_MEMORY";
			break;
		case GLFWError::PLATFORM_ERROR:
			return "PLATFORM_ERROR";
			break;
		case GLFWError::VERSION_UNAVAILABLE:
			return "VERSION_UNAVAILABLE";
			break;
		default:
			return "?";
			break;
		}

		return "?";
	}

	std::string Debug::ErrorToString(const OpenGLErrorSource error)
	{
		switch(error)
		{
		case OpenGLErrorSource::SOURCE_API:
			return "SOURCE_API";
			break;
		case OpenGLErrorSource::SOURCE_WINDOW_SYSTEM:
			return "SOURCE_WINDOW_SYSTEM";
			break;
		case OpenGLErrorSource::SOURCE_SHADER_COMPILER:
			return "SOURCE_SHADER_COMPILER";
			break;
		case OpenGLErrorSource::SOURCE_THIRD_PARTY:
			return "SOURCE_THIRD_PARTY";
			break;
		case OpenGLErrorSource::SOURCE_APPLICATION:
			return "SOURCE_APPLICATION";
			break;
		case OpenGLErrorSource::SOURCE_OTHER:
			return "SOURCE_OTHER";
			break;
		default:
			return "?";
			break;
		}

		return "?";
	}

	std::string Debug::ErrorToString(const OpenGLErrorType error)
	{
		switch(error)
		{
		case OpenGLErrorType::TYPE_ERROR:
			return "TYPE_ERROR";
			break;
		case OpenGLErrorType::TYPE_DEPRECATED_BEHAVIOR:
			return "TYPE_DEPRECATED_BEHAVIOR";
			break;
		case OpenGLErrorType::TYPE_UNDEFINED_BEHAVIOR:
			return "TYPE_UNDEFINED_BEHAVIOR";
			break;
		case OpenGLErrorType::TYPE_PORTABILITY:
			return "TYPE_PORTABILITY";
			break;
		case OpenGLErrorType::TYPE_PERFORMANCE:
			return "TYPE_PERFORMANCE";
			break;
		case OpenGLErrorType::TYPE_MARKER:
			return "TYPE_MARKER";
			break;
		case OpenGLErrorType::TYPE_PUSH_GROUP:
			return "TYPE_PUSH_GROUP";
			break;
		case OpenGLErrorType::TYPE_POP_GROUP:
			return "TYPE_POP_GROUP";
			break;
		case OpenGLErrorType::TYPE_OTHER:
			return "TYPE_OTHER";
			break;
		default:
			return "?";
			break;
		}

		return "?";
	}

	std::string Debug::ErrorToString(const OpenGLErrorSeverity error)
	{
		switch(error)
		{
		case OpenGLErrorSeverity::SEVERITY_HIGH:
			return "SEVERITY_HIGH";
			break;
		case OpenGLErrorSeverity::SEVERITY_MEDIUM:
			return "SEVERITY_MEDIUM";
			break;
		case OpenGLErrorSeverity::SEVERITY_LOW:
			return "SEVERITY_LOW";
			break;
		case OpenGLErrorSeverity::SEVERITY_NOTIFICATION:
			return "SEVERITY_NOTIFICATION";
			break;
		default:
			return "?";
			break;
		}

		return "?";
	}

	GLFWError Debug::GetGLFWError(std::string& errorMsg)
	{
		const char* description;

		GLFWError error = (GLFWError)glfwGetError(&description);

		if(description)
		{
			errorMsg = description;
		}

		return error;
	}

	OpenGLError Debug::GetOpenGLError()
	{
		return (OpenGLError)glGetError();
	}
}}