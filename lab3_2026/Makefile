CXX = g++
COPTS = -Wall -g -c -O0 -std=c++11 -Wno-unused-function

OBJS = main.o parse.o utils.o lex.yy.o

all: calc

calc: $(OBJS)
	$(CXX) $(OBJS) -o calc

%.o: %.cpp
	$(CXX) $(COPTS) $< -o $@

lex.yy.c: calc.l
	flex -o lex.yy.c calc.l

lex.yy.o: lex.yy.c
	$(CXX) $(COPTS) -Wno-sign-compare lex.yy.c -o lex.yy.o

clean:
	rm -f *.o calc lex.yy.c
