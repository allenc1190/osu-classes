CC=g++
EXE_FILE=catelog

all: $(EXE_FILE)

$(EXE_FILE): assignment1.o assignment1.hpp assignment1_prog.cpp 
	$(CC) assignment1.o assignment1_prog.cpp -o $(EXE_FILE)

assignment1.o: assignment1.hpp assignment1.cpp
	$(CC) -c assignment1.cpp

clean:
	rm -f *.o $(EXE_FILE)