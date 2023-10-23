compile:
	g++ Icarus/*.cpp Icarus/Table/*.cpp Icarus/Table/ExpParser/*.cpp Icarus/Parser/*.cpp main.cpp -o main

run: 
	make compile && ./main