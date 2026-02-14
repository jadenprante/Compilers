#**************************************
# Makefile
#
# Makefile for lang compiler
#
# Author: Phil Howard 
# phil.howard@oit.edu
#
# Date: Jan. 12, 2016
#

# Makefile for Lab1 Compiler
CXX = g++
CXXFLAGS = -Wall -g -O0 -std=c++11

OBJS = langparse.o langlex.o main.o cSymbolTable.o

all: lang

lang: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o lang

# -------------------------------
# Bison (generate cpp and header)
# -------------------------------
langparse.cpp langparse.h: lang.y
	bison --defines=langparse.h --output=langparse.cpp lang.y

langparse.o: langparse.cpp langparse.h
	$(CXX) $(CXXFLAGS) -c langparse.cpp -o langparse.o

# -------------------------------
# Flex
# -------------------------------
langlex.c: lang.l langparse.h
	flex -o langlex.c lang.l

langlex.o: langlex.c langparse.h
	$(CXX) $(CXXFLAGS) -Wno-sign-compare -c langlex.c -o langlex.o

# -------------------------------
# Other objects
# -------------------------------
main.o: main.cpp langparse.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

cSymbolTable.o: cSymbolTable.cpp cSymbolTable.h
	$(CXX) $(CXXFLAGS) -c cSymbolTable.cpp -o cSymbolTable.o

clean:
	rm -f *.o lang langlex.c langparse.cpp langparse.h y.tab.h
