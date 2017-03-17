#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ctime>
#include <algorithm>
using namespace std;

#include "Framework/Game.h"
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
	
	glutSwapBuffers();
}

void changeSize(int w, int h)
{
	// TODO: resolution independence

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	game = new Game("Sam's Game", 300, 200);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(game->getWidth(), game->getHeight());
	glutCreateWindow(game->getTitle());

	game->Start();

	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	glutIdleFunc(display);

	glutMainLoop();

	delete game;
	return 1;
}