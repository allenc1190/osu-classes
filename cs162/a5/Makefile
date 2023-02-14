CC = g++ -std=c++11
exe_file = main

$(exe_file): main.o linked_list_node.o linked_list.o
	$(CC) main.o linked_list_node.o linked_list.o -o $(exe_file)

linked_list_node.o: linked_list_node.cpp linked_list_node.hpp
	$(CC) -c linked_list_node.cpp -o linked_list_node.o

linked_list.o: linked_list.cpp linked_list.hpp
	$(CC) -c linked_list.cpp -o linked_list.o

clean:
	rm -f *.out *.o $(exe_file)