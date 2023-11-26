g++ ../Stack/Stack.cpp -c -o ../Stack/Stack.o

g++ source/SPUV3.cpp -c -o source/SPUV3.o

g++ ../Stack/Stack.o source/SPUV3.o -o SPUV3.exe
