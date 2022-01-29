CC=gcc

all: filter

filter.tab.c filter.tab.h:	filter.y
	bison -t -v -d $^

lex.yy.c: filter.l
	flex $^

lex.yy.o filter.tab.o: lex.yy.c filter.tab.c
	$(CC) -c $^

filter: lex.yy.o filter.tab.o main.c
	$(CC) -o filter $^

clean:
	rm filter filter.tab.o lex.yy.o filter.tab.c lex.yy.c filter.tab.h filter.output