all: obj/state.o obj/PQ.o
	g++ -Wall -Wextra -O0 -o bin/PathFinder src/main.cpp obj/PQ.o obj/state.o

obj/state.o:
	g++ -Wall -Wextra -O0 -c -o obj/state.o include/state.cpp

obj/PQ.o: 
	g++ -Wall -Wextra -O0 -c -o obj/PQ.o include/priorityq.cpp

clean:
	rm -rf obj/*
	rm -rf bin/*