#include <BuildCraft.hpp>
#include "Mouse.hpp"

namespace BuildCraft {
namespace Base {

	MouseButtonCallback Mouse::mouseButtonCallback = nullptr;
	MousePositionCallback Mouse::mousePositionCallback = nullptr;
	MouseScrollCallback Mouse::mouseScrollCallback = nullptr;
	MouseEnterWindowCallback Mouse::mouseEnterWindowCallback = nullptr;

	glm::vec2 Mouse::LastPosition;

	float Mouse::ScrollAcumulation = 0;
	float Mouse::LastScroll = 0;

	bool Mouse::EnterDisplay = true;

	void Mouse::MasterCursorEnterWindow(GLFWwindow* window, int entered)
	{
		Mouse::EnterDisplay = (bool)entered;

		if(Mouse::mouseEnterWindowCallback != nullptr) Mouse::mouseEnterWindowCallback((bool)entered);
	}

	void Mouse::MasterCursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		if(Mouse::mousePositionCallback != nullptr) Mouse::mousePositionCallback({xpos, ypos});
	}

	void Mouse::MasterMouseButtonCallback(GLFWwindow* window, int button, int action, int mod)
	{
		if(Mouse::mouseButtonCallback != nullptr) Mouse::mouseButtonCallback((MouseButton)button, (InputAction)action, (InputModifier)mod);
	}

	void Mouse::MasterScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Mouse::LastScroll = yoffset;
		Mouse::ScrollAcumulation += yoffset;

		if(Mouse::mouseScrollCallback != nullptr) Mouse::mouseScrollCallback(yoffset);
	}

	void Mouse::Init()
	{
		glfwSetScrollCallback(Window::windowPtr, MasterScrollCallback);
		glfwSetCursorEnterCallback(Window::windowPtr, MasterCursorEnterWindow);

		#if DEBUG_LEVEL > 0
		Debug::cout << "[Mouse]: Initialized";
		Debug::Log();
		#endif		
	}

	void Mouse::Release()
	{
		glfwSetScrollCallback(Window::windowPtr, nullptr);
		glfwSetCursorEnterCallback(Window::windowPtr, nullptr);
		glfwSetCursorPosCallback(Window::windowPtr, nullptr);
		glfwSetMouseButtonCallback(Window::windowPtr, nullptr);

		mouseButtonCallback = nullptr;
		mousePositionCallback = nullptr;
		mouseScrollCallback = nullptr;
		mouseEnterWindowCallback = nullptr;

		LastPosition = {0.0f, 0.0f};
		ScrollAcumulation = 0;
		LastScroll = 0;
		EnterDisplay = true;

		#if DEBUG_LEVEL > 0
		Debug::cout << "[Mouse]: Released";
		Debug::Log();
		#endif
	}

	void Mouse::SetMouseButtonCallback(MouseButtonCallback callback)
	{
		Mouse::mouseButtonCallback = callback;

		glfwSetMouseButtonCallback(Window::windowPtr, MasterMouseButtonCallback);
	}

	void Mouse::SetMousePositionCallback(MousePositionCallback callback)
	{
		Mouse::mousePositionCallback = callback;

		glfwSetCursorPosCallback(Window::windowPtr, MasterCursorPositionCallback);
	}

	void Mouse::SetMouseScrollCallback(MouseScrollCallback callback)
	{
		Mouse::mouseScrollCallback = callback;
	}

	void Mouse::SetMouseEnterWindowCallback(MouseEnterWindowCallback callback)
	{
		Mouse::mouseEnterWindowCallback = callback;
	}

	InputAction Mouse::GetMouseButtonState(const MouseButton button)
	{
		return (InputAction)glfwGetMouseButton(Window::windowPtr, (int)button);
	}

	glm::vec<2, int> Mouse::GetMousePosition()
	{
		double xpos, ypos;
		glfwGetCursorPos(Window::windowPtr, &xpos, &ypos);

		return {xpos, ypos};
	}

	glm::vec2 Mouse::GetMouseVariation()
	{
		return Mouse::LastPosition - glm::vec2(Mouse::GetMousePosition().x, Mouse::GetMousePosition().y);
	}

	void Mouse::SetMouseMode(const MouseMode mode)
	{
		glfwSetInputMode(Window::windowPtr, GLFW_CURSOR, (int)mode);
	}

	float Mouse::GetScrollVariantion()
	{
		return Mouse::LastScroll;
	}

	float Mouse::GetScrollCumulativeVariation()
	{
		return Mouse::ScrollAcumulation;
	}

	bool Mouse::IsMouseInsideWindow()
	{
		return Mouse::EnterDisplay;
	}
}}
