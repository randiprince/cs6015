#Makefile - CS6015 MSDscript
#Targets and what they do:
#build runs the executable
#MSDscript creates the executable
#*.o targets compile .cpp and .h files into an o file
#clean removes all files and executables

CXXSOURCE = main.o commandLine.o expr.o
HEADERS = commandLine.hpp catch.h expr.hpp
CXXFLAGS = --std=c++14
COMPILER = c++
COMPILEOPTS = -c
LINKINGOPTS = -o
objects := $(wildcard *.o)

run: msdscript
	./msdscript
test: msdscript
	./msdscript --test
build:
	msdscript
msdscript: $(CXXSOURCE)
	$(COMPILER) $(CXXFLAGS) $(LINKINGOPTS) msdscript $(CXXSOURCE)
$(objects): %.o: %.cpp %.hpp
	$(COMPILER) $(COMPILEOPTS) $< -o $@
.PHONY: clean test
clean:
	rm -rf *.o msdscript
