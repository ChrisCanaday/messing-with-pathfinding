all: clean obj/state.o obj/dss.o obj/pqs.o
	g++ -Wall -Wextra -O0 -o bin/PathFinder src/main.cpp obj/state.o obj/dss.o obj/pqs.o

obj/state.o:
	g++ -Wall -Wextra -O0 -c -o obj/state.o include/state.cpp

obj/PQ.o: 
	g++ -Wall -Wextra -O0 -c -o obj/PQ.o include/priorityq.cpp

obj/DS.o:
	g++ -Wall -Wextra -O0 -c -o obj/DS.o include/dstar.cpp

obj/pqs.o:
	g++ -Wall -Wextra -O0 -c -o obj/pqs.o include/pqs.cpp

obj/dss.o:
	g++ -Wall -Wextra -O0 -c -o obj/dss.o include/dstars.cpp

clean:
	rm -rf obj/*
	rm -rf bin/*