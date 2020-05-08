

YASMFLAGS=-f elf64 -g dwarf2
LDFLAGS=-g -static

gcd: gcd.o getnum.o putnum.o usage.o wrapper.o
	ld -e start $(LDFLAGS) -o gcd gcd.o getnum.o putnum.o usage.o wrapper.o


gcd.o: gcd.yasm
	yasm $(YASMFLAGS) -o gcd.o gcd.yasm

getnum.o: getnum.yasm
	yasm $(YASMFLAGS) -o getnum.o getnum.yasm

putnum.o: putnum.yasm
	yasm $(YASMFLAGS) -o putnum.o putnum.yasm

usage.o: usage.yasm
	yasm $(YASMFLAGS) -o usage.o usage.yasm

wrapper.o: wrapper.yasm
	yasm $(YASMFLAGS) -o wrapper.o wrapper.yasm



