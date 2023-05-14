#pragma once

#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Base {

	class Camera2D;

	typedef std::shared_ptr<Camera2D> Camera2DPtr;

	class Camera2D
	{
	private:
		float l, r, t, b, znear, zfar;

		glm::mat4 projectionMatrix;

		static std::weak_ptr<Camera2D> current;
	public:
		Camera2D(const float l = 0, const float r = 800, const float t = 600, const float b = 0, const float znear = 0.0f, const float zfar = 20.0f);

		glm::mat4 GetProjectionMatrix() const;

		void Update();

		void SetLeft(const float l);
		void SetRight(const float r);
		void SetTop(const float t);
		void SetBottom(const float b);
		void SetZNear(const float znear);
		void SetZFar(const float zfar);

		float GetLeft() const;
		float GetRight() const;
		float GetTop() const;
		float GetBottom() const;
		float GetZNear() const;
		float GetZFar() const;

		static Camera2DPtr GetCurrentCamera();
		static void SetCurrentCamera(Camera2DPtr camera);
	};
}}	