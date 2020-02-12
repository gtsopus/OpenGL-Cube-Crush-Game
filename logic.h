/*GRIGORIOS TSOPOURIDIS, AM:3358
  LIST OF FUNCTIONS USED PRIMARILY IN GAME LOGIC
- fillBoard Fills the board and makes it so that there will be no 3 same cubes in a row
- isNextTo Checks if cubes are next to each other
- findPosition Finds the cube x,y position in the board array
- selectTwo Selects two cubes and exchanges their colors if they are next to each other
- checkDestroyed Finds and destroys the correct cubes after a player move
- destroyArea Destroys an area of cubes according to color
*/

#ifndef _LOGICH_
#define _LOGICH_

using namespace std;

extern int board[15][15];
extern unsigned char canSelect;
extern int selected;
extern int moves;
extern int score;

// fill the game board and prevent 3 cubes in a row
void fillBoard(){
	for(int i = 0; i<15;i++){
		for(int j = 0;j<15;j++){
			int col = (rand()%6)+1;
			board[i][j] = col;
		}
	}

	for(int i = 0; i<15;i++){
		for(int j = 0;j<15;j++){
			int tempL = board[i-1][j];
			int tempU = board[i][j+1];
			while(board[i][j]== tempL || board[i][j] == tempU){
				int col = (rand()%5)+1;
				board[i][j] = col;
			}
		}
	}
	//had some problems with these areas, quick fix may change later
	while(board[6][5] == board[6][6] || board[6][5] == board[5][5]){
		int col = (rand()%5)+1;
		board[6][5] = col;
	}
	while(board[13][8] == board[13][9] || board[13][8] == board[12][8]){
		int col = (rand()%5)+1;
		board[13][8] = col;
	}

	board[10][2] = 1;
}


//check if cubes are next to each other
int isNextTo(int selection1[2], int selection2[2]){
	if(selection1[0] == selection2[0] && selection1[1] == (selection2[1]-1)){
		return 1;
	}else if(selection1[0] == selection2[0] && selection1[1] == (selection2[1]+1)){
		return 1;
	}else if(selection1[1] == selection2[1] && selection1[0] == (selection2[0]-1)){
		return 1;
	}else if(selection1[1] == selection2[1] && selection1[0] == (selection2[0]+1)){
		return 1;
	}
	return 0;
}

void findPosition(int position[2], GLuint id){
	if(id>0){
		position[0] = ceil((id-1)/15);
		int temp = id;
		while(temp > 15){
			temp -=15;
		}
		position[1] = temp-1;
	}
}

//checks around 4 directions of the cube to find if the cubes can be "beaten" and destroys them
//x1 first, x2 second cube, x3 third cube
void destroyArea(int color , int x1, int y1, int x2,int y2, int x3, int y3){
	if(color == 1||color == 2){
		for(int i=-1;i<2;i++){
			for(int j=-1;j<2;j++){

					//bomb points
					if(board[x1+i][y1+j] != -1 && board[x1+i][y1+j] == 6){
						board[x1+i][y1+j] = -1;
						score -=30;
					}
					if(board[x2+i][y2+j] != -1 && board[x2+i][y2+j] == 6){
						board[x2+i][y2+j] = -1;
						score -=30;
					}
					if(board[x3+i][y3+j] != -1 && board[x3+i][y3+j] == 6){
						board[x3+i][y3+j] = -1;
						score -=30;
					}
			}
		}
	}
	if(color == 3){
		for(int i=-3;i<4;i++){
			if(x1 + i < 0 || x2 + i < 0 || x3 + i < 0 || x1 + i > 14 || x2 + i > 14 || x3 + i > 14 ){
				continue;
			}
			for(int j=-3;j<4;j++){
				if(y1 + j < 0 || y2 + j < 0 || y3 + j < 0 || y1 + j > 14 || y2 + j > 14 || y3 + j > 14 ){
					continue;
				}
				if(i>= -1 && i<=1 && j>=-1 && j<=1){
					if(board[x1+i][y1+j] != -1 && board[x1+i][y1+j] == 6){
						board[x1+i][y1+j] = -1;
						score -=30;
					}
					if(board[x2+i][y2+j] != -1 && board[x2+i][y2+j] == 6){
						board[x2+i][y2+j] = -1;
						score -=30;
					}
					if(board[x3+i][y3+j] != -1 && board[x3+i][y3+j] == 6){
						board[x3+i][y3+j] = -1;
						score -=30;
					}



					if(board[x1+i][y1+j] != -1 && board[x1+i][y1+j] != 4){
						board[x1+i][y1+j] = -1;
						score +=2;
					}else{
						score-=1;
					}
					if(board[x2+i][y2+j] != -1 && board[x2+i][y2+j] != 4){
						board[x2+i][y2+j] = -1;
						score +=2;
					}else{
						score-=1;
					}
					if(board[x3+i][y3+j] != -1 && board[x3+i][y3+j] != 4){
						board[x3+i][y3+j] = -1;
						score +=2;
					}else{
						score-=1;
					}				
				}else {
					if(board[x1+i][y1+j] != -1 && board[x1+i][y1+j] == 5){
						board[x1+i][y1+j] = -1;
						score +=3;
					}
					if(board[x2+i][y2+j] != -1 && board[x2+i][y2+j] == 5){
						board[x2+i][y2+j] = -1;
						score +=3;
					}
					if(board[x3+i][y3+j] != -1 && board[x3+i][y3+j] == 5){
						board[x3+i][y3+j] = -1;
						score +=3;
					}
				}				
			}
		}	
	}

	if(color == 4){
		for(int i=-3;i<4;i++){
			if(x1 + i < 0 || x2 + i < 0 || x3 + i < 0 || x1 + i > 14 || x2 + i > 14 || x3 + i > 14){
				continue;
			}
			for(int j=-3;j<4;j++){
				if(y1 + j < 0 || y2 + j < 0 || y3 + j < 0 || y1 + j > 14 || y2 + j > 14 || y3 + j > 14){
					continue;
				}
				if(i>= -1 && i<=1 && j>=-1 && j<=1){
					if(board[x1+i][y1+j] != -1 && board[x1+i][y1+j] == 6){
						board[x1+i][y1+j] = -1;
						score -=30;
					}
					if(board[x2+i][y2+j] != -1 && board[x2+i][y2+j] == 6){
						board[x2+i][y2+j] = -1;
						score -=30;
					}
					if(board[x3+i][y3+j] != -1 && board[x3+i][y3+j] == 6){
						board[x3+i][y3+j] = -1;
						score -=30;
					}				

					if(board[x1+i][y1+j] != -1 && board[x1+i][y1+j] != 5){
						board[x1+i][y1+j] = -1;
					}
					if(board[x2+i][y2+j] != -1 && board[x2+i][y2+j] != 5){
						board[x2+i][y2+j] = -1;
					}
					if(board[x3+i][y3+j] != -1 && board[x3+i][y3+j] != 5){
						board[x3+i][y3+j] = -1;
					}
					continue;
				}else{
					if(board[x1+i][y1+j] != -1 && board[x1+i][y1+j] == 3){
						board[x1+i][y1+j] = -1;
					}
					if(board[x2+i][y2+j] != -1 && board[x2+i][y2+j] == 3){
						board[x2+i][y2+j] = -1;
					}
					if(board[x3+i][y3+j] != -1 && board[x3+i][y3+j] == 3){
							board[x3+i][y3+j] = -1;
					}
				}
			}					
		}	
	}

	if(color == 5){
		for(int i=-3;i<4;i++){
			if(x1 + i < 0 || x2 + i < 0 || x3 + i < 0 || x1 + i > 14 || x2 + i > 14 || x3 + i > 14 ){
				continue;
			}
			for(int j=-3;j<4;j++){
				if(y1 + j < 0 || y2 + j < 0 || y3 + j < 0 || y1 + j > 14 || y2 + j > 14 || y3 + j > 14 ){
					continue;
				}
				if(i>= -1 && i<=1 && j>=-1 && j<=1){
					if(board[x1+i][y1+j] != -1 && board[x1+i][y1+j] == 6){
						board[x1+i][y1+j] = -1;
						score -=30;
					}
					if(board[x2+i][y2+j] != -1 && board[x2+i][y2+j] == 6){
						board[x2+i][y2+j] = -1;
						score -=30;
					}
					if(board[x3+i][y3+j] != -1 && board[x3+i][y3+j] == 6){
						board[x3+i][y3+j] = -1;
						score -=30;
					}


					if(board[x1+i][y1+j] != -1 && board[x1+i][y1+j] != 3){
						board[x1+i][y1+j] = -1;
					}
					if(board[x2+i][y2+j] != -1 && board[x2+i][y2+j] != 3){
						board[x2+i][y2+j] = -1;
					}
					if(board[x3+i][y3+j] != -1 && board[x3+i][y3+j] != 3){
						board[x3+i][y3+j] = -1;
					}	
					continue;				
				}else{
					if(board[x1+i][y1+j] != -1 && board[x1+i][y1+j] == 4){
						board[x1+i][y1+j] = -1;
					}
					if(board[x2+i][y2+j] != -1 && board[x2+i][y2+j] == 4){
						board[x2+i][y2+j] = -1;
					}
					if(board[x3+i][y3+j] != -1 && board[x3+i][y3+j] == 4){
						board[x3+i][y3+j] = -1;
					}
				}
			}					
		}	
	}
}
	

//check board for 3 cubes in a row and destroy them & destroy after cube exchange
void checkDestroyed(){
	//destroy 3 in a row and area
	for(int i = 0; i<15;i++){
		for(int j = 0;j<15;j++){
			int check = 0;
			int tempC = board[i][j];
			if((board[i][j] == board[i-1][j]) && (board[i][j] == board[i+1][j])){
				board[i+1][j] = -1;
				board[i-1][j] = -1;
				board[i][j] = -1;
				if(tempC != -1){
					check = 1;
					destroyArea(tempC,i-1,j,i,j,i+1,j);
				}
			}
			if((tempC == board[i][j-1]) && (board[i][j] == board[i][j+1])){
				board[i][j] = -1;
				board[i][j-1] = -1;
				board[i][j+1] = -1;
				if(tempC != -1){
					check = 1;
					destroyArea(tempC, i,j-1,i,j,i,j+1);
				}
			}
			if((tempC == board[i][j-1]) && (board[i][j] == board[i][j-2])){
				board[i][j] = -1;
				board[i][j-1] = -1;
				board[i][j-2] = -1;
				if(tempC != -1){
					check = 1;
					destroyArea(tempC, i,j,i,j-1,i,j-2);
				}
			}
			if((tempC == board[i][j+1]) && (board[i][j] == board[i][j+2])){
				board[i][j] = -1;
				board[i][j+1] = -1;
				board[i][j+2] = -1;
				if(tempC != -1){
					check = 1;
					destroyArea(tempC, i,j,i,j+1,i,j+2);
				}
			}
			//10 points per explosion
			if(check){score+=10;}
		}
	}
}

void selectTwo(int x, int y, int position[2], int selection1[2],int selection2[2], GLuint id){
	if(canSelect == 1){
		selected ++;
		if(selected > 1){
			//stencil picking to identify item clicked
			glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &id);
			if(selected == 2){
				findPosition(position, id);
				selection1[0] = position[0];
				selection1[1] = position[1];
			}
			if(selected == 3){
				findPosition(position, id);
				selection2[0] = position[0];
				selection2[1] = position[1];
				int temp = board[selection1[0]][selection1[1]];
				if(isNextTo(selection1, selection2) || isNextTo(selection2, selection1)){
					//destroy "enemy" neightboring cube after a move
					board[selection1[0]][selection1[1]] = board[selection2[0]][selection2[1]];
					board[selection2[0]][selection2[1]] = temp;
					//increase move if move is legal to make.
					moves++;

					//destroy cubes
					checkDestroyed();

					//enemy next to && empty filling score
					int col1 = board[selection1[0]][selection1[1]];
					int col2 = board[selection2[0]][selection2[1]]; 
					int enCol1 = 0;
					int enCol2 = 0;
					if(col1 == 3){enCol1 = 5;}
					else if(col1 == 4){enCol1 = 3;}
					else if(col1 == 5){enCol1 = 4;}
					if(col2 == 3){enCol2 = 5;}
					else if(col2 == 4){enCol2 = 3;}
					else if(col2 == 5){enCol2 = 4;}

					int flag = 0;

					if(board[selection1[0]+1][selection1[1]] == enCol1){
						board[selection1[0]+1][selection1[1]] = -1;
						//if destroyed during "destroyed cube filling"
						flag = 1;
					}

					if(board[selection1[0]-1][selection1[1]] == enCol1){
						board[selection1[0]-1][selection1[1]] = -1;
						flag = 1;
					}

					if(board[selection1[0]][selection1[1]+1] == enCol1){
						board[selection1[0]][selection1[1]+1] = -1;
						flag = 1;
					}
					
					if(board[selection1[0]][selection1[1]-1] == enCol1){
						board[selection1[0]][selection1[1]-1] = -1;
						flag=1;
					}
					
					if(board[selection2[0]+1][selection2[1]] == enCol2){
						board[selection2[0]+1][selection2[1]] = -1;
						flag=1;
					}
					if(board[selection2[0]-1][selection2[1]] == enCol2){
						board[selection2[0]-1][selection2[1]] = -1;
						flag=1;
					}

					if(board[selection2[0]][selection2[1]+1] == enCol2){
						board[selection2[0]][selection2[1]+1] = -1;
						flag=1;
					}

					if(board[selection2[0]][selection2[1]-1] == enCol2){
						board[selection2[0]][selection2[1]-1] = -1;
						flag=1;
					}

					if(flag == 1 && (board[selection1[0]][selection1[1]] == -1 || board[selection2[0]][selection2[1]] == -1)){
						score +=2;
					}
					//POINT CHECK
				}
				selected = 1;
			}
		}
	}
}
#endif