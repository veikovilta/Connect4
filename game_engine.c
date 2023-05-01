#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game_engine.h"
#include "board.h"

bool IfWin(int coloredBoard[ROWS][COLS], int playerFlag, int *winRow, int *winCol, int *winType)
{
	//~ DebugBoard(coloredBoard);
	
	//horisontal check
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < NUM_OF_CHECKS_HORISONTALLY; j++)
		{
			if (CheckIfWinHorisontally(j, WIN_LEN, coloredBoard[i], playerFlag))
			{
				*winRow = i; 
				*winCol = j;
				*winType = 0; 
								
				return 1;
			}
		}
	}
	
	//vertical Check 
	for (int i = 0; i < COLS; i++)
	{
		for (int j = 0; j < NUM_OF_CHECKS_VERTICALLY; j++)
		{
			if (CheckIfWinVertically(j, WIN_LEN, coloredBoard, playerFlag, i))
			{
				*winRow = j; 
				*winCol = i;
				*winType = 1; 
				return 1;
			}
		}
	}
	
	//declining diagonal win check  
	
	if (CheckIfWinDiag(coloredBoard, playerFlag, winRow, winCol, winType))
	{
		return 1;
	}
	
	return 0;
}

bool CheckIfWinDiag(int board[ROWS][COLS], int playerFlag, int *winRow, int *winCol, int *winType)
{
    // Check diagonals starting from top-left corner
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 3; j++) {
            if (board[i][j] == playerFlag &&
                board[i+1][j+1] == playerFlag &&
                board[i+2][j+2] == playerFlag &&
                board[i+3][j+3] == playerFlag) {
                
                *winRow = i; 
				*winCol = j;
				*winType = 2;
				
                return true; // Diagonal win found
            }
        }
    }

    // Check diagonals starting from top-right corner
    for (int i = 0; i <= 2; i++) {
        for (int j = 6; j >= 3; j--) {
            if (board[i][j] == playerFlag &&
                board[i+1][j-1] == playerFlag &&
                board[i+2][j-2] == playerFlag &&
                board[i+3][j-3] == playerFlag) {
					
				*winRow = i; 
				*winCol = j;
				*winType = 3;
				
                return true; // Diagonal win found
            }
        }
    }

    // No diagonal win found
    return false;
}

bool CheckIfWinHorisontally(int startMemb, int winLen, int *row, int playerFlag)
{
	int counter = 0;
	
	//printf("\n");
	
	for (int i = startMemb; i < winLen + startMemb; i++)
	{
		//printf("%d", *(row + i));
		
		if (*(row + i) == playerFlag)
		{
			counter++;
		}
	}
	
	//printf("\n");
	
	if (counter == winLen)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CheckIfWinVertically(int startMemb, int winLen, int board[ROWS][COLS], int playerFlag, int col)
{
	int counter = 0;
	
	//~ printf("\n");
	
	for (int i = startMemb; i < winLen + startMemb; i++)
	{
		//~ printf("%d", board[i][col]);
		
		if (board[i][col] == playerFlag)
		{
			counter++;
		}
	}
	
	//~ printf("\n");
	
	if (counter == winLen)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//test main
//~ int main(void)
//~ {
	//~ int coloredBoard[ROWS][COLS] = {{ 0, 0, 0, 0, 0, 0, 0},
									 //~ {0, 0, 0, 0, 0, 0, 0},
									  //~ {0, 0, 0, 0, 0, 0, 0},
									   //~ {0, 0, 0, 0, 0, 0, 0},
										//~ {0, 0, 0, 0, 0, 0, 0},
										 //~ {0, 0, 0, 0, 0, 0, 0}};
						
	//~ for (int k = 0; k < ROWS; k++)
	//~ {
		//~ for (int l = 0; l < COLS; l++)
		//~ {
			//~ printf("%d", coloredBoard[k][l]);
		//~ }
		
		//~ printf("\n");
	//~ }
	
	//~ if (IfWin(coloredBoard))
	//~ {
		//~ printf("Win");
	//~ }
	//~ else
	//~ {
		//~ printf("nothing");
	//~ }
	
	//~ return EXIT_SUCCESS;
//~ }

 
