
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
#include "texture.h"
using namespace cv;
//using namespace cvb;
using namespace std;

unsigned int textures[] = {0, 1};

//Game 
BouncingBall bBall;
Platform platform;
float xLook =0.0f, yLook = 0.0f, zLook =0.0f, yFar;
bool grid[10][10];
vector<vector<vector<Block>>> level;

//OpenCV
IplImage *frame, *frame2, *cameraFrame; //frame: upper region; frame2: lower region; cameraFrame: camera view
CvCapture* capture = cvCaptureFromCAM(1);
float cX, cY;
CvMemStorage *mem;
CvSeq *contours, *ptr; 

int score = 0;

//Test
//IplImage *img, *cc_color;
bool cameraTextureLoaded = false;

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
void setLight(void);

void initTexture(IplImage* frameImg)
{

 IplImage *textImg = cvCreateImage(cvSize(512,256), frameImg->depth, frameImg->nChannels);
 cvResize(frameImg, textImg);
    //cvFlip(textImg, NULL, 0);
 
	glGenTextures(1, &TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TEXTURE1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
 
    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glTexImage2D(GL_TEXTURE_2D, 0, 3,textImg->width, textImg->height,0,
       GL_BGR_EXT,GL_UNSIGNED_BYTE, textImg->imageData);
 
    cvReleaseImage(&textImg);
 
}

void updateTexture(IplImage* frameImg)
{
	IplImage *textImg = cvCreateImage(cvSize(512,256), frameImg->depth, frameImg->nChannels);
	cvResize(frameImg, textImg);

	glBindTexture(GL_TEXTURE_2D, TEXTURE1);    //A texture you have already created with glTexImage2D
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, textImg->width, textImg->height, GL_BGR_EXT, GL_UNSIGNED_BYTE, textImg->imageData);

	cvReleaseImage(&textImg);
}

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

void drawScore()
{
	char buf[20];
	sprintf(buf, "Score: %i", score);
	string scoreString = buf;

	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);
	//Assume we are in MODEL_VIEW already
	glPushMatrix ();
	glLoadIdentity ();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix ();
	glLoadIdentity();

	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2f(-1, -1);
	
	for(int i = 0; i < scoreString.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreString[i]);
	}
	glColor3f(1.0f, 1.0f, 1.0f);
	glPopMatrix ();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix ();
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
					level[x][y][z].draw();
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
	//glEnable(GL_DEPTH_TEST);
	
	setLight();
	//glEnable (GL_DEPTH_TEST); //enable the depth testing
 //   glEnable (GL_LIGHTING); //enable the lighting
	//glEnable (GL_COLOR_MATERIAL);
	//glEnable (GL_LIGHT0); //enable LIGHT0, our Diffuse Light
	//GLfloat LightAmbient[]  = {0.5f, 0.5f, 0.5f, 1.0f};  
	//GLfloat LightDiffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};  
	//GLfloat LightPosition[] = {0.0f, 1.0f, 1.0f, 1.0f};  
	//glLightfv(GL_LIGHT0, GL_POSITION,  LightAmbient);
	//glLightfv(GL_LIGHT0, GL_AMBIENT,  LightDiffuse);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE,  LightPosition);

 //   glShadeModel (GL_SMOOTH); //set the shader to smooth shader

	//glutSwapBuffers();

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glEnable(GL_DEPTH_TEST);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();  
    //gluLookAt(0.0f, -0.1f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();  
	gluPerspective(90, 1, 0.1, 600);
    gluLookAt(0.0, -0.6f, 1.2, 
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
		
		glEnable(GL_TEXTURE_2D);
		if(!cameraTextureLoaded)
		{
			initTexture(cameraFrame);
			cameraTextureLoaded++;
		}
		else
		{
			updateTexture(cameraFrame);
		}
		//glColor3f(1.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(0,1); glVertex3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(1,1); glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(1,0); glVertex3f(1.0f, -1.0f, 0.0f);
		glEnd();
		//DrawIplImage(cameraFrame);
	}
	glDisable(GL_TEXTURE_2D);
	//Draw grid
	//for(float x = -1.00f; x < 1.00f; x+=0.1f)
	//{
	//	glBegin(GL_LINES); 	
	//	glColor3f(1.0f, 0.0f, 0.0f);
	//	glVertex2f(x, -1.0); 
	//	glVertex2f(x, 1.0);  
	//	glEnd();  
	//}

	//drawAxes();
	//for(float y = -1.00f; y < 1.00f; y+=0.1f)
	//{
	//	glBegin(GL_LINES); 	
	//	glColor3f(0.0f, 1.0f, 0.0f);
	//	glVertex2f(-1.0, y); 
	//	glVertex2f(1.0, y);  
	//	glEnd();  
	//}
	bBall.draw();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	platform.draw();
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	drawBlocks();
	glDisable(GL_TEXTURE_2D);
	
	//glDisable(GL_LIGHTING);

	drawScore();

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
	//glRotatef(xLook, yLook, zLook);
	glRasterPos3f(-0.5, -0.5, -0.5);
    glPixelZoom(xZoom, yZoom);
    glDrawPixels(image->width, image->height, format, GL_UNSIGNED_BYTE, image->imageData);
	glPopMatrix();
}

void generateDefaultLevel()
{
	float size = 0.2f;
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
				float x2= size*x-size*level[x].size();
				float y2 = size*y;
				level[x][y][z].setCoordinates(x2, y2, z*size);
				level[x][y][z].setDimensions(size,size, size);
				level[x][y][z].setColor(1.0, 1.0, 1.0);
				grid[x][y] = true;
			}
			cntr++;
		}
	}
	//cout << "yay" << endl;
}

void switchBlocksDownAbove(int x, int y, int z)
{
	for(int idx = z; idx < level[x][y].size()-1; idx++)
	{
		level[x][y][idx+1].drop();
		level[x][y][idx] = level[x][y][idx+1];
		level[x][y][idx+1].disable();
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

	cvReleaseImage(&gray);
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
	float platformX = -1.0f+((largestRect.x+largestRect.width/2)*1.0f/240);
	float platformY = -1.0f+((largestRect.y+largestRect.height/2)*1.0f/240);
	platform.moveTo(platformX, platformY);
	frame2 = cc_color;
	cvReleaseImage(&img);
	cvReleaseMemStorage(&mem);
}

void analyseCameraFrame()
{
	analyseLowerFrame();
	//analyseUpperFrame();
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
	for(int x = 0; x < level.size(); x++)
	{
		for(int y = 0; y < level[x].size(); y++)
		{
			if(bBall.intersects(level[x][y][0]) && level[x][y][0].isEnabled())
			{
				if(bBall.collide(level[x][y][0]))
				{
					removeBlock(x, y, 0);
					score++;
				}
			}
		}
	}
}

void IdleFunc(int value)
{
	updateCameraFrame();
	analyseCameraFrame();
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
		case 'z': xLook+=0.1f; printf("\nX: %f", xLook); break;
		case 'x': yLook+=0.1f; printf("\nY: %f", yLook); break;
		case 'c': zLook+=0.1f; printf("\nZ: %f", zLook); break;
		case 'q': xLook-=0.1f; printf("\nX: %f", xLook); break;
		case 'w': yLook-=0.1f; printf("\nY: %f", yLook); break;
		case 'e': zLook-=0.1f; printf("\nZ: %f", zLook); break;
		case 'v': yFar+=0.1f; printf("\nYFar: %f", yFar); break;
		case 'b': yFar-=0.1f; printf("\nYFar: %f", yFar); break;
	}
}

void setLight(void)
{
	////////////////////////////////Lighting Implementation////////////////////////////////////////
	//Andrew Experimental///////////////////////////////////////////////////////////////////////////
	glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);

   GLfloat mat_specular[] = { 0.8, 0.5, 0.2, 1.0 };
   GLfloat mat_shininess[] = { 1 }; //experiment with this one
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };
   //glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);

	////////////////////////////////////////////////////////////////////////////////////////////
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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	// load texture as compressed
	textures[0] = LoadTexture("metal.bmp");
	textures[1] = LoadTexture("asteroid.bmp");

	// Turn the flow of control over to GLUT
	glutMainLoop ();

	return 0;
}

