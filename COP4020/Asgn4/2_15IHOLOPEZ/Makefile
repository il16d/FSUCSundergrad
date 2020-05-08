
CC=clang -pedantic -g

targets : 2_15

2_15 : 2_15.o parse-2.15-recdescent.o lexer-v2-1.o
	$(CC) -o 2_15 2_15.o parse-2.15-recdescent.o lexer-v2-1.o

2_15.o : 2_15.c lexer-v2-1.h
	$(CC) -c 2_15.c

parse-2.15-recdescent.o: parse-2.15-recdescent.c lexer-v2-1.h
	$(CC) -c parse-2.15-recdescent.c

lexer-v2-1.o: lexer-v2-1.c lexer-v2-1.h
	$(CC) -c lexer-v2-1.c



clean:
	rm -f *.o 2_15
