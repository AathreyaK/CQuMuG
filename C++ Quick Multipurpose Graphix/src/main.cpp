#define CQUMUG_VERSION		"2.0.0"
#define SETTINGS_PATH		"Settings.h"

#include "Graphics/Window/Window.h"
#include "Graphics/Window/Observer/Observer.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Object/Mesh.h"
#include "Tools/Plotting.h"
#include "Projects/Projects.h"
#include SETTINGS_PATH

extern int key_pressed[GLFW_KEY_LAST];
extern int button_pressed[GLFW_MOUSE_BUTTON_LAST];

int main(void)
{
	HighResStopwatch s;
	srand(time(0));

	Window window(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, WIN_ICON);
	Observer observer(&window, glm::vec3(0.0f, 0.0f, 2.0f), 60.0f, 0.1f, 100.0f, PI, PI / 2, -1 * PI, -1 * PI / 2);

	Shader basicShader("res/Shaders/vertexBasic.glsl", "res/Shaders/fragmentBasic.glsl");													GL_DEBUG;
	std::vector<Shader *> shaders;
	shaders.push_back(&basicShader);
	
	std::cout << "Loading meshes . . . " << std::endl;
	s.reset();
	Mesh m = Plotting::plotFunction(false, false, true, -10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 0.1f, 0.1f, [](glm::vec2 v) { float r = sqrt(v.x*v.x + v.y*v.y);  return r + 3 * tan(r + 5); }, [](glm::vec3 v) { return glm::vec4(0.0f, 0.7f, 1.0f, 1.0f); });
	std::cout << "Loading meshes took " << s.read() << " seconds!" << std::endl;
	
	while (!window.isClosed())																				   
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
		m.Render(shaders[0], GL_POINTS);

		{ // EVENT HANDLING
			if (key_pressed[GLFW_KEY_ESCAPE])																   
				window.close();	
			if (key_pressed[GLFW_KEY_P])
				observer.pause();
			if (key_pressed[GLFW_KEY_P] == 2) // Long click
				observer.unpause(&window);
			// DO INPUT EVENTS ONLY IF THE OBSERVER ISN'T PAUSED
			if (!observer.isPaused())
			{
				// GAME EVENT HANDLING
				if (key_pressed[GLFW_KEY_RIGHT])
					observer.move(0.1, CQUMUG_RIGHT);
				if (key_pressed[GLFW_KEY_LEFT])
					observer.move(0.1, CQUMUG_LEFT);
				if (key_pressed[GLFW_KEY_UP])
					observer.move(0.1, CQUMUG_FOREWARD);
				if (key_pressed[GLFW_KEY_DOWN])
					observer.move(0.1, CQUMUG_BACKWARD);
			}
		}																									   

		window.Refresh();				
		observer.update(&window, shaders);
    }

    window.close();
	
    return 0;
}