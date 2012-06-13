
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
using namespace cv;
//using namespace cvb;
using namespace std;


//Game 
BouncingBall bBall;
Platform platform;
float xLook =0.0f, yLook = 0.0f, zLook =0.0f;
bool grid[10][10];
Block block;
vector<vector<vector<Block>>> level;

//OpenCV
IplImage *frame, *frame2, *cameraFrame; //frame: upper region; frame2: lower region; cameraFrame: camera view
CvCapture* capture = cvCaptureFromCAM(1);
float cX, cY;
CvMemStorage *mem;
CvSeq *contours, *ptr; 

//Test
//IplImage *img, *cc_color; 
 

//Texture
GLuint TEXTURE1 = 10;

//Prototypes
void IdleFunc(int value);
void updateCameraFrame();
void analyseCameraFrame();
void DrawIplImage(IplImage *image);
void fillBlocks();
void checkCollisionBall();
void removeBlock(int x, int y);
void analyseUpperFrame();
void analyseLowerFrame();

void drawAxes()
{
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(1000, 0, 0);
	glEnd();

	glColor3f(1, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1000);
	glEnd();
	
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1000, 0);
	glEnd();

}

void drawBlocks()
{
	for(int x = 0; x < level.size(); x++)
	{
		for(int y = 0; y < level[x].size(); y++)
		{
			for(int z= 0; z < level[x][y].size(); z++)
			{
				if(level[x][y][z].isEnabled())
				{
					float x2= 0.1*x-0.1*level[x].size();
					float y2 = 0.1*y+0.4;
					level[x][y][z].draw(x2, y2, z*0.1, 0.2, 0.2, 0.2);
				}
			}
		}
	}
}

void Display(void)
{
	//Camera 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	
	//glutSwapBuffers();

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();  
	gluPerspective(90, 1, 0.1, 600);
    gluLookAt(1.0f, -1.2f, 1.6f, 
		0.0f, 0.0f, 
		0.0f, 0.0f, 1.0f, 0.0f);
	//gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if( frame )
	{
		//glPushMatrix();
		//glTranslatef(0.0f, 1.0f, 0.0f);
		//DrawIplImage(frame);
		//glPopMatrix();
		//DrawIplImage(frame2);
		//DrawIplImage(cameraFrame);
	}
	//Draw grid
	for(float x = -1.00f; x < 1.00f; x+=0.1f)
	{
		glBegin(GL_LINES); 	
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(x, -1.0); 
		glVertex2f(x, 1.0);  
		glEnd();  
	}

	drawAxes();
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
	
	drawBlocks();

	glutSwapBuffers();
}

void DrawIplImage(IplImage *image)
{
	float x = -1.0f;
	float y = -1.0f;
	GLfloat xZoom = 1.3333333333f;
	GLfloat yZoom = 1.3333333333f;
    GLenum format;
    switch(image->nChannels) 
	{
        case 1: format = GL_LUMINANCE; break;
        case 2: format = GL_LUMINANCE_ALPHA; break;
        case 3: format = GL_BGR_EXT; break;
        default: return;
    }
	glPushMatrix();
	glRasterPos2f(x, y);
    glPixelZoom(xZoom, yZoom);
    glDrawPixels(image->width, image->height, format, GL_UNSIGNED_BYTE, image->imageData);
	glPopMatrix();
}

void generateDefaultLevel()
{
	int cntr = 5;
	level.resize(10);
	for(int x = 0; x < 10; x++)
	{
		level[x].resize(5);
		cntr = 1;
		for(int y = 0; y < 5; y++)
		{
			level[x][y].resize(cntr);
			for(int z = 0; z < cntr; z++)
			{
				float x2= 0.1*x-0.1*level[x].size();
				float y2 = 0.1*y+0.4;
				level[x][y][z].setCoordinates(x2, y2, z*0.1);
				level[x][y][z].setDimensions(0.2f, 0.2f, 0.2f);
				level[x][y][z].setColor(1.0, 1.0, 1.0);
				grid[x][y] = true;
			}
			cntr++;
		}
	}
	cout << "yay" << endl;
}

void switchBlocksDownAbove(int x, int y, int z)
{
	for(int idx = y; idx < level[x][y].size()-1; idx++)
	{
		level[x][idx][z] = level[x][idx+1][z];
		level[x][idx+1][z].disable();
	}
}

void removeBlock(int x, int y, int z)
{
	level[x][y][z].disable();
	grid[x][y] = 0;
	switchBlocksDownAbove(x, y, z);
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
	cvReleaseImage(&cameraFrame);
	cvReleaseImage(&frame);
	cvReleaseImage(&frame2);
	
	//Get latest camera frame
	frame = cvQueryFrame( capture );
	//Make sure that width = height
	cvSetImageROI(frame, cvRect(0,0,480, 480)); 
	IplImage *frameRegion = cvCreateImage(cvGetSize(frame),
                               frame->depth,
                               frame->nChannels);
	cvCopy(frame, frameRegion, NULL);
	cameraFrame = frameRegion;
	
	//Convert to grayscale
	IplImage *gray = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1 );
	cvCvtColor(frame, gray, CV_RGB2GRAY );
	//Original frame = grayscale version
	frame = gray;

	//Split image in 2
	//Lower region
	cvSetImageROI(frame, cvRect(0,0,480, 240)); 
	IplImage *frameRegion2 = cvCreateImage(cvGetSize(frame),
                               frame->depth,
                               frame->nChannels);
	cvCopy(frame, frameRegion2, NULL);
	frame2 = frameRegion2;
	
	//Upper region
	cvSetImageROI(frame, cvRect(0,240,480, 480)); 
	IplImage *frameRegion3 = cvCreateImage(cvGetSize(frame),
                               frame->depth,
                               frame->nChannels);
	cvCopy(frame, frameRegion3, NULL);
	frame = frameRegion3;

	//cvReleaseImage(&gray);
	//printf("\n%dx%d", frame->width, frame->height);printf("\n%dx%d", frame->width, frame->height);
}

void analyseUpperFrame()
{
	IplImage *img = frame;
    IplImage *cc_color = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
 
    cvThreshold(img, img, 100, 200, CV_THRESH_BINARY_INV);

    mem = cvCreateMemStorage(0);


    cvFindContours(img, mem, &contours, sizeof(CvContour), CV_RETR_CCOMP,
        CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

    for (ptr = contours; ptr != NULL; ptr = ptr->h_next) 
	{
        //CvScalar color = CV_RGB( rand()&255, rand()&255, rand()&255 );
        cvDrawContours(cc_color, ptr, CV_RGB(255,0,0), CV_RGB(0,0,0), -1, CV_FILLED, 8, cvPoint(0,0));
		Rect boundingRect = cvBoundingRect(ptr,0);
			cvRectangle(cc_color,cvPoint(boundingRect.x,boundingRect.y),
                    cvPoint(boundingRect.x+boundingRect.width,
                    boundingRect.y+boundingRect.height),
                    CV_RGB(1.0,0.5,0.5),1,8,0);
		
		//printf("Size: %d", contours->total);
    }

	frame = cc_color;
	cvReleaseImage(&img);
	cvReleaseMemStorage(&mem);
}

void analyseLowerFrame()
{
	IplImage *img = frame2;
    IplImage *cc_color = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
 
    cvThreshold(img, img, 100, 200, CV_THRESH_BINARY_INV);

    mem = cvCreateMemStorage(0);


    cvFindContours(img, mem, &contours, sizeof(CvContour), CV_RETR_CCOMP,
        CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

	int largestArea = 0;
	Rect largestRect;
    for (ptr = contours; ptr != NULL; ptr = ptr->h_next) 
	{
        //CvScalar color = CV_RGB( rand()&255, rand()&255, rand()&255 );
        cvDrawContours(cc_color, ptr, CV_RGB(255,0,0), CV_RGB(0,0,0), -1, CV_FILLED, 8, cvPoint(0,0));
		Rect boundingRect = cvBoundingRect(ptr,0);
		int currentArea = boundingRect.width*boundingRect.height;
		if(currentArea > largestArea)
		{
			largestArea = currentArea;
			largestRect = boundingRect;
		}
		
		//printf("Size: %d", contours->total);
    }
	cvRectangle(cc_color,cvPoint(largestRect.x,largestRect.y),
                    cvPoint(largestRect.x+largestRect.width,
                    largestRect.y+largestRect.height),
                    CV_RGB(1.0,0.5,0.5),1,8,0);
		//printf("\nX: %d", largestRect.x);
	float platformX = -1.0f+(largestRect.x*1.0f/240);
	platform.moveTo(platformX);
	frame2 = cc_color;
	cvReleaseImage(&img);
	cvReleaseMemStorage(&mem);
}

void analyseCameraFrame()
{
	analyseLowerFrame();
	analyseUpperFrame();
}

void checkCollisionBall()
{
	//platform check
	if(bBall.intersects(platform))
	{
		if(bBall.collide(platform))
		{
			platform.applyBoost(bBall);
		}
	}
	//blocks check
	int x = (5.0f*(bBall.getCenterX()+1.0f));
	int y = (5.0f*(bBall.getCenterY()+1.0f));

	cout << x << " " << y << endl;

	if(bBall.intersects(level[x][y+1][0]))
	{
		bBall.collide(level[x][y+1][0]);
		removeBlock(x, y+1, 0);
	}
	else if(bBall.intersects(level[x+1][y][0]))
	{
		bBall.collide(level[x+1][y][0]);
		removeBlock(x+1, y, 0);
	}
	else if(bBall.intersects(level[x-1][y][0]))
	{
		bBall.collide(level[x-1][y][0]);
		removeBlock(x-1, y, 0);
	}
	else if(bBall.intersects(level[x][y-1][0]))
	{
		bBall.collide(level[x][y-1][0]);
		removeBlock(x, y-1, 0);
	}
}

void IdleFunc(int value)
{
	//updateCameraFrame();
	//analyseCameraFrame();
	bBall.update();
	platform.update();
	checkCollisionBall();

	glutPostRedisplay();

	glutTimerFunc(10, IdleFunc, 0);
}

void Idle() {
	IdleFunc(0);
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
	platform = Platform(0.0f, -1.0f);
	generateDefaultLevel();

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
		glutIdleFunc (Idle);
	// Turn the flow of control over to GLUT
	glutMainLoop ();

	return 0;
}

