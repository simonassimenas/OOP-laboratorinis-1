main: addFunctions.o
	g++ -std=c++20 -march=native -O3 main.cpp -o main addFunctions.o
list: addFunctions.o
	g++ -std=c++20 -march=native -O3 list.cpp -o list addFunctions.o
deque: addFunctions.o
	g++ -std=c++20 -march=native -O3 deque.cpp -o deque addFunctions.o
addFunctions:
	g++ -c addFunctions.cpp
clean:
	rm *.o main list deque vargsai.txt saunuoliai.txt
cleanres:
	rm vargsai.txt saunuoliai.txt
txt:
	rm *.txt