g++ source\StrFunctions.cpp -c -o source\StrFunctions.o

g++ source\AssemblerV3.cpp -c -o source\AssemblerV3.o

g++ ..\Onegin\source\InputText.cpp -c -o ..\Onegin\source\InputText.o

g++ ..\Onegin\source\ProcessingText.cpp -c -o ..\Onegin\source\ProcessingText.o


g++ source\StrFunctions.o source\AssemblerV3.o ..\Onegin\source\InputText.o ..\Onegin\source\ProcessingText.o -o AssemblerV3.exe
