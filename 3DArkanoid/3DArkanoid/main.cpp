#include <glut.h>
#include <gl/GL.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "bouncingBall.h"
#include "platform.h"

BouncingBall bBall;
Platform platform;
float xLook =0.0f, yLook = 0.0f, zLook =0.0f;

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();                       
    gluLookAt(0.0f, 0.2f, 0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
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
		if(bBall.collide(platform))
		{
			platform.applyBoost(bBall);
		}
	}
	bBall.update();
	platform.update();
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'd': platform.moveLeft(); break;
		case 'l': platform.moveRight(); break;
		//case 'z': xLook+=0.1f; printf("X: %f", xLook); break;
		//case 'x': yLook+=0.1f; printf("Y: %f", yLook); break;
		//case 'c': zLook+=0.1f; printf("Z: %f", zLook); break;
		//case 'q': xLook-=0.1f; printf("X: %f", xLook); break;
		//case 'w': yLook-=0.1f; printf("Y: %f", yLook); break;
		//case 'e': zLook-=0.1f; printf("Z: %f", zLook); break;
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

