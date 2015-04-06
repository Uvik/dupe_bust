all:
	g++ -Wall -Wextra -DDEBUG tinyxml2/tinyxml2.cpp find_dupes.cpp -o dupe_buster

clean:
	rm -f *.o dupe_buster
