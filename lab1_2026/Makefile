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

COPTS    = -Wall -g -c -O0 -std=c++11

OBJS = main.o \
       langlex.o \
       langparse.o \
       cSymbolTable.o \
       cVisitor.o

all: lang

lang: $(OBJS)
	$(CXX) $(OBJS) -o lang

%.o: %.cpp
	$(CXX) $(COPTS) $< -o $@

langlex.c: lang.l langparse.c
	flex -o langlex.c lang.l

langlex.o: langlex.c
	$(CXX) $(COPTS) -Wno-sign-compare langlex.c -o langlex.o

langparse.c langparse.h: lang.y
	bison --defines=langparse.h -o langparse.c lang.y

langparse.o: langparse.c
	$(CXX) $(COPTS) langparse.c -o langparse.o

main.o: main.cpp langlex.c langparse.c
	$(CXX) $(COPTS) main.cpp -o main.o

clean:
	rm -f *.o
	rm -f lang
	rm -f langlex.c
	rm -f langparse.c
	rm -f langparse.h
	rm -f out.xml
	rm -f out2.xml
