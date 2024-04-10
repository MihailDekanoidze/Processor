#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include "StrFunctions.h"
#include "InputText.h"
#include "ProcessingText.h"

const size_t COMMAND_SIZE = 4;
const size_t ASM_N_OF_COMMANDS = 2;
enum Command_size
{
    push_size = 4,
    add_size  = 3,
    div_size  = 3,
    sub_size  = 3,
    out_size  = 3,
    hlt_size  = 3,
    in_size   = 2,
    pop_size  = 3,
    mul_size  = 3,
    jmp_size  = 3,
    jb_size   = 2,
    jnb_size  = 3,
    ja_size   = 2,
    jna_size  = 3,
    je_size   = 2,
    jne_size  = 3
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


enum Assembler_error
{
    ASM_ERROR_OPEN_FILE       = 3,
    ASM_ERROR_PUSH_REG        = 4,
    ASM_ERROR_POP_REG         = 5,
    ASM_ERROR_RPUSH_REG       = 6,
    ASM_ERROR_SPU_POP_REG     = 7,
    ASM_ERROR_UNKNOWN_COMMAND = 8,
    ASM_ERROR_CALLOC          = 9
};


const char push[]  = "PUSH";
const char  add[]  = "ADD";
const char  sub[]  = "SUB";
const char  div[]  = "DIV";
const char  out[]  = "OUT";
const char  hlt[]  = "HLT";
const char   in[]  = "IN";
const char  pop[]  = "POP";
const char  mul[]  = "MUL";
const char  jmp[]  = "JMP";
const char   jb[]  = "JB";
const char  jnb[]  = "JNB";
const char   ja[]  = "JA";
const char  jna[]  = "JNA";
const char   je[]  = "JE";
const char  jne[]  = "JNE";
//int* AssemblerV3(FILE* fp);


#endif // ASSEMBLER_H