.PHONY: all test format clean 

all:
	gcc -fPIC -c -o calc.o calc.c -std=gnu99 -pie -fno-stack-protector
	ld -o calc.so calc.o -z execstack -pie --script ./linker.script -fno-stack-protector
	bash generate.sh
	cpp -o out.f95 template.f95
	gfortran -o prog.s out.f95 -S -masm=intel -fno-range-check
	gfortran -o prog out.f95 -g -O0 -z execstack -fno-range-check
	./prog < data.txt

test:
	gcc -o test-runner test-runner.c -std=gnu99 -lm
	./test-runner < data.txt

format:
	ruby ./format.rb out.f95 > out-formatted.f95
	gfortran -o prog out-formatted.f95 -g -O0 -z execstack -fno-range-check

clean:
	rm -f prog test-runner ftr.f95 core.* *.so *.o *.mod out*.f95 *.s *.in *.a *.exe *.dll
	rm -f doc/*.aux doc/*.dvi doc/*.log doc/*.synctex.gz

