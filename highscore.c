#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "highscore.h"
#include "menu.h"

void PrintPossibleNames(player **pPlayer, int nPlayers)
{
	mvprintw(15, 20, "ALREADY EXISTING NAMES");
	
	mvprintw(13, 20, "%s", (*pPlayer)->name);

	for (int i = 0; i < nPlayers; i++)
	{
		mvprintw(17 + i, 20, "%s", (*pPlayer + i)->name);
	}
}

void SearchForName(char *name, player *pPlayer, int nPlayers, int *playerNameFlag, int cnt)
{
	int flag = 0; 
	
	for (int i = 0; i < nPlayers + cnt; i++)
	{
		if (!strcmp(name, (pPlayer + i)->name))
		{
			*playerNameFlag = i;
			flag = 1;  
			break;
		}
	}

	if (!flag)
	{
		*playerNameFlag = -1; 
	}
}

void GetPlayerName(player **pPlayer, int max, int *nPlayers, int *playerOneNameFlag, 
					int *playerTwoNameFlag, WINDOW *nameWin)
{
	clear();
	
	char mesg1[]="Enter new Player one name: ";
	char mesg2[]="Enter new Player two name: ";
	int row, col;
	int counter = 0;

	int inputFlag = 0;

	int inputCnt = 0;
	
	int ch;
	
	char tempName[NAME_LEN]; 
	
	player *pTemp = NULL;  
	player *pArr = NULL;

	pArr = *pPlayer;   
					
	getmaxyx(stdscr, row, col);
	
	int numberOfNamesWithNew = *(nPlayers) + 2; 
	int numberOfNames = *(nPlayers); 
	
	for (int i = numberOfNames; i < numberOfNamesWithNew; i++)
	{
		clear(); 
		
		PrintConnect4(); 
		
		if (!inputCnt)
		{
			attron(A_BOLD | A_DIM | A_STANDOUT | A_BLINK);
			mvprintw(11 , 70,"PLAYER ONE");
			attroff(A_BOLD | A_DIM | A_STANDOUT | A_BLINK);
		}
		else
		{
			attron(A_BOLD | A_DIM | A_STANDOUT | A_BLINK);
			mvprintw(11 , 70,"PLAYER TWO");
			attroff(A_BOLD | A_DIM | A_STANDOUT | A_BLINK);
		}
		

		inputFlag = NameMenu(nameWin); 

		if (!inputFlag)
		{

			do
			{
				clear(); 
			
				PrintConnect4();
				HowToUse(FUNCTION_NAME_INPUT);

				
				mvprintw(11, 90, "Search for a name: "); 
				
				echo(); 
				getnstr(tempName, NAME_LEN);
				noecho(); 
				
				if (!inputCnt)
				{
					SearchForName(tempName, *pPlayer, *(nPlayers), playerOneNameFlag, counter); 
				}
				else
				{
					SearchForName(tempName, *pPlayer, *(nPlayers), playerTwoNameFlag, counter); 
				}
				
				
				if (*playerOneNameFlag == -1 || *playerTwoNameFlag == -1)
				{				
					mvprintw(15, 90, "NAME :: %s :: DOES NOT EXIST", tempName); 
					getch(); 
				}
				
			} while (*playerOneNameFlag == -1 || *playerTwoNameFlag == -1);
			
			
		}
		else if (inputFlag)
		{
			clear(); 
			
			counter++;
			
			*nPlayers = *nPlayers + 1; 
			
			pTemp = (player *)realloc(pArr, (unsigned)*(nPlayers) * sizeof(player));
			
			if (pTemp == NULL)
			{
				exit(EXIT_FAILURE); 
			}
			
			PrintConnect4(); 

			HowToUse(FUNCTION_NAME_INPUT);
			
			//PrintPossibleNames(pPlayer, *(nPlayers));

			if (!inputCnt)
			{
				mvprintw(11 , 90,"%s",mesg1);
			}
			else
			{
				mvprintw(11 , 90,"%s",mesg2);
			}

			do
			{  
				
				echo();
				
				getnstr(tempName, NAME_LEN); 

				noecho(); 
				
				if (CheckName(tempName, max, *(nPlayers), *pPlayer, counter))
				{
					ch = getch();
					
					while (ch != '\n')
					{
						ch = getch();
					}
					
					clear();
					
					PrintConnect4(); 

					HowToUse(FUNCTION_NAME_INPUT);
					
					if (!inputCnt)
					{
						mvprintw(11 , col / 2,"%s",mesg1);
					}
					else
					{
						mvprintw(11 , col / 2,"%s",mesg2);
					}
					
					echo();
					getnstr(tempName, NAME_LEN);
					noecho(); 
				}
				
				
				
			} while (CheckName(tempName, max, *(nPlayers), *pPlayer, counter));
			
			(pTemp + i)->score = 0;
			
			if (!inputCnt)
			{
				*playerOneNameFlag = *nPlayers - 1;
			}
			else 
			{
				*playerTwoNameFlag = *nPlayers - 1;
			}
			
			strcpy((pTemp + (*nPlayers - 1))->name, tempName);   
			pArr = pTemp;
		}
		
		inputCnt++;  
		
		clear(); 
	} 

	*pPlayer = pArr;
	
}

bool CheckName(char *name, int maxLen, int nPlayers, player *pPlayer, int cnt)
{
	long unsigned int len = strlen(name); 
	
	//check if name already exists 
	for (int i = 0; i < nPlayers - cnt; i++)
	{
		if (!strcmp(name, (pPlayer + i)->name))
		{
			mvprintw(20, 90, "Name already exists");
			mvprintw(21, 90, "PRESS ENTER TO COUNTINUE");
			return 1;
		}
	}
	
	//check if name is longer than allowed
	if (len > (long unsigned int)maxLen)
	{
		mvprintw(20, 90, "Name is to long");
		mvprintw(21, 90, "PRESS ENTER TO COUNTINUE");
		return 1; 
	}
	
	return 0; 
}

void PrintWithNcurses(player *pPlayer, int nPlayers)
{
	clear();
	
	PrintConnect4();
	
	mvprintw(11 ,80 , "%3s %10s %12s", "nr", "NAME", "WINS");
	mvprintw(12 ,80 , "====================================");
	
	for (int i = 0; i < nPlayers; i++)
	{ 
		mvprintw(13 + i, 80, "%3d %10s %10d wins", i + 1, (pPlayer + i)->name, (pPlayer + i)->score);
	}
	
	attron(A_BLINK | A_STANDOUT); 
	mvprintw(11, 40, "PRESS ENTER TO LEAVE"); 
	attroff(A_BLINK | A_STANDOUT);
	
	refresh(); 
}

int ComparFuncStructHighscore(const void *x, const void *y)
{
	if (((player *)x)->score > ((player *)y)->score)
	{
		return -1;
	}
	else if (((player *)x)->score < ((player *)y)->score)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

void PrintDataFile(char *fileName, int nPlayers, player *pPlayer)
{
	FILE *foutput = fopen(fileName, "w");
	
	if (foutput == NULL)
	{
		exit(EXIT_FAILURE);
	}

	int i;
	
	fprintf(foutput, "%d\n", nPlayers);
	
	for (i = 0; i < nPlayers; i++)
	{
		fprintf(foutput, "%s %d\n", (pPlayer + i)->name, (pPlayer + i)->score);
	}
	
	fclose(foutput);
}

void ReadDataFile(char *fileName, int *nPlayers, player **pPlayer)
{
	FILE *finput = fopen(fileName, "r");
	
	if (finput == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	fscanf(finput, "%d", nPlayers); 
	
	*pPlayer = (player*)malloc((unsigned)*nPlayers * sizeof(player)); 
	
	if(pPlayer == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	int i = 0;
	
	while (fscanf(finput, "%s %d", (*pPlayer + i)->name, &(*pPlayer + i)->score) == 2)
	{
		i++;
	} 
	
	fclose(finput);
}
