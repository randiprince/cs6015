#Makefile - CS6015 MSDscript
#Targets and what they do:
#build runs the executable
#MSDscript creates the executable
#*.o targets compile .cpp and .h files into an o file
#clean removes all files and executables

CXXSOURCE = MSDscript/MSDscript/main.o MSDscript/MSDscript/commandLine.o MSDscript/MSDscript/expr.o
HEADERS = MSDscript/MSDscript/commandLine.hpp MSDscript/MSDscript/expr.hpp
CXXFLAGS = --std=c++14
COMPILER = c++
COMPILEOPTS = -c
LINKINGOPTS = -o
objects := $(wildcard *.o)

MSDscript: $(CXXSOURCE)
	$(COMPILER) $(CXXFLAGS) $(LINKINGOPTS) MSDscript/MSDscript/MSDscript $(CXXSOURCE)

	
.PHONY: clean test

run: MSDscript
	./MSDscript/MSDscript/MSDscript
	
test: MSDscript
	./MSDscript/MSDscript/MSDscript --test
	
main.o: MSDscript/MSDscript/main.cpp $(HEADERS)
	$(COMPILER) $(CXXFLAGS) $(COMPILEOPTS) main.cpp
	
commandLine.o: MSDscript/MSDscript/commandLine.cpp $(HEADERS)
	$(COMPILER) $(CXXFLAGS) $(COMPILEOPTS) commandLine.cpp

expr.o: MSDscript/MSDscript/expr.cpp $(HEADERS)
	$(COMPILER) $(CXXFLAGS) $(COMPILEOPTS) expr.cpp

clean:
	rm -rf *.o MSDscript/MSDscript/MSDscript
