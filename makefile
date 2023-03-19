main: addFunctions.o
	g++ -std=c++20 -march=native -O3 main.cpp -o main addFunctions.o
list: addFunctions.O
	g++ -std=c++20 -march=native -O3 list.cpp -o list addFunctions.o
deque: addFunctions.O
	g++ -std=c++20 -march=native -O3 deque.cpp -o list addFunctions.o
addFunctions:
	g++ -c addFunctions.cpp
clean:
	rm *.o main vargsai.txt saunuoliai.txt
cleanres:
	rm vargsai.txt saunuoliai.txt
cleanall:
	rm *.0 main list deque
txt:
	rm *.txt