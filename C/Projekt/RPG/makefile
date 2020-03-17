PROG = sfml-rpg
CC = g++
CPPFLAGS = -O2 -std=c++11 -Wall
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
OBJS = main.o game.o state.o GameState.o entity.o MainMenuState.o button.o player.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(SFMLFLAGS)

main.o :
	$(CC) -c $(CPPFLAGS) main.cpp
game.o:
	$(CC) -c $(CPPFLAGS) game.cpp
state.o:
	$(CC) -c $(CPPFLAGS) state.cpp
GameState.o:
	$(CC) -c $(CPPFLAGS) GameState.cpp
entity.o:
	$(CC) -c $(CPPFLAGS) entity.cpp
MainMenuState.o:
	$(CC) -c $(CPPFLAGS) MainMenuState.cpp
button.o:
	$(CC) -c $(CPPFLAGS) button.cpp
player.o:
	$(CC) -c $(CPPFLAGS) player.cpp
clean :
	rm -f core $(PROG) $(OBJS)