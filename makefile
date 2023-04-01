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

install: all
	install $(BIN_FILES) $(INSTALL_PATH)

clean:
	rm -f $(BIN_FILES) $(OBJ_FILES) vargsai.txt saunuoliai.txt

cleanf:
	rm -f $(BIN_FILES) $(OBJ_FILES)

cleanres:
	rm vargsai.txt saunuoliai.txt

txt:
	rm *.txt