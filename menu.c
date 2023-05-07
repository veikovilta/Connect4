#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "highscore.h"
#include "menu.h"

char *mainMenu[] = {
                        "NEW GAME",
                        "HIGHSCORE",
                        "LEAVE GAME",
                  };
                  
char *playAgainMenu[] = {
                        "PLAY AGAIN",
                        "MAIN MENU",
                  };
                  
char *nameMenu[] = {
                        "NEW NAME",
                        "SEARCH NAME",
                  };

int MainMenu(WINDOW *mainMenuWin)
{
	curs_set(0); 
	
	int maxX, maxY;
	
	int selected = 0;
	
	PrintConnect4();

	HowToUse(FUNCTION_MENU);

	getmaxyx(stdscr, maxY, maxX);
	
	mainMenuWin = newwin(7, 13, 10, maxX / 2 - 13);
	
	box(mainMenuWin, 0, 0);
	
	refresh();
	
	wrefresh(mainMenuWin); 
	
	int flag = 3;
	
	while (true) 
    {
        getmaxyx(stdscr, maxY, maxX);
        
        // Print the menu options, with the selected option highlighted using standout
        for (int i = 0; i < 3; i++) 
        {
            if (i == selected) 
            {
                attron(A_STANDOUT);
            }
			
			attron(A_BOLD);
			attron(A_DIM);
			
			mvprintw(11 + i * 2, maxX / 2 - 11,"%s", *(mainMenu + i));
            
            attroff(A_BOLD);
			attroff(A_DIM);
            
            if (i == selected) 
            {
                attroff(A_STANDOUT);
            }
        }

        HowToUse(FUNCTION_MENU);
        
		refresh();
		
        int ch = getch();

        switch (ch) 
        {
            case '\n':

                flag = selected;
				
				break;
				
            case KEY_UP:
                if (selected > 0) 
                {
                    selected--;
                }
                
                break;
            case KEY_DOWN:
                if (selected < 2) 
                {
                    selected++;
                }
                
                refresh();
                break;
        }
        
        if (flag == 0 || flag == 1 || flag == 2)
		{
			break;
		}
    }
    
    return flag;
}

bool PlayAgainMenu(WINDOW *playAgainMenuWin)
{
	curs_set(0); 
	
	int maxX, maxY;
	
	int selected = 0;
	
	PrintConnect4();

    HowToUse(FUNCTION_MENU);
	
	getmaxyx(stdscr, maxY, maxX);
	
	playAgainMenuWin = newwin(5, 15, 10, maxX / 2 - 13);
	
	box(playAgainMenuWin, 0, 0);
	
	refresh();
	
	wrefresh(playAgainMenuWin); 
	
	int flag = 3;
	
	while (true) 
    {
        getmaxyx(stdscr, maxY, maxX);
        
        // Print the menu options, with the selected option highlighted using standout
        for (int i = 0; i < 2; i++) 
        {
            if (i == selected) 
            {
                attron(A_STANDOUT);
            }
			
			attron(A_BOLD);
			attron(A_DIM);
			
			mvprintw(11 + i * 2, maxX / 2 - 11,"%s", *(playAgainMenu + i));
            
            attroff(A_BOLD);
			attroff(A_DIM);
            
            if (i == selected) 
            {
                attroff(A_STANDOUT);
            }
        }

        HowToUse(FUNCTION_MENU);

		refresh();
		
        int ch = getch();

        switch (ch) 
        {
            case '\n':
               
                
                flag = selected;
				
				break;
				
            case KEY_UP:
                if (selected > 0) 
                {
                    selected--;
                }
                
                break;
            case KEY_DOWN:
                if (selected < 1) 
                {
                    selected++;
                }
                
                refresh();
                break;
        }
        
        if (flag == 0)
		{
			return true; 
		}
		else if (flag == 1)
		{
			return false; 
		}
    }
}

bool NameMenu(WINDOW *nameMenuWin)
{
	curs_set(0); 
	
	int maxX, maxY;
	
	int selected = 0;
	
	PrintConnect4();

    HowToUse(FUNCTION_MENU);
	
	getmaxyx(stdscr, maxY, maxX);
	
	nameMenuWin = newwin(5, 15, 10, maxX / 2 - 13);
	
	box(nameMenuWin, 0, 0);
	
	refresh();
	
	wrefresh(nameMenuWin); 
	
	int flag = 3;
	
	while (true) 
    {
        getmaxyx(stdscr, maxY, maxX);
        
        // Print the menu options, with the selected option highlighted using standout
        for (int i = 0; i < 2; i++) 
        {
            if (i == selected) 
            {
                attron(A_STANDOUT);
            }
			
			attron(A_BOLD);
			attron(A_DIM);
			
			mvprintw(11 + i * 2, maxX / 2 - 11,"%s", *(nameMenu + i));
            
            attroff(A_BOLD);
			attroff(A_DIM);
            
            if (i == selected) 
            {
                attroff(A_STANDOUT);
            }
        }

        HowToUse(FUNCTION_MENU);

		refresh();
		
        int ch = getch();

        switch (ch) 
        {
            case '\n':
               
                
                flag = selected;
				
				break;
				
            case KEY_UP:
                if (selected > 0) 
                {
                    selected--;
                }
                
                break;
            case KEY_DOWN:
                if (selected < 1) 
                {
                    selected++;
                }
                
                refresh();
                break;
        }
        
        if (flag == 0)
		{
            return true;

		}
		else if (flag == 1)
		{
			return false; 
		}
    }
}

void HowToUse(enum functions function)
{
    switch (function)
    {
        case FUNCTION_MENU:
            
            //how to use the program 
            mvprintw(20, 1, "HOW TO USE");
            mvprintw(21, 1, "==========");

            attron(A_STANDOUT);

            mvprintw(22, 1, "UP ARROW");
            mvprintw(23, 1, "DOWN ARROW");
            mvprintw(24, 1, "ENTER");  

            attroff(A_STANDOUT);

            mvprintw(22, 10, "> switch options");
            mvprintw(23, 12, "> switch options");
            mvprintw(24, 7, "> pick the option");

            attron(A_BOLD | A_DIM);

            break;
        case FUNCTION_NAME_INPUT:

            //how to use the program 
            mvprintw(20, 1, "HOW TO USE");
            mvprintw(21, 1, "==========");

            attron(A_STANDOUT);

            mvprintw(22, 1, "ENTER");  
            mvprintw(23, 1, "BACKSPACE");

            attroff(A_STANDOUT);

            mvprintw(22, 7, "> confirm name");
            mvprintw(23, 11, "> remove one letter");

            attron(A_BOLD | A_DIM);

            break;

        case FUNCTION_GAME_BOARD:

            //how to use the program 
            mvprintw(20, 1, "HOW TO USE");
            mvprintw(21, 1, "==========");

            attron(A_STANDOUT);

            mvprintw(22, 1, "LEFT ARROW");
            mvprintw(23, 1, "RIGHT ARROW");
            mvprintw(24, 1, "ENTER");  

            attroff(A_STANDOUT);

            mvprintw(22, 12, "> switch col");
            mvprintw(23, 13, "> switch col");
            mvprintw(24, 7, "> drop coin");

            attron(A_BOLD | A_DIM);

            break;
         

    }
}

void PrintConnect4(void)
{
	int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
	
	mvprintw(0, maxX / 12, "       _  _  _             _  _  _  _         _           _        _           _        _  _  _  _  _           _  _  _           _  _  _  _  _                                _       ");
	mvprintw(1, maxX / 12, "    _ (_)(_)(_) _        _(_)(_)(_)(_)_      (_) _       (_)      (_) _       (_)      (_)(_)(_)(_)(_)       _ (_)(_)(_) _       (_)(_)(_)(_)(_)                            _ (_)      ");
	mvprintw(2, maxX / 12, "   (_)         (_)      (_)          (_)     (_)(_)_     (_)      (_)(_)_     (_)      (_)                  (_)         (_)            (_)                               _ (_)(_)      ");
	mvprintw(3, maxX / 12, "   (_)                  (_)          (_)     (_)  (_)_   (_)      (_)  (_)_   (_)      (_) _  _             (_)                        (_)                            _ (_)   (_)      ");
	mvprintw(4, maxX / 12, "   (_)                  (_)          (_)     (_)    (_)_ (_)      (_)    (_)_ (_)      (_)(_)(_)            (_)                        (_)                           (_) _  _ (_) _    ");
	mvprintw(5, maxX / 12, "   (_)          _       (_)          (_)     (_)      (_)(_)      (_)      (_)(_)      (_)                  (_)          _             (_)                           (_)(_)(_)(_)(_)   ");
	mvprintw(6, maxX / 12, "   (_) _  _  _ (_)      (_)_  _  _  _(_)     (_)         (_)      (_)         (_)      (_) _  _  _  _       (_) _  _  _ (_)            (_)                                    (_)      ");
	mvprintw(7, maxX / 12, "      (_)(_)(_)           (_)(_)(_)(_)       (_)         (_)      (_)         (_)      (_)(_)(_)(_)(_)         (_)(_)(_)               (_)                                    (_)      "); 
	
	for (int i = 0; i < maxX; i++)
	{
		mvprintw(9, 0 + i, "=");
	}

}
