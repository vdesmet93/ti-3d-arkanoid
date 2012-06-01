#include <stdlib.h>
#include <glut.h>
#include <gl/GL.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "bouncingBall.h"
#include "platform.h"
#include "block.h"
#include "highgui.h"
#include "cvblob.h"
#include <iostream>
using namespace cvb;
using namespace std;

//Game 
BouncingBall bBall;
Platform platform;
float xLook =0.0f, yLook = 0.0f, zLook =0.0f;
bool grid[10][3];
Block blocks[10][3];
Block block;

//OpenCV
IplImage *frame, *labelImg;
CvCapture* capture = cvCaptureFromCAM(1);
CvBlobs blobs;

//Texture
GLuint TEXTURE1 = 10;

void updateCameraFrame();
void analyseCameraFrame();
void DrawIplImage(IplImage *image);

void Display(void)
{
	//Camera 
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_TEXTURE_2D);
	//if( frame )
	//{
	//	DrawIplImage(frame);
	//}
	//glutSwapBuffers();

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
	block.draw();
	bBall.draw();
	//for(int x = 0; x < 10; x++)
	//{
	//	for(int y = 0; y < 3; y++)
	//	{
	//		if(grid[x][y])
	//		{
	//			blocks[x][y].draw();
	//		}
	//	}
	//}

	glutSwapBuffers();
}

void DrawIplImage(IplImage *image)
{
	int x = -1;
	int y = -1;
	GLfloat xZoom = 2.0f;
	GLfloat yZoom = 2.0f;
    GLenum format;
    switch(image->nChannels) 
	{
        case 1: format = GL_LUMINANCE; break;
        case 2: format = GL_LUMINANCE_ALPHA; break;
        case 3: format = GL_BGR_EXT; break;
        default: return;
    }
	glRasterPos2i(x, y);
    glPixelZoom(xZoom, yZoom);
    glDrawPixels(image->width, image->height, format, GL_UNSIGNED_BYTE, image->imageData);
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

void updateCameraFrame()
{
	cvReleaseImage(&frame);
	//Get latest camera frame
	frame = cvQueryFrame( capture );
	//Convert to grayscale
	IplImage *gray = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1 );
	cvCvtColor(frame, gray, CV_RGB2GRAY );
	//Original frame = grayscale version
	frame = gray;
}

void analyseCameraFrame()
{
	cvReleaseImage(&labelImg);
	cvReleaseBlobs(blobs);

	cvThreshold(frame, frame, 0, 50, CV_THRESH_BINARY);
	labelImg = cvCreateImage(cvGetSize(frame), IPL_DEPTH_LABEL, 1);
	unsigned int result=cvLabel(frame, labelImg, blobs);

	for (CvBlobs::const_iterator it=blobs.begin(); it!=blobs.end(); ++it)
	{
		cout << "Blob #" << it->second->label << ": Centroid = (" << it->second->centroid.x << ", " << it->second->centroid.y << ")" << endl;
	}
}

void IdleFunc(void)
{
	//updateCameraFrame();
	//analyseCameraFrame();

	if(bBall.intersects(platform))
	{
		if(bBall.collide(platform))
		{
			platform.applyBoost(bBall);
		}
	}
	else if(bBall.intersects(block))
	{
		bBall.collide(block);
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
	//for(int x = 0; x < 10; x++)
	//{
	//	for(int y = 0; y < 3; y++)
	//	{
	//		grid[x][y] = true;
	//		blocks[x][y] = Block(-1.0f+(float)(x*0.2f), 1.0f-(float)(y*0.1f), 0.0f, 0.2f, 0.1f, 0.2f);
	//		blocks[x][y].setColor(x*0.1f, y*0.1f, 0.5f);
	//	}
	//}
	block = Block(0.0f, 0.7f, 0.0f, 0.2f, 0.1f, 0.2f);
	block.setColor(0.6f, 0.3f, 0.1f);

	glutInit (&argc, argv);
	glutInitWindowSize (640, 640);
	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow ("3D Arkanoid");
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

