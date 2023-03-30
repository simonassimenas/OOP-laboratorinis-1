CXX = g++
CXXFLAGS = -std=c++20 -march=native -O3
INSTALL_PATH = "./"

SRC_FILES = main.cpp addFunctions.cpp split.cpp single.cpp partition.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)
BIN_FILES = main split single partition

.PHONY: all clean install

all: $(BIN_FILES)

$(BIN_FILES): %: %.o addFunctions.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

cleanf:
	rm -f $(BIN_FILES) $(OBJ_FILES)

install: all
	install $(BIN_FILES) $(INSTALL_PATH)

########################################

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