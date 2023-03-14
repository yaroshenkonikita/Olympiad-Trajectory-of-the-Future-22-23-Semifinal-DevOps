.PHONY: all chess.so test clean gcov_report

CXX = g++
CXX_FLAGS = -Wall -Werror -Wextra -std=c++17
PQXX_FLAGS = $(pkg-config --libs --cflags libpqxx)
PWD = $(shell pwd)
SOURCES_ALL = $(find src/ -maxdepth 1 -name "*.cpp" 2> /dev/null)
HEADER_PIECE = src/Piece.h
HEADER_CHESS = src/Chess.h

all: test

test: chess.so
	@mkdir -p build
	$(CXX) -c src/Tests/test.cpp -o lib/test.o
	$(CXX) $(CXX_FLAGS) $(PQXX_FLAGS) lib/test.o -o build/chess -L./lib/ -lchess
	export LD_LIBRARY_PATH=$(PWD)/lib/:$LD_LIBRARY_PATH
	./build/chess

chess.so: clean $(HEADER_PIECE) $(HEADER_CHESS)
	@echo "Start building shared library..."
	@mkdir -p lib
	$(CXX) $(CXXFLAGS) -fPIC -c -o lib/piece.o src/Piece.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c -o lib/chess.o src/Chess.cpp
	$(CXX) lib/*.o -shared -o lib/chess.so
	sudo cp lib/chess.so /usr/lib
	@echo "Shared library built"
	@rm lib/*.o
	@echo "Object files deleted"

clean:
	@echo "Start cleaning the project..."
	@-rm -rf build lib
	@echo "Project cleared"
