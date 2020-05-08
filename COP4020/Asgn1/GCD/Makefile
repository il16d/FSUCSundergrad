

YASMFLAGS=-f elf64 -g dwarf2
LDFLAGS=-g -static

gcd: gcd-euclid.o getnum.o putnum.o usage.o wrapper.o mydiv.o
	ld -e start $(LDFLAGS) -o gcd gcd-euclid.o getnum.o putnum.o usage.o wrapper.o mydiv.o


gcd-euclid.o: gcd-euclid.yasm
	yasm $(YASMFLAGS) -o gcd-euclid.o  gcd-euclid.yasm 

getnum.o: getnum.yasm
	yasm $(YASMFLAGS) -o getnum.o getnum.yasm

putnum.o: putnum.yasm
	yasm $(YASMFLAGS) -o putnum.o putnum.yasm

usage.o: usage.yasm
	yasm $(YASMFLAGS) -o usage.o usage.yasm

wrapper.o: wrapper.yasm
	yasm $(YASMFLAGS) -o wrapper.o wrapper.yasm

mydiv.o: mydiv.yasm
	yasm $(YASMFLAGS) -o mydiv.o mydiv.yasm


