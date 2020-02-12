/*GRIGORIOS TSOPOURIDIS, AM:3358
  LIST OF INPUT RELATED FUNCTIONS(MOUSE,KEYBOARD)
- mouseButton
- keySpecialFunc*/

#include "logic.h"

extern float tempx;
extern float tempy;
extern float tempz;

using namespace std;

extern float angle;
extern float angle2;

extern float lx;
extern float lz;

extern int board[15][15];
extern unsigned char canSelect;
extern int selected;

int position[2];
GLuint id = 0;//item ID saved in stencil buffer

int selection1[2];
int selection2[2];


//mouse func
void mouseButton(int button, int state, int x, int y) {
	//select object based on mouse click.
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP && selected <3) {
			selectTwo(x,y,position, selection1, selection2, id);
		}
	}
}

//function that handles special key-pressed events
void keySpecialFunc(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			if(lz<45)
				lz+= 1;
			break;
		case GLUT_KEY_DOWN:
			if(lz>-45)
				lz-= 1;
			break;
		case GLUT_KEY_RIGHT:
			if(lx<45)
				lx+= 1;
			break;
		case GLUT_KEY_LEFT:
			if(lx >-45)
				lx-=1;
			break;
	}
	glutPostRedisplay();
}

