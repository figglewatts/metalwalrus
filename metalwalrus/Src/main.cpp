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
double t = 0;
double targetDeltaTime = 1 / 60.0; // target fps: 60
double lag = 0;
clock_t prevTime = clock();

void display()
{
	// semi-fixed timestep
	clock_t currTime = clock();
	clock_t elapsedTime = currTime - prevTime;
	prevTime = currTime;

	double frameTime = ((double)elapsedTime) / CLOCKS_PER_SEC;
	lag += frameTime;

	// process input here

	while (lag >= targetDeltaTime)
	{
		// if the frame time is too large then use the target
		double deltaTime = min(frameTime, targetDeltaTime);
		game->Update(deltaTime);
		lag -= deltaTime;
		t += deltaTime;
	}

	game->Draw();

	check_gl_error();
	
	glutSwapBuffers();
}

void changeSize(int w, int h)
{
	// TODO: resolution independence

	Settings::WIDTH = w;
	Settings::HEIGHT = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	Debug::redirect("log.txt");
	
	game = new Game("Sam's Game", 300, 200);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(game->getWidth(), game->getHeight());
	glutCreateWindow(game->getTitle());

	glewInit();

	game->Start();

	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	glutIdleFunc(display);

	glutMainLoop();

	delete game;
	return 1;
}