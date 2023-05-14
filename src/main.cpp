#include "BuildCraft.hpp"

using namespace BuildCraft::Base;
using namespace BuildCraft::Core;

int main()
{
	srand(time(NULL));

	Window::Create();

	Command::EnableVSync();
	Command::EnableDepthTesting();
	Command::SetPrimitivePointSize(3);

	Primitives2D::Initialize();
	Primitives3D::Initialize();

    Camera2DPtr cam2d = Camera2DPtr(new Camera2D());
    Camera2D::SetCurrentCamera(cam2d);
	GUI::Initiatlize();

	Camera3DPtr cam3d = Camera3DPtr(new Camera3D());
	Camera3D::SetCurrentCamera(cam3d);
	cam3d->SetPosition({ 10000, 0, 10000 });

	CameraController controller;

	Terrain t = Terrain(10);
	Framebuffer::SetClearModes({ ClearMode::COLOR, ClearMode::DEPTH });
	float speed = 1.0f;

	while(Window::ShouldRun())
	{
		controller.ControllCurrentCamera(speed);

		Framebuffer::SwitchViewPort({0, 0}, Window::GetSize());
		Framebuffer::ClearCurrentFrameBuffer({0.6f, 0.7f, 1.0f, 1.0f});

		cam2d->SetLeft(0);
		cam2d->SetRight(Window::GetSize().x);
		cam2d->SetBottom(0);
		cam2d->SetTop(Window::GetSize().y);
		cam2d->Update();

		// Create and delete chunks max iterations
		t.DrawTerrain(1000, 1000);

		GUI::InitFrame();

		if (GUI::BeginWindow("Menu"))
		{
			GUI::MakeBulletText("Speed");
			GUI::ContinueSameLine();
			GUI::MakeSlider("speed", 0, 5, speed);
			
			bool& walkMode = t.GetWalkMode();
			bool& eraseMode = t.GetEraseMode();

			if(walkMode)
				GUI::MakeSelectable("Trocar para camera livre", walkMode);
			else
				GUI::MakeSelectable("Trocar para camera caminhada", walkMode);

			if (!eraseMode)
				GUI::MakeSelectable("Trocar para modo adicionar bloco", eraseMode);
			else
				GUI::MakeSelectable("Trocar para modo remover bloco", eraseMode);

			if (GUI::MakeButton("Bloco de madeira"))
				t.SetCurrentBlock({ 14, 21 });
			if (GUI::MakeButton("Bloco de pedra"))
				t.SetCurrentBlock({ 15, 19 });
			if(GUI::MakeButton("Bloco de grama"))
				t.SetCurrentBlock({ 15, 2 });
			if(GUI::MakeButton("Bloco de tijolo"))
				t.SetCurrentBlock({ 14, 29 });

			GUI::EndWindow();
		}

		GUI::EndFrame();
		
		Window::SwapAndPollEvents();
	}

	Window::Destroy();

	return 0;
}
