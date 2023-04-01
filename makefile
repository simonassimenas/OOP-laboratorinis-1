CXX = g++
CXXFLAGS = -std=c++20 -march=native -O3
INSTALL_PATH = "./"

SRC_FILES = main.cpp addFunctions.cpp vector.cpp deque.cpp list.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)
BIN_FILES = main vector deque list

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
vector: addFunctions.o
	g++ -std=c++20 -march=native -O3 vector.cpp -o vector addFunctions.o
deque: addFunctions.o
	g++ -std=c++20 -march=native -O3 deque.cpp -o deque addFunctions.o
list: addFunctions.o
	g++ -std=c++20 -march=native -O3 list.cpp -o list addFunctions.o
cleanres:
	rm vargsai.txt saunuoliai.txt
txt:
	rm *.txt