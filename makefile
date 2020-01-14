CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system
CFLAGS += -pthread
LDFLAGS += -pthread


all:StompBookClubClient
	g++ -o bin/StompBookClubClient bin/Book.o bin/connectionHandler.o bin/keyboardHandler.o bin/serverHandler.o   bin/UserData.o bin/ClientRunner.o $(LDFLAGS)

StompBookClubClient: bin/Book.o bin/connectionHandler.o bin/keyboardHandler.o bin/serverHandler.o  bin/UserData.o bin/ClientRunner.o

bin/Book.o: src/Book.cpp include/Book.h
	g++ $(CFLAGS) -o bin/Book.o src/Book.cpp

bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp

bin/keyboardHandler.o:  src/keyboardHandler.cpp include/keyboardHandler.h
	g++ $(CFLAGS) -o bin/keyboardHandler.o src/keyboardHandler.cpp

bin/serverHandler.o: src/serverHandler.cpp include/serverHandler.h
	g++ $(CFLAGS) -o bin/serverHandler.o src/serverHandler.cpp

bin/UserData.o:  src/UserData.cpp include/UserData.h
	g++ $(CFLAGS) -o bin/UserData.o src/UserData.cpp

bin/ClientRunner.o:  src/ClientRunner.cpp include/ClientRunner.h
	g++ $(CFLAGS) -o bin/ClientRunner.o src/ClientRunner.cpp


.PHONY: clean
clean:
	rm -f bin/*
