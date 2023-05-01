#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#define COLORED_ROWS 6
#define COLORED_COLS 7
#define COLS 7
#define ROWS 6
#define PLAYER_ONE 1
#define PLAYER_TWO 2
#define NUM_OF_WINS 42 
#define COLOR_PLAYER_ONE 1
#define COLOR_PLAYER_TWO 2
#define COLOR_BIG_WIN 3
#define SMALL_WIN_START_Y maxY / 5 + 2
#define SMALL_WIN_Y_STEP ((maxY - (maxY / 5) + 3) / ROWS)
#define SMALL_WIN_X_STEP (maxX - 2 * (maxX / 5)) / COLS
#define SMALL_WIN_START_X maxX / 5 + 3
#define SMALL_WIN_X_SIZE (maxX - 2 * (maxX / 5)) / (COLS + 4)
#define SMALL_WIN_Y_SIZE (maxY - (maxY / 5)) / (ROWS + 3)
#define BIG_WIN_X_SIZE maxX - 2 * (maxX / 5)
#define BIG_WIN_Y_SIZE maxY - (maxY / 5)
#define BIG_WIN_START_Y maxY / 5
#define BIG_WIN_START_X maxX / 5
#define COL_FILL_CONSTANT 10
#define SHOW_WIN 3
#define COLOR_SHOW_WIN 4

typedef struct 
{
	WINDOW *win;
	int startX;
	int startY;
	 
}window;

void PrintHighscoreNextToBoard(player *pPlayer, int nPlayers); 
void PrintPlayerInfo(player *pPlayer, int playerOneNameFlag, int playerTwoNameFlag, int winFlag); 
void ShowWin(int winRow, int winCol, int winType, int coloredWin[COLORED_ROWS][COLORED_COLS]); 
void ReDecleareMatrix(int cols, int rows, int matrix[ROWS][COLS]); 
int SwitchOptions(window win[], window board, player *pPlayer, int coloredWin[COLORED_ROWS][COLORED_COLS], 
					int playerOneNameFlag, int playerTwoNameFlag, int winFlag, int nPlayers); 
void DrawBoard(window win[], int coloredWin[COLORED_ROWS][COLORED_COLS]);
int FindMinRow(int selectedCol, int coloredWin[COLORED_ROWS][COLORED_COLS]);
void DebugBoard(int coloredWin[COLORED_ROWS][COLORED_COLS]);
void BigWin(window board, player *pPlayer, int playerOneNameFlag, int playerTwoNameFlag, int winFlag); 
void PrintCoinCorCol(int selected, int playerFlag, const char* options[COLORED_COLS], int maxX, int maxY);

#endif
