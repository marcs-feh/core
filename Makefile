# User config
CXX      ?= g++ -std=c++14
CXXFLAGS ?= -O0 -march=native -pipe -Wall -Wextra -g -fsanitize=address -DRELEASE_MODE
# ===========

CXXFLAGS := $(CXXFLAGS) -I. -fno-exceptions -fno-strict-aliasing -std=c++20

INTERFACER := python tools/interfacer.py

.PHONY: run clean codegen

run: main.bin
	@./main.bin

codegen: mem/internal/allocator.yaml
	 $(INTERFACER) mem/internal/allocator.yaml -guard:none -out:mem/internal/allocator_interface.hpp

main.bin: main.cpp *.hpp tests/*
	$(CXX) $(CXXFLAGS) main.cpp -o main.bin

clean:
	rm -f *.bin
