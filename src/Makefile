CFLAGS = -std=c++11
OBJS = Main.o PIRServer.o PIRClient.o Util.o FoldingTree.o
IFLAGS = -I$(HELIB)/src
UNAME = $(shell uname)

# COMPILE FOR LINUX (THIS SHIT IS BROKEN FOR THE MOMENT)
ifeq ($(UNAME), Linux)
LFLAGS = $(HELIB)/src/fhe.a -lntl -lgmp -L/usr/lib
CC = g++
endif

# COMPILE FOR OSX (WORKS LIKE A CHARM)
ifeq ($(UNAME), Darwin)
LFLAGS = -L/usr/lib -lntl -lgmp $(HELIB)/src/fhe.a
CC = clang++
endif

all: App

ifeq ($(UNAME), Darwin)
App: $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(OBJS) -o PIR
endif

ifeq ($(UNAME), Linux)
App: $(OBJS)
	$(CC) $(OBJS) $(IFLAGS) $(LFLAGS) $(CFLAGS) -o PIR
endif

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

