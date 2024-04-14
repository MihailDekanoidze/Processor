all:	Asm.o SPU.o

Factorial_Loop:	AsmF.o SPU.o

AsmF.o:
	./Assembler/Assembler ./Input/Factorial_Loop.txt ./Output/ByteCode.txt


Asm.o:
	./Assembler/Assembler ./Input/Commands.txt ./Output/ByteCode.txt 
	
SPU.o:
	./SPU/SPU	./Output/ByteCode.txt