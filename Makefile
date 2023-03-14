.PHONY: all chess.so test clean gcov_report

CXX = g++
CC = gcc
CXX_FLAGS = -Wall -Werror -Wextra -std=c++17
PQXX_FLAGS = $(pkg-config --libs --cflags libpqxx)
SOURCES_ALL = $(find src/ -maxdepth 1 -name "*.cpp" 2> /dev/null)
HEADER_PIECE = src/Piece.h
HEADER_CHESS = src/Chess.h

all: test

test: chess.so
	@mkdir -p build
	$(CXX) -Llib/ $(CXXFLAGS) $(PQXX_FLAGS) src/Tests/test.cpp -o build/chess -lchess
	export LD_LIBRARY_PATH=lib/:$LD_LIBRARY_PATH
	./build/chess


chess.so: clean $(HEADER_PIECE) $(HEADER_CHESS)
	@echo "Start building shared library..."
	@mkdir -p lib
	$(CXX) $(CXXFLAGS) -c -fPIC -o lib/piece.o src/Piece.cpp
	$(CXX) $(CXXFLAGS) -c -fPIC -o lib/chess.o src/Chess.cpp
	gcc -shared -o lib/chess.so lib/*.o
	@echo "Shared library built"
	@rm lib/*.o
	@echo "Object files deleted"

clean:
	@echo "Start cleaning the project..."
	@-rm -rf build lib
	@echo "Project cleared"
