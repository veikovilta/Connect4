#include <ncurses.h>
#include <stdbool.h>
#include "highscore.h"
#include "menu.h"
#include "board.h"
#include "game_engine.h"

void PrintHighscoreNextToBoard(player *pPlayer, int nPlayers)
{
	int maxY, maxX; 
	
	getmaxyx(stdscr, maxY, maxX); 

	int startRow = BIG_WIN_START_X + BIG_WIN_X_SIZE + 2;
	int startCol = BIG_WIN_START_Y; 
	
	mvprintw(startCol, startRow, "HIGHSCORE");
	mvprintw(startCol + 1, startRow, "nr     name      wins"); 
	
	for (int i = 0; i < nPlayers; i++)
	{
		mvprintw(startCol + i + 2, startRow, "%2d) %7s %8d", i + 1, (pPlayer + i)->name, (pPlayer + i)->score); 
	}
}

void ReDecleareMatrix(int cols, int rows, int matrix[ROWS][COLS])
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			matrix[i][j] = 0; 
		}
	}
}

void BigWin(window board, player *pPlayer, int playerOneNameFlag, int playerTwoNameFlag, int winFlag)
{
	//big win 
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    
    init_pair(COLOR_PLAYER_ONE,COLOR_BLUE, COLOR_RED);
    init_pair(COLOR_PLAYER_TWO,COLOR_BLUE, COLOR_CYAN);
    init_pair(COLOR_BIG_WIN,COLOR_BLUE, COLOR_YELLOW);

    
    board.win = newwin(BIG_WIN_Y_SIZE, BIG_WIN_X_SIZE, BIG_WIN_START_Y, BIG_WIN_START_X);

    wbkgd(board.win, COLOR_PAIR(COLOR_BIG_WIN));
    
    PrintPlayerInfo(pPlayer, playerOneNameFlag, playerTwoNameFlag, winFlag); 
    
    refresh(); 
    wrefresh(board.win);
}

void PrintPlayerInfo(player *pPlayer, int playerOneNameFlag, int playerTwoNameFlag, int winFlag)
{
	init_pair(COLOR_SHOW_WIN, COLOR_BLUE, COLOR_GREEN);
    //draw player info
    
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    
    WINDOW *playerOne = newwin(BIG_WIN_START_Y, maxX - (BIG_WIN_START_X + BIG_WIN_X_SIZE), 0, 0);    
    box(playerOne, 0, 0);
    
    WINDOW *playerTwo = newwin(BIG_WIN_START_Y, maxX - BIG_WIN_START_X, 0, BIG_WIN_X_SIZE + BIG_WIN_START_X);
    box(playerTwo, 0, 0);
    
    if (winFlag == PLAYER_ONE)
	{
		wbkgd(playerOne, COLOR_PAIR(COLOR_SHOW_WIN));
	}
	else if (winFlag == PLAYER_TWO)
	{
		wbkgd(playerTwo, COLOR_PAIR(COLOR_SHOW_WIN));
	}
    
    mvwprintw(playerOne, 1, 1, "PLAYER ONE");
    mvwprintw(playerOne, 3, 1, "Name: %s", (pPlayer + playerOneNameFlag)->name);
    mvwprintw(playerOne, 5, 1, "Color: RED");
    mvwprintw(playerOne, 7, 1, "Score: %d wins", (pPlayer + playerOneNameFlag)->score);
    
    mvwprintw(playerTwo, 1, 1, "PLAYER TWO");
    mvwprintw(playerTwo, 3, 1, "Name: %s", (pPlayer + playerTwoNameFlag)->name);
    mvwprintw(playerTwo, 5, 1, "Color: CYAN");
    mvwprintw(playerTwo, 7, 1, "Score: %d wins", (pPlayer + playerTwoNameFlag)->score);
    
    refresh();
    
    wrefresh(playerOne);
    wrefresh(playerTwo);
}

void PrintCoinCorCol(int selected, int playerFlag, const char* options[COLORED_COLS], int maxX, int maxY)
{
	init_pair(COLOR_PLAYER_ONE,COLOR_BLUE, COLOR_RED);
    init_pair(COLOR_PLAYER_TWO,COLOR_BLUE, COLOR_CYAN);
	
	for (int i = 0; i < 7; i++) 
	{
		if (i == selected && playerFlag == PLAYER_ONE) 
		{
			attron(COLOR_PAIR(COLOR_PLAYER_ONE));
		}
		else  if (i == selected && playerFlag == PLAYER_TWO)
		{
			attron(COLOR_PAIR(COLOR_PLAYER_TWO));
		}
		else
		{
			attron(A_NORMAL);
		}

		for (int j = 0; j < SMALL_WIN_Y_SIZE; j++)
		{
			mvprintw(SMALL_WIN_START_Y - 4 - j, SMALL_WIN_START_X + i * SMALL_WIN_X_STEP, "%s",  options[i]);
		}
		
		if (i == selected && playerFlag == PLAYER_ONE) 
		{
			attroff(COLOR_PAIR(COLOR_PLAYER_ONE));
		}
		else if (i == selected && playerFlag == PLAYER_TWO)
		{
			attroff(COLOR_PAIR(COLOR_PLAYER_TWO));
		}
		else
		{
			attroff(A_NORMAL);
		}
	}

	refresh();
}

int SwitchOptions(window win[], window board, player *pPlayer, int coloredWin[COLORED_ROWS][COLORED_COLS], 
					int playerOneNameFlag, int playerTwoNameFlag, int winFlag, int nPlayers)
{	
	curs_set(0);
	
    const char* options[COLORED_COLS] = {"           ", "           ", 
										"           ", "           ", 
										"           ", "           ", "           "};
    int selected = 0;
    int selectedRow;
    int flag = 0;
    int playerFlag = 0;
	int maxY, maxX;
	int winRow; 
	int winCol; 
	int winType; 
	
    while (true) 
    {
		getmaxyx(stdscr, maxY, maxX);
		
		if (flag == 0)
		{
			playerFlag = PLAYER_ONE;
		}
		else if (flag == 1)
		{
			playerFlag = PLAYER_TWO;
		}
		
		DrawBoard(win, coloredWin);
		
		PrintHighscoreNextToBoard(pPlayer, nPlayers); 
		
		PrintCoinCorCol(selected, playerFlag, options, maxX, maxY);
		
        int ch = getch();
        
        switch (ch) 
        {
            case KEY_LEFT:
                if (selected > 0) 
                {
                    selected--;
                }
                
                break;
            case KEY_RIGHT:
                if (selected < 6) 
                {
                    selected++;
                }
                
                break;
            case '\n':
                
                mvprintw(0, 90, " ");
                
                if (FindMinRow(selected, coloredWin) != COL_FILL_CONSTANT)
				{
					selectedRow = FindMinRow(selected, coloredWin);
					coloredWin[selectedRow][selected] = playerFlag;
					
					if (IfWin(coloredWin, playerFlag, &winRow, &winCol, &winType))
					{
						if (playerFlag == PLAYER_ONE)
						{
							winFlag = PLAYER_ONE; 
							(pPlayer + playerOneNameFlag)->score++; 
						}
						else
						{
							winFlag = PLAYER_TWO;
							(pPlayer + playerTwoNameFlag)->score++;
						}
						
					}
					
					BigWin(board, pPlayer, playerOneNameFlag, playerTwoNameFlag, winFlag);
					DrawBoard(win, coloredWin);
					
					if (flag == 0)
					{
						flag = 1;
					}
					else if (flag == 1)
					{
						flag = 0;
					}
					
				}
		
                refresh();
                break;
            default:
                break;
                
        }
		
		if (IfWin(coloredWin, playerFlag, &winRow, &winCol, &winType))
		{
			ShowWin(winRow, winCol, winType, coloredWin);
			PrintPlayerInfo(pPlayer, playerOneNameFlag, playerTwoNameFlag, winFlag);  
			DrawBoard(win, coloredWin);
			
			break;
		}
    }
    
    return playerFlag;

}

void ShowWin(int winRow, int winCol, int winType, int coloredWin[COLORED_ROWS][COLORED_COLS])
{
	switch (winType)
	{
		case 0:
			
			for (int i = winCol; i < winCol + 4; i++)
			{
				coloredWin[winRow][i] = SHOW_WIN; 
			}
			
			break;
		case 1:
			
			for (int i = winRow; i < winRow + 4; i++)
			{
				coloredWin[i][winCol] = SHOW_WIN; 
			}
			
			break;
		case 2:
			
			for (int i = 0; i < 4; i++)
			{
                coloredWin[winRow + i][winCol + i] = SHOW_WIN;
			}
			
			break;
		case 3:
			
			for (int i = 0; i < 4; i++)
			{
                coloredWin[winRow + i][winCol - i] = SHOW_WIN;
			}
			
			break;

	}
	
}

int FindMinRow(int selectedCol, int coloredWin[COLORED_ROWS][COLORED_COLS])
{
	int row = COL_FILL_CONSTANT;
	
	for (int i = ROWS - 1; i >= 0; i--)
	{	
		if (coloredWin[i][selectedCol] == 0)
		{
			row = i;
			break;
		}
	}
	
	return row;
}

//loop for printig out the values for connect 4 board
void DebugBoard(int coloredWin[COLORED_ROWS][COLORED_COLS])
{
	for (int k = 0; k < COLORED_ROWS; k++)
	{
		for (int l = 0; l < COLORED_COLS; l++)
		{
			mvprintw(30 + k, 1 + l, "%d", coloredWin[k][l]);
		}
	}
}

void DrawBoard(window win[], int coloredWin[COLORED_ROWS][COLORED_COLS])
{
	//DebugBoard(coloredWin);

	HowToUse(FUNCTION_GAME_BOARD); 
	
	int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    
    init_pair(COLOR_PLAYER_ONE,COLOR_BLUE, COLOR_RED);
    init_pair(COLOR_PLAYER_TWO,COLOR_BLUE, COLOR_CYAN);
    init_pair(COLOR_SHOW_WIN, COLOR_BLUE, COLOR_GREEN);
    
    int startingY = SMALL_WIN_START_Y;
    int row = 0;
    int cols = 0;
    int i = 0;
    
    while(i < NUM_OF_WINS) 
	{
		if (i != 0)
		{
			if (i % COLS == 0)
			{
				row++;
				cols = 0;
				startingY += SMALL_WIN_Y_STEP; 
			}
		}
		
		win[i].startY = startingY;
		
		win[i].startX = SMALL_WIN_START_X + (cols * SMALL_WIN_X_STEP);
		
		win[i].win = newwin(SMALL_WIN_Y_SIZE, SMALL_WIN_X_SIZE, win[i].startY, win[i].startX);
	
		if (coloredWin[row][cols] != 0)
		{
			if (coloredWin[row][cols] == PLAYER_ONE)
			{
				wbkgd(win[i].win, COLOR_PAIR(COLOR_PLAYER_ONE));
			}
			else if (coloredWin[row][cols] == PLAYER_TWO)
			{
				wbkgd(win[i].win, COLOR_PAIR(COLOR_PLAYER_TWO));
			}
			else if (coloredWin[row][cols] == SHOW_WIN)
			{
				wbkgd(win[i].win, COLOR_PAIR(COLOR_SHOW_WIN));
			}
			
		}
		
		wrefresh(win[i].win);
		
		i++;
		cols++; 
	}
}
