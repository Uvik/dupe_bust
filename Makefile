all:
	g++ -Wall -DDEBUG tinyxml2.cpp find_dupes.cpp -o find_dupes

clean:
	rm -f *.o find_dupes
