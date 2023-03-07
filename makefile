main: addFunctions.o
	g++ -std=c++20 -march=native -O3 main.cpp -o main addFunctions.o
addFunctions:
	g++ -c addFunctions.cpp
clean:
	rm *.o main vargsai.txt saunuoliai.txt