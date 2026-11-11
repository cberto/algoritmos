CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TEST = tests/test_estructuras.cpp

ifeq ($(OS),Windows_NT)
OUT = tests/test_estructuras.exe
CLEAN_COMMAND = powershell -NoProfile -Command "if (Test-Path -LiteralPath '$(OUT)') { Remove-Item -LiteralPath '$(OUT)' }"
else
OUT = tests/test_estructuras
CLEAN_COMMAND = rm -f $(OUT)
endif

.PHONY: all test clean

all: test

test: $(OUT)
	./$(OUT)

$(OUT): $(TEST) ArbolBinarioBusqueda.h Cola.h FuncionHash.h Grafo.h ListaEnlazada.h MonticuloMinimo.h TablaHash.h
	$(CXX) $(CXXFLAGS) -I. -o $(OUT) $(TEST)

clean:
	$(CLEAN_COMMAND)
