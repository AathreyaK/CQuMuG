#include "Plotting.h"

Mesh Plotting::plotPoints(std::queue<float> pos, std::function<glm::vec4(glm::vec3)> colF)
{
	std::queue<float> cols;
	std::queue<float> temp = pos;
	while (!temp.empty())
	{
		float a, b, c;
		a = temp.front(); temp.pop();
		b = temp.front(); temp.pop();
		c = temp.front(); temp.pop();
		glm::vec4 col = colF(glm::vec3(a, b, c));
		for (int i = 0; i < 4; i++)
			cols.push(col[i]);
	}
	return Mesh(pos, cols, std::vector<int>(), CQUMUG_MESH_3D, 0, 1);
}

Mesh Plotting::plotPoints(std::queue<glm::vec3> pos, std::function<glm::vec4(glm::vec3)> colF)
{
	std::queue<float> poss;
	std::queue<float> cols;
	while (!pos.empty())
	{
		poss.push(pos.front().x);
		poss.push(pos.front().y);
		poss.push(pos.front().z);

		glm::vec4 col = colF(pos.front());
		cols.push(col.x);
		cols.push(col.y);
		cols.push(col.z);
		cols.push(col.w);

		pos.pop();
	}
	return Mesh(poss, cols, std::vector<int>(), CQUMUG_MESH_3D, 0, 1);
}

Mesh Plotting::plotRecurrence(glm::vec3 start, std::function<glm::vec3(glm::vec3)> f, uint64_t n, std::function<glm::vec4(glm::vec3)> colF)
{
	std::queue<float> p;
	std::queue<float> c;

	for (uint64_t i = 0; i < n; i++)
	{
		p.push(start.x);
		p.push(start.y);
		p.push(start.z);

		glm::vec4 col = colF(start);
		c.push(col.x);
		c.push(col.y);
		c.push(col.z);
		c.push(col.w);

		start = f(start); 
	}
	return Mesh(p, c, std::vector<int>(), CQUMUG_MESH_3D, 0, 1);
}

Mesh Plotting::plotFunction(bool x, bool y, bool z, float xl, float xr, float yl, float yr, float zl, float zr, float xs, float ys, float zs, std::function<float(glm::vec2)> f, std::function<glm::vec4(glm::vec3)> colF) // mark the function of the other with true (x(y, z)) would be (true, false, false)
{
	std::queue<float> p;
	std::queue<float> c;
	if (x)
	{
		for (float i = yl; i < yr; i += ys)
		{
			for (float j = zl; j < zr; j += zs)
			{
				float v = f(glm::vec2(i, j));
				p.push(v);
				p.push(i);
				p.push(j);

				glm::vec4 col = colF(glm::vec3(v, i, j));
				c.push(col.x);
				c.push(col.y);
				c.push(col.z);
				c.push(col.w);
			}
		}
	}
	else if (y)
	{
		for (float i = xl; i < xr; i += xs)
		{
			for (float j = zl; j < zr; j += zs)
			{
				float v = f(glm::vec2(i, j));
				p.push(i);
				p.push(v);
				p.push(j);

				glm::vec4 col = colF(glm::vec3(i, v, j));
				c.push(col.x);
				c.push(col.y);
				c.push(col.z);
				c.push(col.w);
			}
		}
	}
	else
	{
		for (float i = xl; i < xr; i += xs)
		{
			for (float j = yl; j < yr; j += ys)
			{
				float v = f(glm::vec2(i, j));
				p.push(i);
				p.push(j);
				p.push(v);

				glm::vec4 col = colF(glm::vec3(i, j, v));
				c.push(col.x);
				c.push(col.y);
				c.push(col.z);
				c.push(col.w);
			}
		}
	}

	// TODO: Make indices to make draw the surfaces in squares

	return Mesh(p, c, std::vector<int>(), CQUMUG_MESH_3D, 0, 1);
}