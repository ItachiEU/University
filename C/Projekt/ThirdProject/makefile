PROG = sfml-third
CC = g++
CPPFLAGS = -O2 -std=c++11 -Wall
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
OBJS = main.o game.o player.o bullet.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(SFMLFLAGS)

main.o :
	$(CC) -c $(CPPFLAGS) main.cpp
game.o:
	$(CC) -c $(CPPFLAGS) game.cpp
player.o:
	$(CC) -c $(CPPFLAGS) player.cpp
bullet.o:
	$(CC) -c $(CPPFLAGS) bullet.cpp
clean :
	rm -f core $(PROG) $(OBJS)