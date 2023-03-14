.PHONY: all test clean gcov_report

all:
	mkdir build
	g++ src/*.cpp `pkg-config --libs --cflags libpqxx` -o build/chess
	./build/chess localhost chess postgres 1
