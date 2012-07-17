/*
 * Template for simple OpenGL / GLUT program under Win32.
 *
 * Based on example by Paul Solt.
 * Link against opengl32, glu32 and glut32.
 *
 * For a tutorial on how to set up a MinGW / Eclipse environment for
 * building OpenGL apps, see this page:
 * http://www.ritgamedev.com/tutorials/glutEclipse/
 *
 * {{PROJECT}}
 * {{PROJECT}l}.cpp
 */

#include <windows.h>

// Necessary in order to get this to compile
#define _STDCALL_SUPPORTED
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>


//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------

const int KWidth = 600;
const int KHeight = 480;


//-----------------------------------------------------------------------------
// Function prototypes
//-----------------------------------------------------------------------------

void init();
void display();


//-----------------------------------------------------------------------------
// Function definitions
//-----------------------------------------------------------------------------

void init()
	{
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	}


void display()
	{
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
	}


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
	{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(KWidth, KHeight);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
	}



