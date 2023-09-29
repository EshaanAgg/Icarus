compile:
	g++ Icarus/*.cpp Icarus/Table/*.cpp Icarus/*/*/*.cpp Icarus/Parser/*.cpp main.cpp -o main

run: 
	make compile && ./main