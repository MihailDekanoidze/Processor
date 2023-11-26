g++ source/StrFunctions.cpp -c -o source/StrFunctions.o

g++ source/Disassembler.cpp -c -o source/Disassembler.o

g++ source/StrFunctions.o source/Disassembler.o -o Disassembler.exe
