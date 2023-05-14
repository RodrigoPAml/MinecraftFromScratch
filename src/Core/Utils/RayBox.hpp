#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Core
{
	// Ray box tracer
	// Adapted from https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
	class RayBox
	{
	private:
		glm::vec3 orig, dir;

		glm::vec3 invdir;

		int sign[3];
	public:
		void SetOrig(const glm::vec3& orig)
		{
			this->orig = orig;
		}

		void SetDir(const glm::vec3& dir)
		{
			this->dir = dir;

			invdir = 1.0f/dir;

			sign[0] = (invdir.x < 0);
			sign[1] = (invdir.y < 0);
			sign[2] = (invdir.z < 0);
		}
			
		bool intersect(glm::vec3* bounds)
		{
			float tmin, tmax, tymin, tymax, tzmin, tzmax;

			tmin = (bounds[sign[0]].x - orig.x) * invdir.x;
			tmax = (bounds[1 - sign[0]].x - orig.x) * invdir.x;
			tymin = (bounds[sign[1]].y - orig.y) * invdir.y;
			tymax = (bounds[1 - sign[1]].y - orig.y) * invdir.y;

			if ((tmin > tymax) || (tymin > tmax))
				return false;
			if (tymin > tmin)
				tmin = tymin;
			if (tymax < tmax)
				tmax = tymax;

			tzmin = (bounds[sign[2]].z - orig.z) * invdir.z;
			tzmax = (bounds[1 - sign[2]].z - orig.z) * invdir.z;

			if ((tmin > tzmax) || (tzmin > tmax))
				return false;
			if (tzmin > tmin)
				tmin = tzmin;
			if (tzmax < tmax)
				tmax = tzmax;

			return true;
		}
	};
}}