#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Base {

	struct WindowConfig
	{
		std::string windowName = "Minecraft de pobre";

		glm::vec2 windowPosition = {40, 40}, windowSize = {800, 600};

		std::uint8_t windowMSAA = 8;

		unsigned int OpenGLVersionMin = 3;
		unsigned int OpenGLVersionMax = 4;
	};

	typedef std::function<void(glm::vec<2, int>)> ResizeWindowCallback;
	typedef std::function<void(glm::vec<2, int>)> RepositionWindowCallback;
	typedef std::function<void(bool)> MaximizeWindowCallback;
	typedef std::function<void(bool)> MinimizeWindowCallback;
	typedef std::function<void(bool)> FocusWindowCallback;
	typedef std::function<void(void)> CloseWindowCallback;

	/// <summary>
	/// Manage the window
	/// </summary>
	class Window
	{
		friend class Keyboard;
		friend class Mouse;
	private:
		static GLFWwindow* windowPtr;

		static ResizeWindowCallback resizeWindowCallback;
		static RepositionWindowCallback repositionWindowCallback;
		static MaximizeWindowCallback maximizeWindowCallback;
		static MinimizeWindowCallback minimizeWindowCallback;
		static CloseWindowCallback closeWindowCallback;
		static FocusWindowCallback focusWindowCallback;

		static WindowConfig config;

		static bool _isInit;
		static bool _isMinimized;
		static bool _isFullscreen;
		static bool _isHide;
		static bool _isFocus;

		static void WindowResizeCallback(GLFWwindow* window, int width, int height);
		static void WindowCloseCallback(GLFWwindow* window);
		static void WindowPositionCallback(GLFWwindow* window, int xpos, int ypos);
		static void WindowMaximizeCallback(GLFWwindow* window, int maximized);
		static void WindowMinimizeCallback(GLFWwindow* window, int maximized);
		static void WindowFocusCallback(GLFWwindow* window, int focused);
	public:
		static bool Create(const WindowConfig& config = WindowConfig());
		static void Destroy();

		static bool ShouldRun();

		static void Resize(const glm::vec2& newSize);
		static glm::vec2 GetSize();

		static void SetPosition(const glm::vec2& pos);
		static glm::vec2 GetPosition();

		static std::string GetName();
		static void SetName(const std::string& title);

		static void SetFullscreen();
		static void RemoveFullscreen(const glm::vec2& newSize, const glm::vec2& newPos);

		static void Hide();
		static void Show();

		static void Maximize();
		static void Minimize();
		static void Restore();
		static void Close();

		static void RequestAttention();
		static void SwapAndPollEvents();

		static void SetResizeWindowCallback(const ResizeWindowCallback callback);
		static void SetRepositionWindowCallback(const RepositionWindowCallback callback);
		static void SetMaximizeWindowCallback(const MaximizeWindowCallback callback);
		static void SetMinimizeWindowCallback(const MinimizeWindowCallback callback);
		static void SetCloseWindowCallback(const CloseWindowCallback callback);
		static void SetFocusWindowCallback(const FocusWindowCallback callback);

		static bool isMinimized();
		static bool isHide();
		static bool isFullscreen();
		static bool isInFocus();

		static bool SetIcon(const ReadableTexturePtr texture);
		static glm::vec2 GetScreenLimits();

		static GLFWwindow* GetWindowPtr();
	};
}}
