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

const int TARGET_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = CLOCKS_PER_SEC / TARGET_FPS;
clock_t startTick = 0;
clock_t endTick = 0;
clock_t diffTicks = 0;
double dt = 0;
double idealDt = 1 / (double)TARGET_FPS; // 60fps
int countedFrames = 0;

void display()
{
	startTick = clock();
	
	if (diffTicks <= 0) dt = idealDt;
	else dt = diffTicks / CLOCKS_PER_SEC;

	float avgFPS = countedFrames / dt;
	if (avgFPS > 2000000) avgFPS = 0;

	game->Update(dt);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	float scaleX = (float)Settings::WIDTH / (float)Settings::VIRTUAL_WIDTH;
	float scaleY = (float)Settings::HEIGHT / (float)Settings::VIRTUAL_HEIGHT;
	glScalef(scaleX, scaleY, 0);

	game->Draw();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPopMatrix();

	endTick = clock();

	++countedFrames;

	// if frame finished early
	diffTicks = endTick - startTick;
	if (diffTicks < SCREEN_TICKS_PER_FRAME)
	{
		float remainingMs = (SCREEN_TICKS_PER_FRAME - diffTicks);
		Sleep(remainingMs);
	}
	
	
	/*current = clock();
	if (current > nextGameTick)
	{
		while (current > nextGameTick) 
		{		
		    dt = ((double)current - (double)nextGameTick) / CLOCKS_PER_SEC;
		    
			game->Update(dt);

			nextGameTick += SKIP_TICKS;
		}

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		float scaleX = (float)Settings::WIDTH / (float)Settings::VIRTUAL_WIDTH;
		float scaleY = (float)Settings::HEIGHT / (float)Settings::VIRTUAL_HEIGHT;
		glScalef(scaleX, scaleY, 0);

		game->Draw();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPopMatrix();
	}
	else
	{
		
	}
	*/
	// animation??

	


	// handle input here

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