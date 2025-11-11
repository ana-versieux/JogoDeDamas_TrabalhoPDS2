
CXX = g++

HEADER_DIR = ../contratos

CXXFLAGS = -Wall -std=c++14 -I. -I$(HEADER_DIR)

TARGET = damas

SRC = 	peca.cpp\
		tabuleiro.cpp\
		jogo.cpp\
		main.cpp

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)
	rm -f $(OBJ)

run: all
	@cls
	./$(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
