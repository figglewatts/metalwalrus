#include<GL/glew.h>
#include<GL/freeglut.h>

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(50, 75);
		glVertex2f(100, 0);
	glEnd();

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
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(300, 200);
	glutCreateWindow("Metal Walrus");

	glutDisplayFunc(draw);
	glutReshapeFunc(changeSize);

	glutMainLoop();

	return 1;
}