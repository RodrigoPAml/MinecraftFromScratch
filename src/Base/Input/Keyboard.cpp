#include <BuildCraft.hpp>
#include "Keyboard.hpp"

namespace BuildCraft {
namespace Base {

	KeyboardCallback Keyboard::callback = nullptr;

	std::set<KeyboardKey> Keyboard::frameClickedKeys;

	void Keyboard::MasterKeyboardEventCallback(GLFWwindow* window, int key, int scancode, int action, int mod)
	{
		if((InputAction)action == InputAction::REPEAT) Keyboard::frameClickedKeys.insert((KeyboardKey)key);
		else if((InputAction)action == InputAction::RELEASE) Keyboard::frameClickedKeys.erase((KeyboardKey)key);

		if(Keyboard::callback != nullptr) Keyboard::callback((KeyboardKey)key, (InputAction)action, (InputModifier)mod);
	}

	void Keyboard::Init()
	{
		glfwSetKeyCallback(Window::windowPtr, MasterKeyboardEventCallback);

		Debug::cout << "[Keyboard]: Initialized";
		Debug::Log();
	}

	void Keyboard::Release()
	{
		glfwSetKeyCallback(Window::windowPtr, nullptr);
		callback = nullptr;
		frameClickedKeys.clear();

		Debug::cout << "[Keyboard]: Released";
		Debug::Log();
	}

	void Keyboard::RegisterKeyboardEventCallback(const KeyboardCallback callback)
	{
		Keyboard::callback = callback;
	}

	InputAction Keyboard::GetKeyState(const KeyboardKey key)
	{
		if(Keyboard::frameClickedKeys.find(key) != Keyboard::frameClickedKeys.end())
		{
			return InputAction::REPEAT;
		}

		return (InputAction)glfwGetKey(Window::windowPtr, (int)key);
	}
}}
