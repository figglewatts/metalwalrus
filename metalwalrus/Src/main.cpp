#include <GL/glew.h>
#include <GL/freeglut.h>

#include <ctime>
#include <algorithm>
using namespace std;

#include "Framework/Util/Debug.h"
#include "Framework/Util/GLError.h"
#include "Framework/Game.h"
#include "Framework/Settings.h"
using namespace metalwalrus;

Game *game;
GLContext *context;

clock_t t = 0.0;
float dt = 1 / 60.0;
clock_t currTime = clock();

double lastLoopTime = 0;
double timeAccumulatedMs = 0;

void displayFunc()
{
	double now = glutGet(GLUT_ELAPSED_TIME);
	double timeElapsedMs = ((now - lastLoopTime) * 1000) / CLOCKS_PER_SEC;
	timeAccumulatedMs += timeElapsedMs;

}

void display()
{
	clock_t timeThisIteration = 0;
	clock_t startTime = clock();
	
	while (t >= dt)
	{
		game->Update(dt);
		t -= dt;
		timeThisIteration += dt;
	}

	// animation??

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	float scaleX = (float)Settings::WIDTH / (float)Settings::VIRTUAL_WIDTH;
	float scaleY = (float)Settings::HEIGHT / (float)Settings::VIRTUAL_HEIGHT;
	glScalef(scaleX, scaleY, 0);

	game->Draw();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPopMatrix();

	// handle input here

	t += clock() - startTime;

	check_gl_error();

	glutSwapBuffers();
}

void resolutionIndependentViewport(int w, int h)
{
	context->clear(0, 0, 0);

	float targetAspect = (float)Settings::TARGET_WIDTH / (float)Settings::TARGET_HEIGHT;
	
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

void changeSize(int w, int h)
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

int main(int argc, char **argv)
{
	Debug::redirect("log.txt");
	
	context = new GLContext();
	game = new Game("Sam's Game", Settings::TARGET_WIDTH, Settings::TARGET_HEIGHT, context);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(game->getWidth(), game->getHeight());
	glutCreateWindow(game->getTitle());

	glewInit();

	lastLoopTime = glutGet(GLUT_ELAPSED_TIME);

	//resolutionIndependentViewport(game->getWidth(), game->getHeight());

	game->Start();

	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	glutIdleFunc(display);

	glutMainLoop();

	delete game;
	delete context;
	return 1;
}