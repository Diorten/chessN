default: build

build:
	g++ -Wall -o Szachy src/main.cpp src/Board.cpp src/Engine.cpp