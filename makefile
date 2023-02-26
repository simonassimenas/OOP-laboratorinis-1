main: addFunctions.o
	g++ -O3 main.cpp -o main addFunctions.o
addFunctions:
	g++ -c addFunctions.cpp
clean:
	rm *.o main