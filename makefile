main: addFunctions.o
	g++ -std=c++20 -O3 main.cpp -o main addFunctions.o
addFunctions:
	g++ -c addFunctions.cpp
clean:
	rm *.o main kursiokai.txt