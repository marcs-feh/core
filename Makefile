# User config
CXX      ?= clang++ -std=c++14
PYTHON   ?= python
CXXFLAGS ?= -O2 -pipe -g 
# -fsanitize=address -DRELEASE_MODE
# ===========

CXXFLAGS := $(CXXFLAGS) -Wall -Wextra -I. -fno-exceptions -fno-strict-aliasing

.PHONY: run clean codegen

run: main.bin
	@./main.bin

codegen:
	 $(PYTHON) generate_interfaces.py

main.bin: main.cpp *.hpp tests/*
	$(CXX) $(CXXFLAGS) main.cpp -o main.bin

clean:
	rm -f *.bin
