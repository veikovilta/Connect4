# define the compiler
CC = gcc

CFLAGS = -g

# output file name
EXEC = connect4

all: game_engine.o highscore.o board.o menu.o main.o
	$(CC) -o $(EXEC) $(CFLAGS) game_engine.c highscore.c board.c menu.c main.c -lncurses
	
game_engine.o: game_engine.c game_engine.h
	$(CC) $(CFLAGS) -c game_engine.c
	 
highscore.o: highscore.c highscore.h
	$(CC) $(CFLAGS) -c highscore.c 
	
board.o: board.c board.h
	$(CC) $(CFLAGS) -c board.c
	
menu.o: menu.c menu.h
	$(CC) $(CFLAGS) -c menu.c
	
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

.PHONY: clean cleanobj

# cleans objects as a dependency and then the executable
clean: cleanobj
	rm $(EXEC)

# only cleans objects
cleanobj:
	rm *.o
