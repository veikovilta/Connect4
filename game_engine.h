#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#define ROWS 6
#define COLS 7
#define NUM_OF_CHECKS_HORISONTALLY 4
#define NUM_OF_CHECKS_VERTICALLY 3
#define WIN_LEN 4
#define PLAYER_ONE 1

bool IfWin(int coloredBoard[ROWS][COLS], int playerFlag, int *winRow, int *winCol, int *winType); 
bool CheckIfWinHorisontally(int startMemb, int winLen, int *row, int playerFlag);
bool CheckIfWinVertically(int startMemb, int winLen, int board[ROWS][COLS], int playerFlag, int col);
bool CheckIfWinDiag(int board[ROWS][COLS], int playerFlag, int *winRow, int *winCol, int *winType); 

#endif
