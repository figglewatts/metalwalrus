#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <ctime>
#include <algorithm>
#include <iostream>
using namespace std;

#include "Framework/Util/Debug.h"
#include "Framework/Util/GLError.h"
#include "Framework/Input/InputHandler.h"
#include "Framework/Game.h"
#include "Framework/Settings.h"
#include "game/MetalWalrus.h"
using namespace metalwalrus;

MetalWalrus *game;
GLContext *context;

double dt = 1 / 60; // 60fps in s
double current = 0;
double last = 0;
double timeDelta = 0;
double cumuFramerate = 0;
int measurements = 0;
double avgFramerate = 0;
/*
void display()
{
    
}

void handleInputDown(unsigned char key, int mouseX, int mouseY)
{
	InputHandler::updateKeys(key, true);
}

void handleInputDown(int key, int mouseX, int mouseY)
{
	InputHandler::updateSpecials(key, true);
}

void handleInputUp(unsigned char key, int mouseX, int mouseY)
{
	InputHandler::updateKeys(key, false);
}

void handleInputUp(int key, int mouseX, int mouseY)
{
	InputHandler::updateSpecials(key, false);
}
*/

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	InputHandler::updateKeys(key, action);
}

void resolutionIndependentViewport(int w, int h)
{
	context->clear(0, 0, 0);

	float targetAspect =
		(float)Settings::TARGET_WIDTH / (float)Settings::TARGET_HEIGHT;

	int width = w;
	int height = (int)(width / targetAspect + 0.5F);

	if (height > h)
	{
		height = h;
		width = (int)(height * targetAspect + 0.5F);
	}

	int xPos = (w / 2) - (width / 2);
	int yPos = (h / 2) - (height / 2);

	context->viewport(xPos, yPos, width, height);
}

void changeSizeCallback(GLFWwindow *window, int w, int h)
{
	Settings::WIDTH = w;
	Settings::HEIGHT = h;

	resolutionIndependentViewport(w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, Settings::TARGET_WIDTH, 0, Settings::TARGET_HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void update()
{
	current = glfwGetTime();
	timeDelta = current - last;

	Debug::frameTime = timeDelta;
	Debug::fps = 1.0 / timeDelta;
	cumuFramerate += 1.0 / timeDelta;
	measurements++;
	avgFramerate = cumuFramerate / (double)measurements;

	if (timeDelta >= dt)
	{
		glfwPollEvents();

		InputHandler::handleInput();
		game->update(timeDelta);

		last = current;
	}
}

void draw()
{
	check_gl_error();
	glMatrixMode(GL_MODELVIEW);
	check_gl_error();
	glPushMatrix();
	check_gl_error();
	float scaleX = (float)Settings::WIDTH / (float)Settings::VIRTUAL_WIDTH;
	float scaleY = (float)Settings::HEIGHT / (float)Settings::VIRTUAL_HEIGHT;
	glScalef(scaleX, scaleY, 0);
	check_gl_error();

	game->draw();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPopMatrix();

	check_gl_error();
}

// initialization code from:
// https://learnopengl.com/code_viewer.php?code=getting-started/hellowindow2
int main(int argc, char **argv)
{
	Debug::redirect("log.txt");

	context = new GLContext();

	game = new MetalWalrus("Metal Walrus", Settings::TARGET_WIDTH, Settings::TARGET_HEIGHT, context);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(Settings::TARGET_WIDTH, Settings::TARGET_HEIGHT, 
		game->getTitle(), nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// set resize callback
	glfwSetWindowSizeCallback(window, changeSizeCallback);
	changeSizeCallback(window, Settings::TARGET_WIDTH, Settings::TARGET_HEIGHT);

	game->start();

	// Game loop
	last = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		update();

		draw();

		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	delete game;
	delete context;
	return 0;
}