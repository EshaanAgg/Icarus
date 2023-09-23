compile:
	g++ Icarus/*/*.cpp Icarus/*.cpp main.cpp -o main

run: 
	make compile && ./main