#include "Observer.h"

Observer::Observer(Window * window, glm::vec3 pos, float FoV, float nearPlane, float farPlane, float maxHorizontalAngle, float maxVerticalAngle, float minHorizontalAngle, float minVerticalAngle)
{
	window->setMousePos(glm::vec2(window->getWidth() / 2, window->getHeight() / 2));
	m_pos = pos;
	m_angles[0] = 0.0f;
	m_angles[1] = 0.0f;
	m_FoV = FoV;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;

	m_maxAngles[0] = maxHorizontalAngle;
	m_maxAngles[1] = maxVerticalAngle;
	m_minAngles[0] = minHorizontalAngle;
	m_minAngles[1] = minVerticalAngle;

	glm::vec3 direction(cos(m_angles[1]) * sin(m_angles[0]), sin(m_angles[1]), cos(m_angles[1]) * cos(m_angles[0]));
	direction = glm::vec3(direction.x * -1, direction.y, direction.z * -1);

	glm::vec3 right = glm::vec3(sin(m_angles[0] - PI / 2.0f), 0, cos(m_angles[0] - PI / 2.0f));
	right = glm::vec3(right.x * -1, right.y, right.z * -1);

	glm::vec3 up = glm::cross(right, direction); // Cross product gives back the vector perpendicular to both

	float aspect = (float)window->getWidth() / (float)window->getHeight();
	glm::mat4 ProjMat = glm::perspective(glm::radians(m_FoV), aspect, m_nearPlane, m_farPlane);
	glm::mat4 ViewMat = glm::lookAt(m_pos, m_pos + direction, up);
	m_VPMat = ProjMat * ViewMat;

	m_direction = -direction;
	m_right = right;

	m_paused = false;

	m_stopwatch.reset();
}

Observer::~Observer()
{
}

void Observer::updateMouseInput(Window * window)
{
	if (!m_paused)
	{
		double dT = m_stopwatch.read();

		glm::vec2 mousePos = window->getMousePos();
		window->setMousePos(glm::vec2(window->getWidth() / 2, window->getHeight() / 2));
		m_angles[0] += MOUSE_SPEED * dT * float(window->getWidth() / 2 - mousePos.x);
		m_angles[1] += MOUSE_SPEED * dT * float(window->getHeight() / 2 - mousePos.y);

		if (m_angles[0] > m_maxAngles[0])
			m_angles[0] = m_maxAngles[0];
		else if (m_angles[0] < m_minAngles[0])
			m_angles[0] = m_minAngles[0];
		if (m_angles[1] > m_maxAngles[1])
			m_angles[1] = m_maxAngles[1];
		else if (m_angles[1] < m_minAngles[1])
			m_angles[1] = m_minAngles[1];

		m_direction = glm::vec3(cos(m_angles[1]) * sin(m_angles[0]), sin(m_angles[1]), cos(m_angles[1]) * cos(m_angles[0]));
		m_direction = glm::vec3(m_direction.x * -1, m_direction.y, m_direction.z * -1);

		m_right = glm::vec3(sin(m_angles[0] - PI / 2.0f), 0, cos(m_angles[0] - PI / 2.0f));
		m_right = glm::vec3(m_right.x * -1, m_right.y, m_right.z * -1);

		m_up = glm::cross(m_right, m_direction); // Cross product gives back the vector perpendicular to both

		glm::mat4 ProjMat = glm::perspective(glm::radians(m_FoV), (float)window->getWidth() / (float)window->getHeight(), m_nearPlane, m_farPlane);
		glm::mat4 ViewMat = glm::lookAt(m_pos, m_pos + m_direction, m_up);
		m_VPMat = ProjMat * ViewMat;

		m_stopwatch.reset();
	}
}

void Observer::setPos(glm::vec3 pos)
{
	if (m_pos.x != pos.x || m_pos.y != pos.y || m_pos.z != pos.z)
		m_moved = true;
	m_pos = pos;
}

glm::vec3 Observer::getPos()
{
	return m_pos;
}

void Observer::move(double amt, int direction)
{
	switch (direction)
	{
	case CQUMUG_RIGHT:
		glm::vec3 rightUnitVec = (m_right / glm::length(m_right));
		m_pos += glm::vec3(rightUnitVec.x * amt, rightUnitVec.y * amt, rightUnitVec.z * amt);
		break;
	case CQUMUG_LEFT:
		this->move(-1 * amt, CQUMUG_RIGHT);
		break;
	case CQUMUG_FOREWARD:
		glm::vec3 directionUnitVec = (m_direction / glm::length(m_direction));
		m_pos += glm::vec3(-directionUnitVec.x * amt, -directionUnitVec.y * amt, -directionUnitVec.z * amt);
		break;
	case CQUMUG_BACKWARD:
		this->move(-1 * amt, CQUMUG_FOREWARD);
		break;
	case CQUMUG_UP:
		glm::vec3 upUnitVec = (m_up / glm::length(m_up));
		m_pos += glm::vec3(-upUnitVec.x * amt, -upUnitVec.y * amt, -upUnitVec.z * amt);
		break;
	case CQUMUG_DOWN:
		this->move(-1 * amt, CQUMUG_UP);
		break;
	}
	m_moved = true;
}

glm::mat4 Observer::getVPMat()
{
	return m_VPMat;
}

glm::vec2 Observer::getAngles()
{
	return glm::vec2(m_angles[0], m_angles[1]);
}

bool Observer::isMoved()
{
	return m_moved;
}

void Observer::resetMoved()
{
	m_moved = false;
}

void Observer::update(Window * window, Shader * shader, const char * VPMatName)
{
	updateMouseInput(window);
	shader->setM4FV(m_VPMat, VPMatName);
}

void Observer::update(Window * window, std::vector<Shader *> shaders, const char * VPMatName)
{
	updateMouseInput(window);

	for (Shader * shader : shaders)
		shader->setM4FV(m_VPMat, VPMatName);
}

void Observer::pause()
{
	m_paused = true;
}

void Observer::unpause(Window * window)
{
	window->setMousePos(glm::vec2(window->getWidth() / 2, window->getHeight() / 2));
	m_paused = false;
}

bool Observer::isPaused()
{
	return m_paused;
}
