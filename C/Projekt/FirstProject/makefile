PROG = sfml-first
CC = g++
CPPFLAGS = -O2 -std=c++11 -Wall
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
OBJS = simple-games.o game.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(SFMLFLAGS)

simple-games.o :
	$(CC) -c $(CPPFLAGS) simple-games.cpp 
game.o :
	$(CC) -c $(CPPFLAGS) game.cpp
clean :
	rm -f core $(PROG) $(OBJS)