#include "Mesh.h"

std::vector<float> getRawData(std::vector <float> pos, std::vector <float> col, int dimension)
{
	std::vector <float> rawData;
	for (int i = 0; i < (float)pos.size() / dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
			rawData.push_back(pos[i*dimension + j]);
		for (int j = 0; j < 4; j++)
			rawData.push_back(col[i * 4 + j]);
	}
	return rawData;
}

std::vector<float> getRawData(std::vector <float> pos, std::vector <float> col, std::vector <float> tex, int dimension)
{
	std::vector <float> rawData;
	for (int i = 0; i < (float)pos.size() / dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
			rawData.push_back(pos[i*dimension + j]);
		for (int j = 0; j < 4; j++)
			rawData.push_back(col[i * 4 + j]);
		for (int j = 0; j < 2; j++)
			rawData.push_back(tex[i * 2 + j]);
	}
	return rawData;
}

std::vector<float> getRawData(std::queue <float> pos, std::queue <float> col, int dimension)
{
	std::vector <float> rawData;

	float temp;
	while (!pos.empty())
	{
		for (int i = 0; i < dimension; i++)
		{
			temp = pos.front(); pos.pop();
			rawData.push_back(temp);
		}
		for (int i = 0; i < 4; i++)
		{
			temp = col.front(); col.pop();
			rawData.push_back(temp);
		}
	}
	return rawData;
}

std::vector<float> getRawData(std::queue <float> pos, std::queue <float> col, std::vector <float> tex, int dimension)
{
	std::vector <float> rawData;
	int j = 0;
	float temp;
	while (!pos.empty())
	{
		for (int i = 0; i < dimension; i++)
		{
			temp = pos.front(); pos.pop();
			rawData.push_back(temp);
		}
		for (int i = 0; i < 4; i++)
		{
			temp = col.front(); col.pop();
			rawData.push_back(temp);
		}
		for (int i = 0; i < 2; i++)
			rawData.push_back(tex[j * 2 + i]);
		j++;
	}
	return rawData;
}

Mesh::Mesh(std::vector<float> pos, std::vector<float> col, std::vector<int> indices, int meshType, int posLoc, int colLoc)
{
	m_hasTex = false;
	std::vector<float> rawData = getRawData(pos, col, meshType + 2);

	if (col.size() % 4 != 0)
		std::cerr << "YOU DIDN'T USE 4DIMENSIONAL COLORS!" << std::endl;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);																												GL_DEBUG;
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);																									GL_DEBUG;
	glBufferData(GL_ARRAY_BUFFER, rawData.size() * sizeof(float), rawData.data(), GL_STATIC_DRAW);										GL_DEBUG;

	glGenBuffers(1, &m_ebo);																												GL_DEBUG;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);																							GL_DEBUG;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);								GL_DEBUG;

	glEnableVertexAttribArray(posLoc);																						GL_DEBUG;
	glVertexAttribPointer(posLoc, meshType + 2, GL_FLOAT, GL_FALSE, (sizeof(float) * (meshType + 6)), (GLvoid*)(0)); 			GL_DEBUG;

	glEnableVertexAttribArray(colLoc);																							GL_DEBUG;
	glVertexAttribPointer(colLoc, 4, GL_FLOAT, GL_FALSE, (sizeof(float) * (meshType + 6)), (GLvoid*)(sizeof(float) * 3)); 		GL_DEBUG;

	m_ic = indices.size();
	m_vc = pos.size() / (meshType + 2);
}

Mesh::Mesh(std::queue<float> pos, std::queue<float> col, std::vector<int> indices, int meshType, int posLoc, int colLoc)
{
	m_hasTex = false;
	std::vector<float> rawData = getRawData(pos, col, meshType + 2);

	if (col.size() % 4 != 0)
		std::cerr << "YOU DIDN'T USE 4DIMENSIONAL COLORS!" << std::endl;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);																												GL_DEBUG;
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);																									GL_DEBUG;
	glBufferData(GL_ARRAY_BUFFER, rawData.size() * sizeof(float), rawData.data(), GL_STATIC_DRAW);										GL_DEBUG;

	glGenBuffers(1, &m_ebo);																												GL_DEBUG;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);																							GL_DEBUG;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);								GL_DEBUG;

	glEnableVertexAttribArray(posLoc);																						GL_DEBUG;
	glVertexAttribPointer(posLoc, meshType + 2, GL_FLOAT, GL_FALSE, (sizeof(float) * (meshType + 6)), (GLvoid*)(0)); 			GL_DEBUG;

	glEnableVertexAttribArray(colLoc);																							GL_DEBUG;
	glVertexAttribPointer(colLoc, 4, GL_FLOAT, GL_FALSE, (sizeof(float) * (meshType + 6)), (GLvoid*)(sizeof(float) * 3)); 		GL_DEBUG;

	m_ic = indices.size();
	m_vc = pos.size() / (meshType + 2);
}

Mesh::~Mesh()
{
}

void Mesh::Render(Shader * shader, GLenum shape)
{
	shader->Bind();
	glBindVertexArray(this->m_vao);				GL_DEBUG;

	if (this->m_ic == 0)
	{
		glDrawArrays(shape, 0, this->m_vc);
	}
	else
	{
		glDrawElements(shape, this->m_ic, GL_UNSIGNED_INT, 0);
	}
}
