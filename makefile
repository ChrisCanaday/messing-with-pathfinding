all: clean obj/state.o obj/PQ.o obj/DS.o
	g++ -Wall -Wextra -O0 -o bin/PathFinder src/main.cpp obj/PQ.o obj/state.o obj/DS.o

obj/state.o:
	g++ -Wall -Wextra -O0 -c -o obj/state.o include/state.cpp

obj/PQ.o: 
	g++ -Wall -Wextra -O0 -c -o obj/PQ.o include/priorityq.cpp

obj/DS.o:
	g++ -Wall -Wextra -O0 -c -o obj/DS.o include/dstar.cpp

clean:
	rm -rf obj/*
	rm -rf bin/*