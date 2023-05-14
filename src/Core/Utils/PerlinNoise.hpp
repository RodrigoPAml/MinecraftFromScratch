#pragma once
#include <BuildCraft.hpp>

namespace BuildCraft {
namespace Core {

	/// <summary>
	/// Perlin noise generator using db perlin
	/// </summary>
	class PerlinNoise
	{
	private:
		unsigned int octaves = 4;
	public:
		void SetOctaves(unsigned int octaves)
		{
			this->octaves = octaves;
		}

		unsigned int GetOctaves() const
		{
			return this->octaves;
		}

		float GetNoise(float x, float y)
		{
			float scalar = 1.0f;
			int divider = 1;
			float noise = 0.0f;
			float normalizer = 0.0f;

			for(int i = 0; i < octaves; i++)
			{
				noise += scalar * db::perlin( (divider * x)/64.0f, (divider * y)/64.0f);

				normalizer += scalar;
				scalar = scalar*0.5f;
				divider = divider*2;
			}

			return noise/normalizer;
		}
	};
}}