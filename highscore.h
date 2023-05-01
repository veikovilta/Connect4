#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#define FILE_NAME "HIGHSCORE.txt"
#define NAME_LEN 10

typedef struct
{
	char name[NAME_LEN];
	int score;
	
}player;

void PrintPossibleNames(player **pPlayer, int nPlayers); 
void ReadDataFile(char *fileName, int *nPlayers, player **pPlayer);
void PrintDataFile(char *fileName, int nPlayers, player *pPlayer);
int ComparFuncStructHighscore(const void *x, const void *y);
void PrintWithNcurses(player *pPlayer, int nPlayers);
void GetPlayerName(player **pPlayer, int max, int *nPlayers, int *playerOneNameFlag, 
					int *playerTwoNameFlag, WINDOW *nameWin);
bool CheckName(char *name, int maxLen, int nPlayers, player *pPlayer, int cnt); 
void SearchForName(char *name, player *pPlayer, int nPlayers, int *playerNameFlag, int cnt); 

#endif
