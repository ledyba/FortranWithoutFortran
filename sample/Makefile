.PHONY: all pie shared linkerscript

all: shared linkerscript pie
	rm test.o

shared:
	gcc -c -o test.o test.c -fPIC
	ld -shared -fPIC -o test-shared.so test.o

linkerscript:
	gcc -c -o test.o test.c -fPIC 
	ld -o test-with-linkerscript test.o --script ./linker.script

pie:
	gcc -c -o test.o test.c -pie
	ld -pie -o test-pie test.o

