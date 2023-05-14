#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Base { 

	typedef std::function<void(MouseButton, InputAction, InputModifier)> MouseButtonCallback;
	typedef std::function<void(glm::vec<2, int>)> MousePositionCallback;
	typedef std::function<void(float)> MouseScrollCallback;
	typedef std::function<void(bool)> MouseEnterWindowCallback;

	class Mouse
	{
		friend class Window;
	private:
		static MouseButtonCallback mouseButtonCallback;
		static MousePositionCallback mousePositionCallback;
		static MouseScrollCallback mouseScrollCallback;
		static MouseEnterWindowCallback mouseEnterWindowCallback;

		static glm::vec2 LastPosition;

		static float ScrollAcumulation;
		static float LastScroll;

		static bool EnterDisplay;

		static void MasterCursorEnterWindow(GLFWwindow* window, int entered);
		static void MasterCursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
		static void MasterMouseButtonCallback(GLFWwindow* window, int button, int action, int mod);
		static void MasterScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		static void Init();
		static void Release();
	public:
		static void SetMouseButtonCallback(MouseButtonCallback callback);

		static void SetMousePositionCallback(MousePositionCallback callback);

		static void SetMouseScrollCallback(MouseScrollCallback callback);

		static void SetMouseEnterWindowCallback(MouseEnterWindowCallback callback);

		static InputAction GetMouseButtonState(const MouseButton button);

		static glm::vec<2, int> GetMousePosition();

		static glm::vec2 GetMouseVariation();

		static void SetMouseMode(const MouseMode mode);

		static float GetScrollVariantion();

		static float GetScrollCumulativeVariation();

		static bool IsMouseInsideWindow();
	};
}}