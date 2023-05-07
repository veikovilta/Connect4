#ifndef MENU_H
#define MENU_H

//#define ARRAY_SIZE(a) ((unsigned)sizeof(a) / (unsigned)sizeof(a[0]))

enum functions{
    FUNCTION_MENU,
    FUNCTION_NAME_INPUT, 
    FUNCTION_GAME_BOARD, 
};

void PrintConnect4(void); 
int MainMenu(WINDOW *mainMenuWin);
bool PlayAgainMenu(WINDOW *playAgainMenuWin); 
bool NameMenu(WINDOW *nameMenuWin); 
void HowToUse(enum functions function); 

#endif
