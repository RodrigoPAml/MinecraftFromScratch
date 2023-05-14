#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Base {

	typedef std::function<void(KeyboardKey, InputAction, InputModifier)> KeyboardCallback;

	class Keyboard
	{
		friend class Window;
	private:
		static KeyboardCallback callback;

		static std::set<KeyboardKey> frameClickedKeys;

		static void MasterKeyboardEventCallback(GLFWwindow* window, int key, int scancode, int action, int mod);

		static void Init();
		static void Release();
	public:
		static void RegisterKeyboardEventCallback(const KeyboardCallback callback);

		static InputAction GetKeyState(const KeyboardKey key);
	};
}}

