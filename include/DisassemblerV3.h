#ifndef DISASSEMBLER_V3_H
#define DISASSEMBLER_V3_H

#include "InputText.h"
#include "CommonIncludes.h"
#include "MyFunctions.h"


#define DISASM_ERRROR_COUNT 5
#define DIGIT_MAX sizeof(int)

#define LOG_FUNCTION_BEGIN fprintf(disasm_code->disam_log, "Function %s begin\n", __PRETTY_FUNCTION__);
#define LOG_FUNCTION_END   fprintf(disasm_code->disam_log, "Function %s end\n",   __PRETTY_FUNCTION__);

struct main_info
{
    struct text_info* byte_code_arr;
    struct text_info* disasm_code_arr;
    size_t errors;
    FILE* disam_log;
};

enum disassembler_error
{
    DISASM_NO_ERRORS             = 0UL,
    DISASM_ERROR_OPEN_FILE       = 1UL,
    DISASM_ERROR_REG             = 2UL,
    DISASM_ERROR_UNKNOWN_COMMAND = 3UL,
    DISASM_ERROR_CALLOC          = 4UL,
    DISASM_ERROR_BYTE_CODE       = 5UL,
    DISASM_ERROR_SPU_POP_REG     = 7UL
};

static const char* error_message_text[] =
{
    "no problem\n",
    "Can not open the file\n",
    "Register does not exist\n",
    "An unknown command was encountered\n",
    "Out of memory for calloc\n",
    "Bytecode has been damaged\n"
};



disassembler_error  files_to_buffer(struct main_info* disasm_code, char* input_file);
disassembler_error  asm_code_to_file(struct main_info* disasm_code, char* output_file);
disassembler_error  byte_code_to_asm_code(struct main_info* disams_code);
void                disasm_dtor(main_info* disasm_code);
size_t              disasm_verify(main_info* disasm_code);
size_t              number_len(int* source);

#endif // DISASSEMBLER_V3_H
