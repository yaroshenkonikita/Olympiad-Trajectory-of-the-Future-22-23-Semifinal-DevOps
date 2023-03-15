.PHONY: all chess.so test clean gcov_report

CXX = g++
CXX_FLAGS = -Wall -Werror -Wextra -std=c++17
PQXX_FLAGS = $(shell pkg-config --libs --cflags libpqxx)
HEADER_PIECE = src/Piece.h
HEADER_CHESS = src/Chess.h

all: test

test: chess.so
	@echo "Start build test cases with shared library..."
	@mkdir -p build
	$(CXX) -c src/Tests/test.cpp -o lib/test.o
	$(CXX) $(CXX_FLAGS) lib/test.o src/*.h -o build/findCheck -lchess $(PQXX_FLAGS)
	@echo "Test cases is built"
	@rm lib/test.o
	@echo "Start test cases"
	./build/findCheck
	@echo "Tests is Complete!"

chess.so: clean $(HEADER_PIECE) $(HEADER_CHESS)
	@echo "Start building shared library..."
	@mkdir -p lib
	$(CXX) $(CXXFLAGS) -fPIC -c -o lib/piece.o src/Piece.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c -o lib/chess.o src/Chess.cpp
	$(CXX) lib/*.o -shared -o lib/libchess.so
	@cp lib/libchess.so /usr/lib
	@echo "Shared library built and copy to library path"
	@rm lib/*.o
	@echo "Object files deleted"

clean:
	@echo "Start cleaning the project..."
	@-rm -rf build lib /usr/lib/libchess.so
	@echo "Project cleared"
