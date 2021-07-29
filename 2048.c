#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SIZE 4
//Code written by Ethan Woollet - NOV2020
void displayBoard(int board[][SIZE]);
void shiftBoard(int board[][SIZE], char direction);
int winLoseCheck(int board[][SIZE]);
void newTile(int board[][SIZE], int turns);

int main(){
	srand(time(0));
	int turns=0, board[SIZE][SIZE], win = 0;
	char input, dir;
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			board[i][j] = 0;
		}
	}
	printf("Would you like to play 2048?(y/n)\n");
	gets(&input);
	if(input == 'y' || input == 'Y'){
		system("cls");
		newTile(board, turns);
		newTile(board, turns);
		displayBoard(board);
		for( ; win == 0 ; turns++){
			printf("What Direction?\n(w for up, d for right, s for down, a for left)\n");
			gets(&dir);
			if((dir != 'w') && (dir != 'a') && (dir != 's') && (dir != 'd')){
				printf("'%c' Is an invalid direction!\n\n", dir);
				turns--;
				continue;
			}
			if(win == 0){
				system("cls");
			}
			shiftBoard(board, dir);
			newTile(board, turns);
			displayBoard(board);
			win = winLoseCheck(board);
		}
	}
	if(winLoseCheck(board) == 1){
				printf("You Won in %d Turns!\n\nThanks for playing! <3\n", turns);
	}
	else if(winLoseCheck(board) == -1){
		printf("\nYou Lost in %d Turns!\n\nBetter luck next time\n", turns);
	}
	else{
		printf("\nGoodbye\n");
	}
	printf("\nSee you later!\n\n");
	return 0;
}

void displayBoard(int board[][SIZE]){
	for(int i=0; i<(SIZE*6 + (SIZE-1)*2); i++){
		printf("-");
	}
	printf("\n");
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			if(board[i][j] != 0){
				printf("[%4d]\t", board[i][j]);
			}
			else
				printf("[    ]\t");
		}
		printf("\n");
	}
	for(int i=0; i<(SIZE*6 + (SIZE-1)*2); i++){
		printf("-");
	}
	printf("\n");
}

void newTile(int board[][SIZE], int turns){
	if (winLoseCheck(board) == -1){
		return;
	}
	int pos, four, i, j;
	for( ; ;){
		pos = 1 + rand()%(SIZE*SIZE), four = rand()%3;
		i = pos/SIZE, j = pos%SIZE;
		if(board[i][j] == 0)
			break;
	}
	printf("New tile: (%d,%d)\n", j+1, i+1);
	if(turns<= 15){
		board[i][j] = 2;
	}
	else if(turns > 20){
		if(four == 0){
			board[i][j] = 4;
		}
		else{
			board[i][j] = 2;
		}
	}
}

int winLoseCheck(int board[][SIZE]){
	int spaceTile=0, winTile=0;
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			if(board[i][j] == 0){
				spaceTile++;
			}
			else if(board[i][j] == 2048){
				winTile++;
			}
		}
	}
	if(spaceTile == 0){
		return -1;
	}
	else if(winTile >=1){
		return 1;
	}
	else
		return 0;
}

void shiftBoard(int board[][SIZE], char direction){
	switch(direction){
		case 'w' : //up
			for(int i=0; i<SIZE-1; i++){
				for(int j=0; j<SIZE; j++){
					if(board[i][j] == board[i+1][j]){
						board[i][j] += board[i+1][j];
						board[i+1][j] = 0;
					}
					else if(board[i][j] == 0){
						board[i][j] += board[i+1][j];
						board[i+1][j] = 0;
						i=0, j=-1;
					}
				}
			}
			break;
		case 'd' : //right
			for(int i=0; i<SIZE; i++){
				for(int j=SIZE-1; j>0; j--){
					if(board[i][j] == board[i][j-1]){
						board[i][j] += board[i][j-1];
						board[i][j-1] = 0;
					}
					else if(board[i][j] == 0){
						board[i][j] += board[i][j-1];
						board[i][j-1] = 0;
						i=0, j=SIZE;
					}
				}
			}
			break;
		case 's' : //down
			for(int i=SIZE-1; i>0; i--){
				for(int j=0; j<SIZE; j++){
					if(board[i][j] == board[i-1][j]){
						board[i][j] += board[i-1][j];
						board[i-1][j] = 0;
					}
					else if(board[i][j] == 0){
						board[i][j] += board[i-1][j];
						board[i-1][j] = 0;
						i=SIZE-1, j=-1;
					}
				}
			}
			break;
		case 'a' : //left
			for(int i=0; i<SIZE; i++){
				for(int j=0; j<SIZE-1; j++){
					if(board[i][j] == board[i][j+1]){
						board[i][j] += board[i][j+1];
						board[i][j+1] = 0;
					}
					else if(board[i][j] == 0){
						board[i][j] += board[i][j+1];
						board[i][j+1] = 0;
						i=0, j=-1;
					}
				}
			}
			break;
	}
}