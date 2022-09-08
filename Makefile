CC=g++

all: filter

filter.tab.c filter.tab.h filter.yy.c : filter.l filter.y
	bison -t -v -d filter.y
	flex -o filter.yy.c --header-file=filter.yy.h filter.l

filter: main.cc filter.tab.c filter.yy.c ast.cc parser.cc FilterTree.cc
	$(CC) -g -std=c++11 -o filter $^

clean:
	rm filter *.o core.*