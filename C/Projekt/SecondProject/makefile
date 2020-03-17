PROG = sfml-second
CC = g++
CPPFLAGS = -O2 -std=c++11 -Wall
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
OBJS = main.o game.o player.o ball.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(SFMLFLAGS)

main.o :
	$(CC) -c $(CPPFLAGS) main.cpp
game.o:
	$(CC) -c $(CPPFLAGS) game.cpp
player.o:
	$(CC) -c $(CPPFLAGS) player.cpp
ball.o:
	$(CC) -c $(CPPFLAGS) ball.cpp
clean :
	rm -f core $(PROG) $(OBJS)