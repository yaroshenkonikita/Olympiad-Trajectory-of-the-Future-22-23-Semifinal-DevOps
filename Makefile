.PHONY: all chess.so test clean gcov_report dvi

CXX = g++
CXX_FLAGS = -Wall -Werror -Wextra -std=c++17
PQXX_FLAGS = $(shell pkg-config --libs --cflags libpqxx)
ALL_SOURCE = $(shell find src/ \( -name "*.cpp" -or -name "*.h" \))
HEADER_PIECE = src/Piece.h
HEADER_CHESS = src/Chess.h

all: test dvi

test: chess.so
	@echo "Start build test cases with shared library..."
	@mkdir -p build
	$(CXX) -Llib/ $(CXX_FLAGS) src/Tests/googletests.cpp -o build/findCheck -lchess $(PQXX_FLAGS) -lgtest -lgtest_main -lpthread -lm
	@echo "Test cases is built"
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

dvi:
	mkdir -p documentation
	doxygen src/Doxyfile

style:
	clang-format -style=google -i $(ALL_SOURCE)

clean:
	@echo "Start cleaning the project..."
	@-rm -rf build lib documentation /usr/lib/libchess.so
	@echo "Project cleared"
