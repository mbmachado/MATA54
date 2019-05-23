all:
	g++ main.cpp file.cpp multilist.cpp;
clear:
	rm file.txt multilist.txt
	touch file.txt multilist.txt
