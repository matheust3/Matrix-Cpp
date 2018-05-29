LIBS = -g -std=c++14
INCLUDE =   
DEBUG = -g

all: main

main:  main.cpp
	g++  main.cpp -o App.run $(LIBS) $(INCLUDE) $(DEBUG)