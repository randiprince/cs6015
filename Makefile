#Makefile - CS6015 MSDscript
#Targets and what they do:
#build runs the executable
#MSDscript creates the executable
#*.o targets compile .cpp and .h files into an o file
#clean removes all files and executables

CXXSOURCE = MSDscript/MSDscript/main.o MSDscript/MSDscript/commandLine.o MSDscript/MSDscript/expr.o MSDscript/MSDscript/parse.o MSDscript/MSDscript/val.o MSDscript/MSDscript/env.o
CXXSOURCE2 = test_msdscript/test_msdscript/main.o test_msdscript/test_msdscript/exec.o
HEADERS = MSDscript/MSDscript/commandLine.hpp MSDscript/MSDscript/expr.hpp MSDscript/MSDscript/parse.hpp MSDscript/MSDscript/val.hpp MSDscript/MSDscript/env.hpp
HEADERS2 = test_msdscript/test_msdscript/exec.h
CXXFLAGS = --std=c++14 -fsanitize=undefined -fno-sanitize-recover=undefined -O2
COMPILER = c++
COMPILEOPTS = -c
LINKINGOPTS = -o
objects := $(wildcard *.o)

msdcopy: msdcopy/MSDscript/main.cpp
	$(COMPILER) $(CXXFLAGS) msdcopy/MSDscript/main.cpp -L./Libraries -lTest -o msdcopy/MSDscript/msdcopy

MSDscript: $(CXXSOURCE)
	$(COMPILER) $(CXXFLAGS) $(LINKINGOPTS) MSDscript/MSDscript/MSDscript $(CXXSOURCE)

test_msdscript: $(CXXSOURCE2)
	$(COMPILER) $(CXXFLAGS) $(LINKINGOPTS) test_msdscript/test_msdscript/test_msdscript $(CXXSOURCE2)
	
.PHONY: clean test showdoc

run: MSDscript
	./MSDscript/MSDscript/MSDscript
	
test: MSDscript
	./MSDscript/MSDscript/MSDscript --test
	
main.o: MSDscript/MSDscript/main.cpp $(HEADERS)
	$(COMPILER) $(CXXFLAGS) $(COMPILEOPTS) main.cpp

#main.o: test_msdscript/test_msdscript/main.cpp $(HEADERS2)
#	$(COMPILER) $(CXXFLAGS) $(COMPILEOPTS) main.cpp
	
commandLine.o: MSDscript/MSDscript/commandLine.cpp $(HEADERS)
	$(COMPILER) $(CXXFLAGS) $(COMPILEOPTS) commandLine.cpp

expr.o: MSDscript/MSDscript/expr.cpp $(HEADERS)
	$(COMPILER) $(CXXFLAGS) $(COMPILEOPTS) expr.cpp
	
parse.o: MSDscript/MSDscript/parse.cpp $(HEADERS)
	$(COMPILER) $(CXXFLAGS) $(COMPILEOPTS) parse.cpp
	
val.o: MSDscript/MSDscript/val.cpp $(HEADERS)
	$(COMPILER) $(CXXFLAGS) $(COMPILEOPTS) val.cpp
	
env.o: MSDscript/MSDscript/env.cpp $(HEADERS)
	$(COMPILER) $(CXXFLAGS) $(COMPILEOPTS) env.cpp

exec.o: test_msdscript/test_msdscript/exec.cpp $(HEADERS2)
	$(COMPILER) $(CXXFLAGS) $(COMPILEOPTS) exec.cpp

clean:
	rm -rf MSDscript/MSDscript/*.o MSDscript/MSDscript/MSDscript
doc: MSDscript
	cd MSDscript/MSDscript/documentation && doxygen Doxyfile

showdoc:
	cd MSDscript/MSDscript/documentation/html && open index.html
