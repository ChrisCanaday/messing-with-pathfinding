all: clean obj/state.o obj/DS.o obj/pqs.o
	g++ -Wall -Wextra -O0 -o bin/PathFinder src/main.cpp obj/state.o obj/DS.o obj/pqs.o

obj/state.o:
	g++ -Wall -Wextra -O0 -c -o obj/state.o include/state.cpp

obj/DS.o:
	g++ -Wall -Wextra -O0 -c -o obj/DS.o include/dstar.cpp

obj/pqs.o:
	g++ -Wall -Wextra -O0 -c -o obj/pqs.o include/pqs.cpp

obj/FDS.o:
	g++ -Wall -Wextra -O0 -c -o obj/FDS.o include/fielddstar.cpp

clean:
	rm -rf obj/*
	rm -rf bin/*