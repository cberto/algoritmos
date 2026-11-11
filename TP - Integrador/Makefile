CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -Iestructuras
SRC = src/main.cpp src/sistema.cpp
HEADERS = include/Estacion.h include/Sistema.h estructuras/TablaHash.h estructuras/Grafo.h estructuras/Cola.h estructuras/ListaEnlazada.h estructuras/FuncionHash.h
OUT = bicis
TEST_OUT = tests/test_estaciones.exe

.PHONY: all clean run test

all: $(OUT)

$(OUT): Makefile $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

test: $(TEST_OUT)
	./$(TEST_OUT)

$(TEST_OUT): Makefile tests/test_estaciones.cpp src/sistema.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TEST_OUT) tests/test_estaciones.cpp src/sistema.cpp

run: $(OUT)
	./$(OUT)

clean:
	powershell -NoProfile -Command "if (Test-Path -LiteralPath '$(OUT).exe') { Remove-Item -LiteralPath '$(OUT).exe' }; if (Test-Path -LiteralPath '$(TEST_OUT)') { Remove-Item -LiteralPath '$(TEST_OUT)' }"
