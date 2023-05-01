#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "highscore.h"
#include "board.h"
#include "menu.h"
#include "game_engine.h"


int main(void)
{
    initscr();
    
    keypad(stdscr, TRUE);
    noecho(); 
    start_color();
    
    int coloredBoard[COLORED_ROWS][COLORED_COLS] = {0};
    
    window win[NUM_OF_WINS];
    window board;
    
    WINDOW *mainMenuWin;
    WINDOW *playAgainMenuWin;
    WINDOW *nameMenuWin;
	
    int playerOneNameFlag = 0; 
    int playerTwoNameFlag = 0;
    int winFlag = 0;   
    
    player *pPlayer;
	int nPlayers = 0;
	
	int menuFlag = 0; 
	int ch;
	
    ReadDataFile(FILE_NAME, &nPlayers, &pPlayer);
    
    do
	{
		menuFlag = MainMenu(mainMenuWin); 

		qsort(pPlayer, (size_t)nPlayers, sizeof(player), ComparFuncStructHighscore);

		switch (menuFlag)
		{
			case 0:
				
				clear();
				
				GetPlayerName(&pPlayer, NAME_LEN, &nPlayers, &playerOneNameFlag, 
								&playerTwoNameFlag, nameMenuWin); 
				
				do
				{
					clear(); 
					
					BigWin(board, pPlayer, playerOneNameFlag, playerTwoNameFlag, winFlag);
			
					DrawBoard(win, coloredBoard);
					
					SwitchOptions(win, board, pPlayer, coloredBoard, 
							playerOneNameFlag, playerTwoNameFlag, winFlag, nPlayers);
							
					ReDecleareMatrix(COLS, ROWS, coloredBoard);
					
					getch(); 
					
					clear(); 

					qsort(pPlayer, (size_t)nPlayers, sizeof(player), ComparFuncStructHighscore);
					 
				} while (PlayAgainMenu(playAgainMenuWin)); 
				
				break;
			case 1:
				
				PrintWithNcurses(pPlayer, nPlayers); 
				
				ch = getch();
					
				while (ch != '\n')
				{
					ch = getch();
				}
				
				break;
			case 2:
				
				break;
		}
		
		clear(); 
		
	} while (menuFlag != 2); 
	
	PrintDataFile(FILE_NAME, nPlayers, pPlayer);
	
	free(pPlayer);
	
    endwin();
    return 0;
}

