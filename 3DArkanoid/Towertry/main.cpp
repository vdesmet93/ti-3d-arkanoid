
#include    <windows.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <iostream>
#include    <gl\gl.h>
#include    <gl\glu.h>
#include    <glut.h>
#include	"Block.h"
#include	<vector>

using namespace std;

int varwidth;
int varheight;
float rotation = 0;
vector<vector<vector<Block>>> level;

/*int LoadTexture(std::string filename)
{
	HBITMAP hBMP;
	BITMAP BMP;
	GLuint texid;

	glGenTextures(1, &texid);
	hBMP=(HBITMAP)LoadImage(GetModuleHandle(NULL), filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glBindTexture(GL_TEXTURE_2D, texid);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texid;

}*/

void generateDefaultLevel()
{
	int cntr = 5;
	level.resize(5);
	for(int x = 0; x < 5; x++)
	{
		level[x].resize(cntr);
		for(int y = 0; y < cntr; y++)
		{
			level[x][y].resize(10);
			for(int z = 0; z < 10; z++)
			{
				level[x][y][z].setColor((x == 0) ? 1 : 1/x, (y == 0) ? 1 : 1/y, (z == 0) ? 1 : 1/z);
			}
		}
		cntr--;
	}
	cout << "yay" << endl;
}

void drawBlocks()
{
	//level[0][0][0].draw(0, 0, 0, 5, 5, 5);
	int cntr = 5;
	for(int x = 0; x < level.size(); x++)
	{
		for(int y = 0; y < level[x].size(); y++)
		{
			for(int z= 0; z < level[x][y].size(); z++)
			{
				level[x][y][z].draw(z*5, y*5,x*5, 5, 5, 5);
			}
		}
	}
}

void drawNode(int nodeHorizontalRotation, int nodeVerticalRotation)
{
	glRotatef(rotation, 0, 1, 0);
	glRotatef(nodeVerticalRotation, 0, 0, 1);
	glRotatef(nodeHorizontalRotation, 1, 0, 0);
	glutSolidSphere(1, 10, 10);
	glTranslatef(0.75, 0, 0);
	glutSolidCube(0.75);
	glTranslatef(0.75, 0, 0);
	glutSolidCube(0.75);
	glTranslatef(0.75, 0, 0);
	glutSolidCube(0.75);
	glTranslatef(0.75, 0, 0);
	glutSolidCube(0.75);
	glTranslatef(0.75, 0, 0);
	glutSolidCube(0.75);
}

void drawAxes()
{
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(1000, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1000);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1000, 0);
	glEnd();

}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	glLoadIdentity();

	gluLookAt(50,100,50,
		0,0,0,
		0,1,0);

	drawAxes();
	drawBlocks();

	glutSwapBuffers();
}

void Display2(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLoadIdentity();

	gluLookAt(100,100,100,
		0,0,0,
		0,1,0);

	glRotatef(rotation, 0, 1, 0);

	for(int i = 0; i < 20; i++)
	{
		drawNode(10, 10);
	}

	glutSwapBuffers();
}


void Reshape(GLint width, GLint height)
{
	varwidth = width;
	varheight = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, varwidth/(float)varheight, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
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
	//rotation += 0.01;
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:             // ESCAPE key
			exit (0);
			break;
	}
}

int main(int argc, char* argv[])
{
	glutInit (&argc, argv);
	glutInitWindowSize (1024, 768);
	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow ("GLUT WK2");
	// Initialize OpenGL graphics state
	InitGraphics();
	// Register callbacks:
	glutDisplayFunc (Display);
	glutReshapeFunc (Reshape);
	glutKeyboardFunc (Keyboard);
	glutMouseFunc (MouseButton);
	glutMotionFunc (MouseMotion);
	glutIdleFunc (IdleFunc);
	glEnable(GL_DEPTH_TEST);
	generateDefaultLevel();
	// Turn the flow of control over to GLUT
	glutMainLoop ();
	return 0;
}