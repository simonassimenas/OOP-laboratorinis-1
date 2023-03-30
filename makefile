main: addFunctions.o
	g++ -std=c++20 -march=native -O3 main.cpp -o main addFunctions.o
addFunctions:
	g++ -c addFunctions.cpp
split: addFunctions.o
	g++ -std=c++20 -march=native -O3 split.cpp -o split addFunctions.o
single: addFunctions.o
	g++ -std=c++20 -march=native -O3 single.cpp -o single addFunctions.o
partition: addFunctions.o
	g++ -std=c++20 -march=native -O3 partition.cpp -o partition addFunctions.o
clean:
	rm *.o main partition single split vargsai.txt saunuoliai.txt
cleanres:
	rm vargsai.txt saunuoliai.txt
txt:
	rm *.txt