CC = g++ -std=c++11
exe_file = zoo

$(exe_file): main.o zoo.o animal.o monkey.o sea_otter.o meerkat.o
	$(CC) main.o zoo.o animal.o monkey.o sea_otter.o meerkat.o -o $(exe_file)

zoo.o: zoo.cpp zoo.hpp
	$(CC) -c zoo.cpp -o zoo.o

animal.o: animal.cpp animal.hpp
	$(CC) -c animal.cpp -o animal.o

monkey.o: monkey.cpp monkey.hpp
	$(CC) -c monkey.cpp -o monkey.o

sea_otter.o: sea_otter.cpp sea_otter.hpp
	$(CC) -c sea_otter.cpp -o sea_otter.o

meerkat.o: meerkat.cpp meerkat.hpp
	$(CC) -c meerkat.cpp -o meerkat.o

clean:
	rm -f *.out *.o $(exe_file)