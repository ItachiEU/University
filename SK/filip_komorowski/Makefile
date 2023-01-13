PROG = traceroute
CC = g++
CPPFLAGS = -O2 -std=c++17 -Wall -Wextra
OBJS = main.o receiver.o sender.o helpers.o packet.o handlers.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o:
	$(CC) -c $(CPPFLAGS) main.cpp

receiver.o:
	$(CC) -c $(CPPFLAGS) receiver.cpp

sender.o:
	$(CC) -c $(CPPFLAGS) sender.cpp

helpers.o:
	$(CC) -c $(CPPFLAGS) helpers.cpp

packet.o:
	$(CC) -c $(CPPFLAGS) packet.cpp

handlers.o:
	$(CC) -c $(CPPFLAGS) handlers.cpp

clean :
	rm -f $(PROG) $(OBJS)

distclean:
	rm -f traceroute $(PROG) $(OBJS)