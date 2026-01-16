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

COPTS=-Wall -g -c -O0 -std=c++11 
OBJS = main.o \
       langlex.o \
       cSymbolTable.o

all: lang

lang: $(OBJS)
	$(CXX) $(OBJS) -o lang

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

langlex.c: lang.l
	flex -o langlex.c lang.l

langlex.o: langlex.c
	$(CXX) $(CXXFLAGS) -Wno-sign-compare -c langlex.c -o langlex.o

clean:
	rm -f *.o
	rm -f lang
	rm -f langlex.c
	rm -f out.xml
	rm -f out2.xml

