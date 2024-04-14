#ifndef DISASSEMBLER_V3_H
#define DISASSEMBLER_V3_H

#include "InputText.h"
#include "CommonIncludes.h"


#define DISASM_ERRROR_COUNT 5
#define DIGIT_MAX sizeof(int)

#define LOG_FUNCTION_BEGIN fprintf(disasm->disam_log, "Function %s begin\n", __PRETTY_FUNCTION__);
#define LOG_FUNCTION_END   fprintf(disasm->disam_log, "Function %s end\n",   __PRETTY_FUNCTION__);


#define DISASM_PROGRAMM_FINISH          \
        text_info_dtor(byte_code);      \
        main_info_dtor(disasm);      

enum disassembler_error
{
    DISASM_NO_ERRORS             = 0UL,
    DISASM_ERROR_OPEN_FILE       = 1UL,
    DISASM_ERROR_REG             = 2UL,
    DISASM_ERROR_UNKNOWN_COMMAND = 3UL,
    DISASM_ERROR_CALLOC          = 4UL,
    DISASM_ERROR_BYTE_CODE       = 5UL,
    DISASM_ERROR_SPU_POP_REG     = 7UL,
    DISASM_ERROR_UNKNOWN_ARG     = 8UL
};

struct main_info
{
    struct text_info* byte_code;
    struct text_info* disasm_code;
    disassembler_error errors;
    FILE* disam_log;
};

struct Argument
{
    size_t              len;
    disassembler_error  error;
};



main_info*          main_info_ctor(text_info* byte_code);
void                main_info_dtor(main_info* disasm);
Argument*           sprint_arg(char* disasm_code, int* byte_code, int command_id);
disassembler_error  byte_code_disasm(main_info* disasm);

#endif // DISASSEMBLER_V3_H
