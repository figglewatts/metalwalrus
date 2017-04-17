#include <GL/glew.h>
#include <GL/freeglut.h>

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

double dt = 1000 / 60; // 60fps in ms
long current = 0;
long last = 0;
double timeDelta = 0;
double cumuFramerate = 0;
int measurements = 0;
double avgFramerate = 0;

void display()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    float scaleX = (float) Settings::WIDTH / (float) Settings::VIRTUAL_WIDTH;
    float scaleY = (float) Settings::HEIGHT / (float) Settings::VIRTUAL_HEIGHT;
    glScalef(scaleX, scaleY, 0);

    game->draw();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPopMatrix();

    check_gl_error();

    glutSwapBuffers();
}

void update(int data)
{
    last = current;
	current = clock();
	timeDelta = ((double)current - (double)last) / CLOCKS_PER_SEC;
	Debug::frameTime = timeDelta;
	Debug::fps = 1.0 / timeDelta;
	cumuFramerate += 1.0 / timeDelta;
	measurements++;
	avgFramerate = cumuFramerate / (double)measurements;
	
	cout << "Framerate: " << avgFramerate << endl;
	
	glutTimerFunc(dt, update, -1);

    InputHandler::handleInput();

    game->update(timeDelta);

    glutPostRedisplay();
}

void resolutionIndependentViewport(int w, int h)
{
    context->clear(0, 0, 0);

    float targetAspect = 
        (float) Settings::TARGET_WIDTH / (float) Settings::TARGET_HEIGHT;

    int width = w;
    int height = (int) (width / targetAspect + 0.5F);

    if (height > h)
    {
        height = h;
        width = (int) (height * targetAspect + 0.5F);
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

int main(int argc, char **argv)
{
    Debug::redirect("log.txt");

    context = new GLContext();
    game = new MetalWalrus("Metal Walrus", Settings::TARGET_WIDTH, Settings::TARGET_HEIGHT, context);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA);
    glutInitWindowPosition(-1, -1);
    glutInitWindowSize(game->getWidth(), game->getHeight());
    glutCreateWindow(game->getTitle());

    glewInit();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    game->start();

    glutDisplayFunc(display);
    glutReshapeFunc(changeSize);
    glutTimerFunc(dt, update, -1);

	glutKeyboardFunc(handleInputDown);
	glutSpecialFunc(handleInputDown);
	glutKeyboardUpFunc(handleInputUp);
	glutSpecialUpFunc(handleInputUp);

    glutMainLoop();

    delete game;
    delete context;
    return 1;
}