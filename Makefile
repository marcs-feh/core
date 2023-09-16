CXX      ?= g++
CXXFLAGS ?= -O1 -march=native -pipe -Wall -Wextra

CXXFLAGS := $(CXXFLAGS) -I. -fno-exceptions -fno-strict-aliasing -std=c++20

.PHONY: run clean

run: main.bin
	@./main.bin

main.bin: main.cpp *.hpp tests/*
	$(CXX) $(CXXFLAGS) main.cpp -o main.bin

clean:
	rm -f *.bin
