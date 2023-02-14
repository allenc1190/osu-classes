CC = g++ -std=c++11
exe_file = hunt

$(exe_file): main.o room.o event.o wumpus.o bats.o pit.o gold.o none.o player.o
	$(CC) main.o room.o event.o wumpus.o bats.o pit.o gold.o none.o player.o -o $(exe_file)

room.o: room.cpp room.hpp
	$(CC) -c room.cpp -o room.o

event.o: event.cpp event.hpp
	$(CC) -c event.cpp -o event.o

wumpus.o: wumpus.cpp wumpus.hpp
	$(CC) -c wumpus.cpp -o wumpus.o

bats.o: bats.cpp bats.hpp
	$(CC) -c bats.cpp -o bats.o

pit.o: pit.cpp pit.hpp
	$(CC) -c pit.cpp -o pit.o

gold.o: gold.cpp gold.hpp
	$(CC) -c gold.cpp -o gold.o

none.o: none.cpp none.hpp
	$(CC) -c none.cpp -o none.o

player.o: player.cpp player.hpp
	$(CC) -c player.cpp -o player.o

clean:
	rm -f *.out *.o $(exe_file)