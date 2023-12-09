#ifndef DISASSEMBLER_V3_H
#define DISASSEMBLER_V3_H

#include "InputText.h"

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

enum Disassembler_error
{
    DISASM_ERROR_OPEN_FILE       = 3,
    DISASM_ERROR_PUSH_REG        = 4,
    DISASM_ERROR_POP_REG         = 5,
    DISASM_ERROR_RPUSH_REG       = 6,
    DISASM_ERROR_SPU_POP_REG     = 7,
    DISASM_ERROR_UNKNOWN_COMMAND = 8,
    DISASM_ERROR_CALLOC          = 9,
    DISASM_ERROE_BYTE_CODE       = 10
};

#endif // DISASSEMBLER_V3_H