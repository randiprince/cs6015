#Makefile - CS6015 MSDscript
#Targets and what they do:
#build runs the executable
#MSDscript creates the executable
#*.o targets compile .cpp and .h files into an o file
#clean removes all files and executables

CXXSOURCE = main.o commandLine.o expr.o
HEADERS = commandLine.hpp expr.hpp
CXXFLAGS = --std=c++14
COMPILER = c++
COMPILEOPTS = -c
LINKINGOPTS = -o
objects := $(wildcard *.o)

msdscript: $(CXXSOURCE)
	$(COMPILER) $(CXXFLAGS) $(LINKINGOPTS) msdscript $(CXXSOURCE)
	
.PHONY: clean test

run: msdscript
	./msdscript
	
test: msdscript
	./msdscript --test
	
main.o: main.cpp $(HEADERS)
	$(COMPILER) $(CXXFLAGS) $(COMPILEOPTS) main.cpp
	
commandLine.o: commandLine.cpp $(HEADERS)
	$(COMPILER) $(CXXFLAGS) $(COMPILEOPTS) commandLine.cpp

expr.o: expr.cpp $(HEADERS)
	$(COMPILER) $(CXXFLAGS) $(COMPILEOPTS) expr.cpp

clean:
	rm -rf *.o msdscript
