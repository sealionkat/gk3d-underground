all: main

main: main 
	g++ project/main.cpp -o underground --std=c++11 -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

clean: 
	rm underground
