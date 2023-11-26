#include "StrFunctions.h"
#include "..\..\Onegin\include\InputText.h"
#include "..\..\Onegin\include\ProcessingText.h"

#define commandsize 4

enum command_size
{
    push_size = 4,
    add_size = 3,
    div_size = 3,
    sub_size = 3,
    out_size = 3,
    hlt_size = 3,
    in_size = 2,
    pop_size = 3,
    mul_size = 3
};

enum command
{
    PUSH = 1,
    ADD = 2,
    SUB = 3,
    DIV = 4,
    OUT = 5,
    HLT = -1,
    IN = 6,
    MUL = 7,
    POP = 32,
    RPUSH = 17
};

enum ERROR
{
    OPEN_FILE = 3,
    PUSH_REG = 4,
    POP_REG = 5,
    RPUSH_REG = 6,
    SPU_POP_REG = 7,
    UNKNOWN_COMMAND = 8
};

//int* AssemblerV3(FILE* fp);
