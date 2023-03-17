.PHONY: all chess.so test clean gcov_report dvi dist

CXX = g++
CXX_FLAGS = -Wall -Werror -Wextra -std=c++17
GCOV_FLAGS = --coverage
PQXX_FLAGS = $(shell pkg-config --libs --cflags libpqxx)
ALL_SOURCE = $(shell find src/ \( -name "*.cpp" -or -name "*.h" \))
HEADER_PIECE = src/Piece.h
HEADER_CHESS = src/Chess.h
ifeq ($(DEBUG), 1)
	DEBUGFLAG = -DOUTPUT
endif

all: gcov_report dvi dist

test: chess.so
	@echo "Start build test cases with shared library..."
	@mkdir -p build
	$(CXX) $(CXX_FLAGS) $(GCOV_FLAGS) -c -o build/solution.o src/Solution.cpp
	$(CXX) -Llib/ $(CXX_FLAGS) $(GCOV_FLAGS) $(DEBUGFLAG) src/Tests/googletests.cpp build/solution.o -o build/findCheck -lchess $(PQXX_FLAGS) -lgtest -lgtest_main -lpthread -lm
	@echo "Test cases is built"
	@echo "Start test cases"
	./build/findCheck
	@echo "Tests is Complete!"

chess.so: $(HEADER_PIECE) $(HEADER_CHESS)
	@echo "Start building shared library..."
	@mkdir -p lib
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) -fPIC -c -o lib/piece.o src/Piece.cpp
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) -fPIC -c -o lib/chess.o src/Chess.cpp
	$(CXX) lib/*.o $(GCOV_FLAGS) -shared -o lib/libchess.so
	@cp lib/libchess.so /usr/lib
	@echo "Shared library built and copy to library path"
	@rm lib/*.o
	@echo "Object files deleted"

dvi:
	@mkdir -p documentation
	doxygen src/Doxyfile

dist:
	@mkdir -p dist
	tar -cvzf dist/source.tar.gz src

gcov_report: test
	@mkdir -p report
	@mkdir -p report/include
	@mv build/*.gc* report/include
	@mv lib/*.gc* report/include
	@-rm report/include/*googletests.gc*
	lcov -t build/findCheck -o report/include/findCheck.info --no-external -c -d .
	genhtml -o report/report_html report/include/findCheck.info

style:
	clang-format -style=google -i $(ALL_SOURCE)

clean:
	@echo "Start cleaning the project..."
	@-rm -rf build lib documentation dist report /usr/lib/libchess.so
	@echo "Project cleared"
