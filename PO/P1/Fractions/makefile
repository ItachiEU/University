PROG = finito
CC = gcc
CFLAGS = -Wall -g
OBJS = main.o ulamek.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(SFMLFLAGS)

main.o : main.c
	$(CC) -c $(CPPFLAGS) main.c
ulamek.o: ulamek.c
	$(CC) -c $(CPPFLAGS) ulamek.c

clean :
	rm -f core $(PROG) $(OBJS)