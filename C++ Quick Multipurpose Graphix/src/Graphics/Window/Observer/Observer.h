#pragma once

#include <gtc/type_ptr.hpp>
#include <gtx/transform.hpp>
#include <vector>

#include "../Window.h"
#include "../../../Utils/Utils.h"
#include "../../Shader/Shader.h"

#define MOUSE_SPEED			0.05f

#define PI					3.141592653589793238462

#define CQUMUG_RIGHT		0
#define CQUMUG_LEFT			1
#define CQUMUG_FOREWARD		2
#define CQUMUG_BACKWARD		3
#define CQUMUG_UP			4
#define CQUMUG_DOWN			5

class Observer
{
private:
	glm::vec3 m_pos;
	float m_angles[2]; // Horizontal, Vertical
	float m_maxAngles[2];
	float m_minAngles[2];
	float m_FoV;
	float m_nearPlane;
	float m_farPlane;
	HighResStopwatch m_stopwatch;

	glm::vec3 m_direction;
	glm::vec3 m_right;
	glm::vec3 m_up;

	glm::mat4 m_VPMat;

	bool m_moved;
	bool m_paused;

public:
	Observer(Window * window, glm::vec3 m_pos, float FoV, float nearPlane, float farPlane, float maxHorizontalAngle, float maxVerticalAngle, float minHorizontalAngle, float minVerticalAngle);
	~Observer();

	void updateMouseInput(Window * window);

	void setPos(glm::vec3 pos);
	glm::vec3 getPos();

	void move(double amt, int direction);

	glm::mat4 getVPMat();
	glm::vec2 getAngles();

	bool isMoved();
	void resetMoved();

	void update(Window * window, Shader * shader, const char * VPMatName = "u_VPMat");
	void update(Window * window, std::vector<Shader *> shaders, const char * VPMatName = "u_VPMat");  // Expects a vector of shaders

	void pause();
	void unpause(Window * window);
	bool isPaused();
};