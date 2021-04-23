#include "Plotting.h"

Mesh Plotting::plot2DPoints(std::queue<float> pos, std::function<glm::vec4(glm::vec2)> colF) // I'm p sure this is deffective, the pos thing should be stored in triples
{
	std::queue<float> cols;
	std::queue<float> temp = pos;
	while (!temp.empty())
	{
		float a, b;
		a = temp.front(); temp.pop();
		b = temp.front(); temp.pop();
		glm::vec4 col = colF(glm::vec2(a, b));
		for (int i = 0; i < 4; i++)
			cols.push(col[i]);
	}
	return Mesh(pos, cols, std::vector<int>(), CQUMUG_MESH_3D, 0, 1);
}

Mesh Plotting::plot2DPoints(std::queue<glm::vec2> pos, std::function<glm::vec4(glm::vec2)> colF)
{
	std::queue<float> poss;
	std::queue<float> cols;
	while (!pos.empty())
	{
		poss.push(pos.front().x);
		poss.push(pos.front().y);
		poss.push(0.0f); // ? Maybe ?

		glm::vec4 col = colF(pos.front());
		cols.push(col.x);
		cols.push(col.y);
		cols.push(col.z);
		cols.push(col.w);

		pos.pop();
	}
	return Mesh(poss, cols, std::vector<int>(), CQUMUG_MESH_3D, 0, 1);
}

Mesh Plotting::plot3DPoints(std::queue<float> pos, std::function<glm::vec4(glm::vec3)> colF)
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

Mesh Plotting::plot3DPoints(std::queue<glm::vec3> pos, std::function<glm::vec4(glm::vec3)> colF)
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

Mesh Plotting::plotFunction(bool x, bool y, bool z, float xl, float xr, float yl, float yr, float zl, float zr, float xs, float ys, float zs, std::function<float(glm::vec2)> f) // mark the function of the other with true (x(y, z)) would be (true, false, false)
{
	std::queue<float> p;
	std::queue<float> c;
	if (x)
	{
		for (float i = yl; i < yr; i += ys)
		{
			for (float j = zl; j < zr; j += zs)
			{
				p.push(f(glm::vec2(i, j)));
				p.push(i);
				p.push(j);
			}
		}
	}
	else if (y)
	{
		for (float i = xl; i < xr; i += xs)
		{
			for (float j = zl; j < zr; j += zs)
			{
				p.push(i);
				p.push(f(glm::vec2(i, j)));
				p.push(j);
			}
		}
	}
	else
	{
		for (float i = xl; i < xr; i += xs)
		{
			for (float j = yl; j < yr; j += ys)
			{
				p.push(i);
				p.push(j);
				p.push(f(glm::vec2(i, j)));
			}
		}
	}

	// TODO: Make indices to make draw the surfaces in squares

	return Mesh(p, c, std::vector<int>(), CQUMUG_MESH_3D, 0, 1);
}