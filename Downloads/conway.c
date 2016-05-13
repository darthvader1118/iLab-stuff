#include <stdlib.h>
extern int update(int **board, int width, int height){
		int i, j, col, row, ncount ,x;
		int **copyboard;
		copyboard = malloc(sizeof(int *) * width);
		for(i = 0; i < height; i++){
			copyboard[i] = malloc(sizeof(int *) * height);
		}
		for(i = 0; i < height; i++){
			for(j = 0; j < width; j++){
				copyboard[i][j] = board[i][j];
			}
		}
	for (i = 0; i < height; i++){
		for ( j = 0; j < width; j++){
			 ncount = 0;
			 if(i > 0){
				 ncount += copyboard[i - 1][j];
				 if(j > 0){
					 ncount += copyboard[i -1][j-1];
				 }
				 if(j < width - 1){
					 ncount += copyboard[i - 1][j + 1];
				 }
			 }
			 if(i < height -1){
				 ncount += copyboard[i+1][j];
				 if( j > 0){
					 ncount+= copyboard[i + 1][j - 1];
				 }
				 if( j < width - 1){
					 ncount += copyboard[i + 1][j + 1];
				 }
			 }
			 if(j > 0){
				 ncount += copyboard[i][j - 1];
			 }
			 if(j < width - 1){
				 ncount += copyboard[i][j + 1];
			 }
			 if(board[i][j] == 1){
				 if(ncount == 2 || ncount == 3){
					 board[i][j] = 1;
				 }
				 else{
					 board[i][j] = 0;
				 }
			 }
			 else{
				 if(ncount == 3){
					 board[i][j] = 1;
				 }
			 }
		}
	}
return 0;
}
