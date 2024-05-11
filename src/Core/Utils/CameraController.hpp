#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Core {

	/// <summary>
	/// Controls the camera movement
	/// </summary>
	class CameraController
	{
	public:
		void ControllCurrentCamera(float speed)
		{
			using namespace BuildCraft::Base;

			Camera3DPtr cam = Camera3D::GetCurrentCamera();

			if(cam == nullptr)
				return;

			if(Keyboard::GetKeyState(KeyboardKey::KEY_W) >= InputAction::PRESS)
				cam->TranslateRelative(CameraMove::FORWARD, speed);
			if(Keyboard::GetKeyState(KeyboardKey::KEY_S) >= InputAction::PRESS)
				cam->TranslateRelative(CameraMove::BACKWARD, speed);
			if(Keyboard::GetKeyState(KeyboardKey::KEY_D) >= InputAction::PRESS)
				cam->TranslateRelative(CameraMove::RIGHT, speed);
			if(Keyboard::GetKeyState(KeyboardKey::KEY_A) >= InputAction::PRESS)
				cam->TranslateRelative(CameraMove::LEFT, speed);

			if (Keyboard::GetKeyState(KeyboardKey::KEY_UP) >= InputAction::PRESS)
				cam->TranslateRelative(CameraMove::FORWARD, speed);
			if (Keyboard::GetKeyState(KeyboardKey::KEY_DOWN) >= InputAction::PRESS)
				cam->TranslateRelative(CameraMove::BACKWARD, speed);
			if (Keyboard::GetKeyState(KeyboardKey::KEY_RIGHT) >= InputAction::PRESS)
				cam->TranslateRelative(CameraMove::RIGHT, speed);
			if (Keyboard::GetKeyState(KeyboardKey::KEY_LEFT) >= InputAction::PRESS)
				cam->TranslateRelative(CameraMove::LEFT, speed);

			if(Mouse::GetMouseButtonState(MouseButton::MOUSE_BUTTON_LEFT) == InputAction::PRESS)
				cam->Rotate(-Mouse::GetMouseVariation().x, Mouse::GetMouseVariation().y);

			cam->Update();
		}
	};
}}