
#include "../../Tools/Plotting.h"

#include <time.h>

glm::vec3 BFernR(glm::vec3 pos)
{
	glm::vec2 tpos(pos.x, pos.y);

	int r = rand() % 10000;
	if (r < 100)
	{
		float f[4] = { 0.00, 0.00, 0.00, 0.16 };
		tpos = glm::make_mat2(f) * tpos;
		return glm::vec3(tpos.x, tpos.y, pos.z);
	}
	else if (r < 8600)
	{
		float f[4] = { 0.85, -0.04, 0.04, 0.85 };
		tpos = glm::make_mat2(f) * tpos + glm::vec2(0.00, 1.60);
		return glm::vec3(tpos.x, tpos.y, pos.z);
	}
	else if (r < 9300)
	{
		float f[4] = { 0.20, 0.23, -0.26, 0.22 };
		tpos = glm::make_mat2(f) * tpos + glm::vec2(0.00, 1.60);
		return glm::vec3(tpos.x, tpos.y, pos.z);
	}
	float f[4] = { -0.15, 0.26, 0.28, 0.24 };
	tpos = glm::make_mat2(f) * tpos + glm::vec2(0.00, 0.44);
	return glm::vec3(tpos.x, tpos.y, pos.z);
}