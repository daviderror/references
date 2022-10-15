asm_program: asm_program.o
	ld -o asm_program asm_0_0.o asm_0_1.o asm_0_2.o

asm_program.o: asm_0_0.s asm_0_1.s asm_0_2.s
	as -o asm_0_0.o asm_0_0.s
	as -o asm_0_1.o asm_0_1.s
	as -o asm_0_2.o asm_0_2.s

clean:
	rm *.o asm_program