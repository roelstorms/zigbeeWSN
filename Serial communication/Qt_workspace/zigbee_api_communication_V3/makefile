# this is a example of Makefile

all:	inputhandler.o connection.o userinput.o APIFrames.o
	g++ main.cpp -o main.out ./obj/inputhandler.o ./obj/connection.o ./obj/userinput.o ./obj/APIFrames.o -lboost_thread -std=c++11
test:	APIFrames.o connection.o
	g++ ./tests/APIFramesTest.cpp -o ./tests/APIFramesTest.out ./obj/APIFrames.o ./obj/connection.o ./obj/userinput.o ./obj/inputhandler.o -lboost_thread -std=c++11
inputhandler.o:
	g++ -c inputhandler.cpp -o ./obj/inputhandler.o -std=c++11
connection.o: inputhandler.o userinput.o
	g++ -c connection.cpp -o ./obj/connection.o -lboost_thread -std=c++11
userinput.o:
	g++ -c userinput.cpp -o ./obj/userinput.o  -std=c++11
APIFrames.o:
	g++ -c APIFrames.cpp -o ./obj/APIFrames.o -std=c++11
clean:
	rm ./obj/inputhandler.o ./obj/connection.o ./obj/userinput.o ./obj/APIFrames.o
