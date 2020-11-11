#pragma once

#include <include/glm.h>

namespace Transformations
{
	// Translate matrix
	inline glm::mat3 Translate(float translateX, float translateY)
	{
		return glm::mat3(
			1.f, 0.f, 0.f,
			0.f, 1.f, 0.f,
			translateX, translateY, 1.f
		);
	}

	// Scale matrix
	inline glm::mat3 Scale(float scaleX, float scaleY)
	{
		return glm::mat3(
			scaleX, 0.f, 0.f,
			0.f, scaleY, 0.f,
			0.f, 0.f, 1.f
		);
	}

	// Rotate matrix
	inline glm::mat3 Rotate(float radians)
	{
		float co = cos(radians), si = sin(radians);

		return glm::mat3(
			co, si, 0.f,
			-si, co, 0.f,
			0.f, 0.f, 1.f
		);
	}
}
