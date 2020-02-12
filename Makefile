#Makefile for VraXaPsa "candy-crush" like game.
#Made by : Grigorios Tsopouridis , 2019

CPP = g++

#OpenGL Libraries
OPENGL = -lglut -lGLU -lGL

all:
	$(CPP) -std=c++0x main.cpp -o VraXaPsa $(OPENGL)
clean:
	rm *.o
