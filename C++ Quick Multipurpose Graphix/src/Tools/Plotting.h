#pragma once

#include "../Graphics/Object/Mesh.h"

#include <functional>

namespace Plotting
{
	Mesh plotPoints(std::queue<float> pos, std::function<glm::vec4(glm::vec3)> colF);
	Mesh plotPoints(std::queue<glm::vec3> pos, std::function<glm::vec4(glm::vec3)> colF);

	Mesh plotRecurrence(glm::vec3 start, std::function<glm::vec3(glm::vec3)> f, uint64_t n, std::function<glm::vec4(glm::vec3)> colF);

	Mesh plotFunction(bool x, bool y, bool z, float xl, float xr, float yl, float yr, float zl, float zr, float xs, float ys, float zs, std::function<float(glm::vec2)> f, std::function<glm::vec4(glm::vec3)> colF);
}