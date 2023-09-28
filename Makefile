compile:
	# The ordering of the folders in done so as to ensure that the classes required by another classes are compiled first
	# (Topological sorting of the dependancy tree for the graph theory folks!)
	g++ Icarus/Table/*.cpp Icarus/Parser/*.cpp Icarus/*.cpp main.cpp -o main

run: 
	make compile && ./main