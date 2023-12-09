#ifndef SPU_V3_H
#define SPU_V3_H

#include <stdio.h>
#include <malloc.h>
#include "Stack.h"
#include "InputText.h"


const int base_capacity = 5; 

typedef int elem_t;

enum command_size
{
    push_size = 4,
    add_size  = 3,
    div_size  = 3,
    sub_size  = 3,
    out_size  = 3,
    hlt_size  = 3, // copypaste
    in_size   = 2,
    pop_size  = 3,
    mul_size  = 3
};

enum CommandID
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
    RPUSH = 17,
    JMP_COMMAND = 33,
    JB_COMMAND  = 34,
    JNB_COMMAND = 35,
    JA_COMMAND  = 36,
    JNA_COMMAND = 37,
    JE_COMMAND  = 38,
    JNE_COMMAND = 39
};

struct Processor //< cool! add this to the asm and disasm!
{
    struct Stack stk;
    double ax;
    double bx;
    double cx;
    double dx;
};

enum ERROR_SPU // ErrorSPU
{
    SPU_ERROR_OPEN_FILE = 1,
    SPU_ERROR_PUSH_REG = 2,
    SPU_ERROR_POP_REG = 3,
    SPU_ERROR_RPUSH_REG = 4,
    SPU_ERROR_SPU_POP_REG = 5,
    SPU_ERROR_UNKNOWN_CURR_COMMAND = 6,
    SPU_ERROR_BYTE_CODE = 7
};


#endif //SPU_V3_H