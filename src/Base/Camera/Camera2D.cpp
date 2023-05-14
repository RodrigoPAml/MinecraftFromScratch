#include <BuildCraft.hpp>
#include "Camera2D.hpp"

namespace BuildCraft {
namespace Base {

	std::weak_ptr<Camera2D> Camera2D::current;

	Camera2D::Camera2D(const float l, const float r, const float t, const float b, const float znear, const float zfar)
	{
		this->l = l;
		this->r = r;
		this->t = t;
		this->b = b;
		this->znear = znear;
		this->zfar = zfar;

		this->projectionMatrix = glm::ortho<float>(this->l, this->r, this->b, this->t);
	}

	glm::mat4 Camera2D::GetProjectionMatrix() const
	{
		return this->projectionMatrix;
	}

	void Camera2D::Update()
	{
		this->projectionMatrix = glm::ortho<float>(this->l, this->r, this->b, this->t);
	}

	void Camera2D::SetLeft(const float l)
	{
		this->l = l;
	}

	void Camera2D::SetRight(const float r)
	{
		this->r = r;
	}

	void Camera2D::SetTop(const float t)
	{
		this->t = t;
	}

	void Camera2D::SetBottom(const float b)
	{
		this->b = b;
	}

	void Camera2D::SetZNear(const float znear)
	{
		this->znear = znear;
	}

	void Camera2D::SetZFar(const float zfar)
	{
		this->zfar = zfar;
	}

	float Camera2D::GetLeft() const
	{
		return this->l;
	}

	float Camera2D::GetRight() const
	{
		return this->r;
	}

	float Camera2D::GetTop() const
	{
		return this->t;
	}

	float Camera2D::GetBottom() const
	{
		return this->b;
	}

	float Camera2D::GetZNear() const
	{
		return this->znear;
	}

	float Camera2D::GetZFar() const
	{
		return this->zfar;
	}

	Camera2DPtr Camera2D::GetCurrentCamera()
	{
		if(Camera2D::current.expired())
		{
			return nullptr;
		}
		else
		{
			return Camera2D::current.lock();
		}
	}

	void Camera2D::SetCurrentCamera(Camera2DPtr camera)
	{
		Camera2D::current = camera;
	}
}}
