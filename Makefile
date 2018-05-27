CPP_Flags=-std=c++11

all: main.cpp LinkedList.h
	g++ $(CPP_Flags) main.cpp LinkedList.h -o output.o
	./output.o

clean:
	rm -rf output.o