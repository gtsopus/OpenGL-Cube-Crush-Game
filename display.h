/**GRIGORIOS TSOPOURIDIS, AM:3358
  LIST OF FUNCTIONS RELATED TO GAME DISPLAY:
- drawBox
- selectColour
- drawCube
- displayInit
- displayStartWhite
- displayStartReplace
- displayInGame
- displayEndGame
- displayText

add info: 1 = blue, 2 = red, 3 = scissors, 4= rock, 5 = paper, -1 = Destroyed cube
**/

#ifndef _DISPLAYH_
#define _DISPLAYH_

#include <string.h>
#include "logic.h"
using namespace std;

extern GLuint rock;
extern GLuint paper;
extern GLuint scissors;
extern GLuint bomb;

extern int moves;

extern int score;

extern unsigned char canSelect;

float colour[3];
void selectColour(int col){
	if(col == 1){
		//blue
		colour[0] = 0.0f;
		colour[1] = 0.0f;
		colour[2] = 0.70f;
	}else if(col == 2){
		//red
		colour[0] = 0.7f;
		colour[1] = 0.0f;
		colour[2] = 0.0f;
	}else if(col == -1){
		//destroyed cube (black cube)
		colour[0] = 0.0f;
		colour[1] = 0.0f;
		colour[2] = 0.0f;
	}
}


//DRAWING A CUBE
void drawCube(int tex, float colr[3]){
	//disable texturing in order to make the colored cubes
	glDisable(GL_TEXTURE_2D);
	//check if cube is textured, if it is enable texturing.
	if(tex >= 3){
		glEnable(GL_TEXTURE_2D);
		if(tex == 3){
			glBindTexture(GL_TEXTURE_2D,scissors);
		}else if(tex == 4){
			glBindTexture(GL_TEXTURE_2D,rock);
		}else if(tex == 5){
			glBindTexture(GL_TEXTURE_2D,paper);
		}else if(tex == 6){
			glBindTexture(GL_TEXTURE_2D,bomb);
		}
	}
	//only textures the front and back sides, for better visuals.
	//FRONT SIDE
	glBegin(GL_POLYGON);
		glColor3f(   colr[0]-0.3,colr[1]-0.3,colr[2]-0.3 );
		
		glTexCoord2f(1.0f,0.0f);
		glVertex3f(  0.5, -0.5, -0.5 );

		glTexCoord2f(1.0f,1.0f);
		glVertex3f(  0.5,  0.5, -0.5 );

		glTexCoord2f(0.0f,1.0f);
		glVertex3f( -0.5,  0.5, -0.5 );

		glTexCoord2f(0.0f,0.0f);
		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();

	//BACK SIDE
	glBegin(GL_POLYGON);
		glColor3f(   colr[0],colr[1],colr[2] );

		glTexCoord2f(1.0f,0.0f);
		glVertex3f(  0.5, -0.5, 0.5 );

		glTexCoord2f(1.0f,1.0f);
		glVertex3f(  0.5,  0.5, 0.5 );

		glTexCoord2f(0.0f,1.0f);
		glVertex3f( -0.5,  0.5, 0.5 );

		glTexCoord2f(0.0f,0.0f);
		glVertex3f( -0.5, -0.5, 0.5 );
	glEnd();

	//RIGHT SIDE
	glBegin(GL_POLYGON);
		glColor3f(   colr[0]-0.3,colr[1]-0.3,colr[2]-0.3 );

		glVertex3f( 0.5, -0.5, -0.5 );
		glVertex3f( 0.5,  0.5, -0.5 );
		glVertex3f( 0.5,  0.5,  0.5 );
		glVertex3f( 0.5, -0.5,  0.5 );
	glEnd();

	//LEFT SIDE
	glBegin(GL_POLYGON);
		glColor3f(   colr[0]-0.3,colr[1]-0.3,colr[2]-0.3 );

		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();

	//TOP SIDE
	glBegin(GL_POLYGON);
		glVertex3f(  0.5,  0.5,  0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
	glEnd();

	//BOTTOM SIDE
	glBegin(GL_POLYGON);
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

//draws a box contaning all the cubes
void drawBox(){
	glPushMatrix();
	glScalef(19.5f,18.4f,5.0f);
	glTranslatef(0.45f,0.45f,0.0f);

	glBegin(GL_POLYGON);
		glColor3f(0.5f-0.1,0.35f-0.1,0.05f);

		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();

	//RIGHT SIDE
	glBegin(GL_POLYGON);
		glColor3f(0.5f,0.35f,0.05f);
		glVertex3f( 0.5, -0.5, -0.5 );
		glVertex3f( 0.5,  0.5, -0.5 );
		glVertex3f( 0.5,  0.5,  0.5 );
		glVertex3f( 0.5, -0.5,  0.5 );
	glEnd();

	//LEFT SIDE
	glBegin(GL_POLYGON);
		glColor3f(0.81f,0.67f,0.25f);
		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();

	//TOP SIDE
	glBegin(GL_POLYGON);
		glColor3f(0.81f,0.67f,0.25f);
		glVertex3f(  0.5,  0.5,  0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5, -0.5 );
		glVertex3f( -0.5,  0.5,  0.5 );
	glEnd();

	//BOTTOM SIDE
	glBegin(GL_POLYGON);
		glColor3f(0.5f,0.35f,0.05f);
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5,  0.5 );
		glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();

	glPopMatrix();

}


void displayText(string str, int x, int y){
	int l=str.length(); // see how many characters are in text string.

	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	gluOrtho2D(0, 600, 0, 600);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	glColor3f(1.0f,1.0f,1.0f);
	for(int k=0; k<l; k++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[k]);
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_LIGHTING);


}

void displayInit(){
	float beige[3] = {0.957f,0.8906f,0.769531f};
	for(int i = 0;i<15;i++){
		for(int j=0;j<15;j++){
			glPushMatrix();
				glTranslatef(0.0+1.25*i,0.0+1.2*j,0.0);
				drawCube(1,beige);
			glPopMatrix();
		}
	}
		
	glColor3f(1.0f,1.0f,1.0f);
	displayText(" Welcome, press right click and select start from the menu.",10,570);
	glutSwapBuffers();
}

void displayStartWhite(){
	float white[3] = {1.0f,1.0f,1.0f};
	for(int i = 0;i<15;i++){
		for(int j=0;j<15;j++){
			glPushMatrix();
				glTranslatef(0.0+1.25*i,0.0+1.2*j,0.0);
				drawCube(1,white);
			glPopMatrix();
		}
	}
	glutSwapBuffers();
}

//after random colors
void displayInGame(int board[15][15]){
	int counter = 0;


	for(int i = 0;i<15;i++){
		for(int j=0;j<15;j++){
			selectColour(board[i][j]);
			glPushMatrix();
				glTranslatef(0.0+1.25*i,0.0+1.2*j,0.0);
				glStencilFunc(GL_ALWAYS, counter + 1, -1);
				glStencilMask(0xFF); // enable writing to the stencil buffer

				drawCube(board[i][j],colour);
			glPopMatrix();
			counter++;
		}
	}
	glColor3f(1.0f,1.0f,1.0f);
	displayText("Score: " + to_string(score),450,575);
	displayText("Moves Left: " + to_string(30 - moves),10,575);

	glutSwapBuffers();
}

int done = 0;
void displayStartReplace(int board[15][15]){
	if(done == 0){
	fillBoard();
	for(int i = 0;i<15;i++){
		for(int j=0;j<15;j++){
			int col = board[i][j];
			selectColour(col);
			usleep(5000);
			glPushMatrix();
				glTranslatef(0.0+1.25*i,0.0+1.2*j,0.0);
				drawCube(col, colour);
			glPopMatrix();
			
			glutSwapBuffers();
		}
	}
	done = 1;
	}

	displayInGame(board);
	canSelect = 1;
}

void displayEndGame(){
	glColor3f(1.0f,1.0f,1.0f);
	displayText("GAME OVER!",215,300);
	displayText("Moves: " + to_string(moves),10,570);
	displayText("Score: " + to_string(score),10,545);
    glutSwapBuffers();
}

#endif