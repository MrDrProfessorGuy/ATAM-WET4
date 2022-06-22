


out: main.o ReadLib.o ElfReader.o
	gcc -std=c99 *.c -o prf
