#include <glut.h>
#include <gl/GL.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "bouncingBall.h"
#include "platform.h"

BouncingBall bBall;
Platform platform;

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();                       
    glOrtho(-1, 1, -1, 1, -1, 1);   
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//Draw grid
	for(float x = -1.00f; x < 1.00f; x+=0.1f)
	{
		glBegin(GL_LINES); 	
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(x, -1.0); 
		glVertex2f(x, 1.0);  
		glEnd();  
	}
	for(float y = -1.00f; y < 1.00f; y+=0.1f)
	{
		glBegin(GL_LINES); 	
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(-1.0, y); 
		glVertex2f(1.0, y);  
		glEnd();  
	}

	platform.draw();
	bBall.draw();

	glutSwapBuffers();
}

void Reshape(GLint width, GLint height)
{
}

void InitGraphics(void)
{
}

void MouseButton(int button, int state, int x, int y)
{
}

void MouseMotion(int x, int y)
{
}

void IdleFunc(void)
{
	if(bBall.intersects(platform))
	{
		bBall.collide(platform);
	}
	bBall.update();
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'd': platform.moveLeft(); break;
		case 'l': platform.moveRight(); break;
	}
}

int main(int argc, char* argv[])
{
	bBall = BouncingBall(0.0f, 0.0f);
	platform = Platform(0.0f, -0.5f);

	glutInit (&argc, argv);
	glutInitWindowSize (640, 640);
	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow ("GLUT example");
	// Initialize OpenGL graphics state
	InitGraphics();
	// Register callbacks:
	glutDisplayFunc (Display);
	glutReshapeFunc (Reshape);
	glutKeyboardFunc (Keyboard);
	glutMouseFunc (MouseButton);
	glutMotionFunc (MouseMotion);
	glutIdleFunc (IdleFunc);
	// Turn the flow of control over to GLUT
	glutMainLoop ();
	return 0;
}

