g++ ..\Stack\Stack.cpp -c -o ..\Stack\Stack.o

g++ source\interpreter.cpp -c -o source\interpreter.o

g++ source\StrFunctions.cpp -c -o source\StrFunctions.o


g++ source\StrFunctions.o ..\Stack\Stack.o source\interpreter.o -o interpreter.exe
