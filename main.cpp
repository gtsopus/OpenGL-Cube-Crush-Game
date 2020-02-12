/*GRIGORIOS TSOPOURIDIS, AM:3358
Main file containing initializations, main and additional functions required for core functionalities.
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <fstream>

//my libs
#include "display.h"
#include "texture.h"
#include "keys.h"

using namespace std;

//game window struct
typedef struct{
	int win_id;
	int width;
	int height;
	char * title;
	float field_of_view_angle;
	float z_near;
	float z_far;
} gameWindow;

//variables for key movements
float lx = 0.0f;
float lz = 0.0f;

float tempx = -8.75f;
float tempy = -8.0f;
float tempz = -36.0f;


//texture id initialization
GLuint rock;
GLuint paper;
GLuint scissors;
GLuint bomb;

//initialize game window.
gameWindow win;

//game state & enum and misc. game logic stuff.
enum gameState {INIT = 0, START1 = 1,START2 =2, INGAME = 3,END = 4};
gameState gState = INIT;

int END_MOVES = 30;

int board[15][15] = {0};

int score = 0;

int selected = 0;
unsigned char canSelect = 0;
int moves = 0;

//menu functions
int menu_id;

//menu function
void menuFunc(int num){
	if(num == 0){
		glutDestroyWindow(win.win_id);
		exit(-1);
	}else {
		gState = START1;
		moves = 0;
	}
	//redisplay game window
	glutPostRedisplay();
}
void createMenu(){
	menu_id = glutCreateMenu(menuFunc);
	glutAddMenuEntry("Start",1);
	glutAddMenuEntry("Exit",0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void reshape(int width, int height){

	// GLsizei for non-negative integer // Compute aspect ratio of the new window
 	win.height = height;
	win.width = width;
	if (height == 0) height = 1; // To prevent divide by 0 
	GLfloat aspect = (GLfloat)win.width / (GLfloat)win.height; // Set the viewport to cover the new window 
	glViewport(0, 0, width, height); // Set the aspect ratio of the clipping volume glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(win.field_of_view_angle,aspect ,win.z_near,win.z_far);

}

/* Handler for window-repaint event. 
Call back when the window first appears 
and whenever the window needs to be re-painted.*/ 
void display() 
{ 
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque 
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT); // Clear the color, stencil, depth buffers 
	
	//switch to model view, to place models in the world.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0,0,6,0,0,0,0,1,0);
	
	//put camera into correct position
	glTranslatef(tempx,tempy,tempz);
	glRotatef(lx, 1,0,0);
	glRotatef(lz, 0,1,0);

  	glEnable(GL_STENCIL_TEST);
  	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	//render board depending on gameState
	if(gState == INIT){
		drawBox();
		displayInit();
	}
	else if(gState == START1){
	  	drawBox();
		displayStartWhite();
		usleep(1000000);
		gState = START2;
	}
	else if(gState == START2){
	  	drawBox();	
		displayStartReplace(board);
		gState = INGAME;
	}else if(gState == INGAME){
	  	drawBox();
		displayInGame(board);
		if(moves == END_MOVES){
			gState = END; 
		}
	}else if(gState == END){
		displayEndGame();
	}

}


//opengl init.
void initGL () 
{
	//load the texture images
	rock = loadTexture("rock.png");
	scissors = loadTexture("scissors.png");
	paper = loadTexture("paper.png");
	bomb = loadTexture("bomb.png");

	//background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //Perspective projection
	GLfloat aspect = (GLfloat) win.width / win.height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(win.field_of_view_angle,aspect ,win.z_near,win.z_far);

	//lighting
	glShadeModel(GL_SMOOTH);
	
	GLfloat lightAmbientColour[] = {0.65f,0.65f,0.65f,1.0f};
	GLfloat lightDiffuseColour[] = {0.70f,0.70f,0.70f,1.0f};
	GLfloat lightSpecularColour[] = {1.00f,1.00f,1.00f,1.0f};
	GLfloat lightPosition[] = {0,0,-10};

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lightAmbientColour);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightDiffuseColour);
	glLightfv(GL_LIGHT0,GL_SPECULAR,lightSpecularColour);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
	
	//enable tests/lighting.
    glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

/* Main function: GLUT runs as a console application starting at main() */ 
int main(int argc, char** argv) { 
	//initialize window variables
	win.width = 600;
	win.height = 600;
	win.title = (char *)"VraXaPsa III";
	win.field_of_view_angle = 30;
	win.z_near = 1;
	win.z_far = 600;

	// Initialize GLUT & OpenGL

	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL);
	glutInitWindowSize(win.width, win.height);
	glutInitWindowPosition(50, 50); 
	win.win_id = glutCreateWindow(win.title);

	createMenu();

	glutDisplayFunc(display); 
	glutIdleFunc(display);
	glutSpecialFunc(keySpecialFunc);//for arrow keys
	glutMouseFunc(mouseButton);

	initGL(); // OpenGL initialization 
	glutMainLoop();

	return 0; 
}