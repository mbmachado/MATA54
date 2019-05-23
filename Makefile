all:
	g++ main.cpp file.cpp multilist.cpp;
	touch file.txt multilist.txt;
faker:
	pip install Faker
	python3.6 input-generator.py;
	./a.out < in
clear:
	rm file.txt multilist.txt rm in;
	touch file.txt multilist.txt;
