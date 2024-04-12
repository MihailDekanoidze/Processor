#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "CommonIncludes.h"
#include "InputText.h"
#include "../include/Registers.h"


#define LOG_FUNCTION_BEGIN fprintf(CSP->assembler_log, "Function %s begin\n", __PRETTY_FUNCTION__);
#define LOG_FUNCTION_END   fprintf(CSP->assembler_log, "Function %s end\n",   __PRETTY_FUNCTION__);
#define CHECK_ADDRESS_NULL(address, error) if (address == NULL){CSP->errors = error; return error;}
#define ASM_LOG_(expression, arg) fprintf(CSP->assembler_log, expression, arg);


#define PROGRAMM_FINISH                 \
        text_info_dtor(chars_buffer);   \
        text_info_dtor(command_lines);  \
        CSP_dtor(CSP)               


const int Num = (1 << 8);
const int Reg = (1 << 9);
const int Mem = (1 << 10);

enum assembler_error
{
    ASM_NO_ERRORS             = 0,
    ASM_ERROR_COMMAND_EMPTY   = 2,
    ASM_ERROR_OPEN_FILE       = 3,
    ASM_ERROR_POP_REG         = 5,
    ASM_ERROR_RPUSH_REG       = 6,
    ASM_ERROR_UNKNOWN_COMMAND = 8,
    ASM_ERROR_CALLOC          = 9,
    ASM_ERROR_NULLPTR         = 10,
    ASM_MEMORY_ACCESS         = 11,
    ASM_ERROR_UNKNOWN_REG     = 12,
    ASM_ERROR_INCORRECT_NUM   = 13
};


struct Argument
{
    int             format;
    int             val; 
    assembler_error error;
};


struct command_string_processing
{
    struct text_info* command_lines;
    FILE* assembler_log;
    void* arr_code;
    size_t arr_code_size;
    enum assembler_error errors;
};



Errors                      file_to_buffer(const char* file_name, text_info* buffer);
assembler_error             code_arr_ctor(struct command_string_processing* CSP);
assembler_error             lines_to_bytecode(struct command_string_processing* CSP);
assembler_error             bytecode_to_file(char* , struct command_string_processing* CSP);
assembler_error             error_check(struct command_string_processing*, const char*);
const char*                 error_message(assembler_error error);
Argument*                   get_arg(const char* source);
command_string_processing*  CSP_ctor(text_info* command_lines);
void                        CSP_dtor(command_string_processing* CSP);

#endif // ASSEMBLER_H