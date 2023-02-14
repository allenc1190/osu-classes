CC = g++ -std=c++11
exe_file = portal

$(exe_file): assignment2.cpp assignment2_prog.o pizza.o menu.o restaurant.o
	$(CC) assignment2.cpp assignment2_prog.o pizza.o menu.o restaurant.o -o $(exe_file)

assignment2_prog.o: assignment2_prog.cpp assignment2.hpp
	$(CC) -c assignment2_prog.cpp -o assignment2_prog.o

pizza.o: pizza.cpp pizza.hpp
	$(CC) -c pizza.cpp -o pizza.o

menu.o: menu.cpp menu.hpp
	$(CC) -c menu.cpp -o menu.o

restaurant.o: restaurant.cpp restaurant.hpp
	$(CC) -c restaurant.cpp -o restaurant.o

clean:
	rm -f *.out *.o $(exe_file)