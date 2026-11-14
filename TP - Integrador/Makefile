CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
SRC = $(wildcard src/*.cpp)
HEADERS = $(wildcard include/*.h)
OUT = bicis

.PHONY: all clean run

all: $(OUT)

$(OUT): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)
