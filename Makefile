all: main

main: main 
	g++ project/main.cpp -o main --std=c++11 -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

clean: 
	rm *o main
