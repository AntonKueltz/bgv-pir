CFLAGS = -g -Wfatal-errors -Wshadow -Wall -std=c++11
OBJS = Main.o PIRServer.o PIRClient.o Util.o FoldingTree.o
IFLAGS = -I/usr/local/include -I$(HELIB)/src
LFLAGS = $(HELIB)/src/fhe.a -L/usr/local/lib -lntl -lgmp -lm
CC = g++

all: App

App: $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) -o PIR $(OBJS) $(LFLAGS)

Main.o: Main.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c Main.cpp

PIRServer.o: PIRServer.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c PIRServer.cpp

PIRClient.o: PIRClient.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c PIRClient.cpp

Util.o: Util.cpp
	$(CC) $(CFLAGS) -c Util.cpp

FoldingTree.o: FoldingTree.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c FoldingTree.cpp

clean:
	rm *o PIR
