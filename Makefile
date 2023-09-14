CXX=clang++ -std=c++20
CXXFLAGS=-O1 -march=native -pipe -I. -Wall -Wextra -fno-exceptions -fno-strict-aliasing

.PHONY: run clean

run: main.bin
	@./main.bin

main.bin: main.cpp *.hpp tests/*
	$(CXX) $(CXXFLAGS) main.cpp -o main.bin

clean:
	rm -f *.bin
