#pragma once

#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Base {

	struct CameraInitialState
	{
		glm::vec3 position = glm::vec3(0.0f, 150.0f, 0.0f);

		float yaw = 0.0f, pitch = 0.0f, fov = 70.0f, aspectRaio = 16.0f/9.0f, zFar = 1000.0f, zNear = 0.1f;
	};

	enum class CameraMove
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};

	class Camera3D;

	typedef std::shared_ptr<Camera3D> Camera3DPtr;

	class Camera3D
	{
	private:
		glm::vec3 position, frontVec, rightVec, upVec;

		glm::mat4 projectionMatrix, viewMatrix;

		float yaw, pitch, fov, aspectRatio, zFar, zNear;

		static std::weak_ptr<Camera3D> current;
	public:
		Camera3D(const CameraInitialState& config = CameraInitialState());
		~Camera3D();

		void TranslateRelative(const CameraMove direction, const float velocity);
		void TranslateAbsolute(const CameraMove direction, const float velocity);

		void Rotate(const double yaw, const double pitch);
		void SetRotation(const double yaw, const double pitch);
		void SetRotation(const glm::vec3& front);

		void UpdateViewMatrix();
		void UpdateProjectionMatrix();
		void Update();

		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix() const;

		void SetPosition(const glm::vec3& position);
		glm::vec3 GetPosition() const;

		void SetYaw(const float yaw);
		float GetYaw() const;

		void SetPitch(const float pitch);
		float GetPitch() const;

		void SetZNear(const float zNear);
		float GetZNear() const;

		void SetZFar(const float zFar);
		float GetZFar() const;

		void SetFOV(const float fov);
		float GetFOV() const;

		void SetAspectRatio(const float aspect);
		float GetAspectRatio() const;

		glm::vec3 GetFront() const;
		glm::vec3 GetRight() const;
		glm::vec3 GetUp() const;

		static void SetCurrentCamera(const Camera3DPtr camera);
		static Camera3DPtr GetCurrentCamera();

		static glm::vec2 TransformFrontToPitchYaw(const glm::vec3& front);
	};
}}
