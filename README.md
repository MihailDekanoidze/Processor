#How to use my processor to execute your prorgramm
##0)Grammar
You can read a description command in file `Command_Description.txt` in folder `/Input`.
Example 
```
ASM_COMMAND("ADD", 2, 3, "ADD",
 
    elem_t arg1 = 0;
    elem_t arg2 = 0;

    StackPop(data_stk, &arg1);
    StackPop(data_stk, &arg2);

    ERROR_PUT(data_stk->error, SPU->error, SPU_DATA_STACK_ERROR, SPU_DATA_STACK_ERROR);

    StackPush(data_stk, arg1 + arg2);
    ip++;
    break;
  )
```
##1)Your need to write a programm 
In folder '/Input'  you must create file `Commands.txt` and write in this file your prorgamm.
###You also can read examlpe programm:
a)`Factorial_Loop.txt`: use a simple circle to calculate factorial of the number you will enter.
Write `make Factorial_Loop` in main repo to start the programm.
b) `Fibonacci_Recurcion.txt`: use a ordinary recursion to calculate value of the member of Fibonacci sequence which number you will enter.
Write `make Fibonacci_Recurcion` in main repo to start the programm.
##2)You can translate your programm into bytecode and execute it at once
Write `make` in main repo
##3)For more details
You should go to appropriate folder and write `make`
a)Bytecode will be saved in folder `/Output` with name `ByteCode.txt`.
b)Use dissasembler to check bytecode in folder `Disassembler`. Disassemblered file will be saved in the folder `/Output` with name `DisassemblerArrCode.txt`.
c)Open `logs` to check programm execute.
