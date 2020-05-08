
#for x86 intel
# nasm command
nasm -f elf32 RandomOrder.s
#link 
ld -m elf_i386 RandomOrder.o -o RandomOrder
#run
./RandomOrder

# 
g++ -m32 randomOrder.cpp -o randomOrder_c

./randomOrder_c



