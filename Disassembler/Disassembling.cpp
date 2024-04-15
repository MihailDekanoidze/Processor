#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/CommonIncludes.h"
#include "../include/DisassemblerV3.h"

main_info* main_info_ctor(text_info* byte_code)
{
    main_info* disasm = (main_info*)calloc(1, sizeof(main_info));
    if (!disasm) return disasm;

    disasm->byte_code = byte_code;
    
    disasm->disasm_code = text_info_ctor();

    ERROR_PUT(!disasm->disasm_code, disasm->errors, DISASM_ERROR_CALLOC, disasm);

    disasm->disasm_code->buffer = calloc(byte_code->elemcount * INT_LEN, sizeof(char));
    disasm->disasm_code->elemcount = byte_code->elemcount * INT_LEN;

    ERROR_PUT(!disasm->byte_code->buffer, disasm->errors, DISASM_ERROR_CALLOC, disasm);

    disasm->disam_log = fopen("Disasm_log.txt", "w");

    ERROR_PUT(!disasm->disam_log, disasm->errors,  DISASM_ERROR_OPEN_FILE, disasm);

    disasm->errors = DISASM_NO_ERRORS;
    return disasm; 
}

void main_info_dtor(main_info* disasm)
{
    if (!disasm) 
    {
        printf("Null ptr was given by %s\n", __PRETTY_FUNCTION__);
        return;
    }

    text_info_dtor(disasm->disasm_code);
    fclose(disasm->disam_log);

    free(disasm);
}

disassembler_error byte_code_disasm(main_info* disasm)
{
    LOG_FUNCTION_BEGIN;

    size_t elem_count   = disasm->byte_code->elemcount;
    FILE* disasm_log    = disasm->disam_log;
    int* byte_code      = (int*)disasm->byte_code->buffer;
    char* disasm_code   = (char*)disasm->disasm_code->buffer;

    for (size_t ip = 0; ip < elem_count; ip++)
    {
        fprintf(disasm_log, "byte_code[%zu] = %d\n", ip, byte_code[ip]);

        switch (byte_code[ip])
        {
            #define ASM_COMMAND(name, id, size, dis, ...)                                         \
            case id:                                                                    \
            {                                                                           \
                sprintf(disasm_code, "%s", dis);                                       \
                disasm_code += size;                                                    \
                                                                                        \
                if (id & (1 << 7))                                                      \
                {                                                                       \
                    sprintf(disasm_code++, "%c", ' ');                                  \
                    ip++;                                                               \
                    Argument* arg =  sprint_arg(disasm_code, byte_code + ip, id);       \
                    disassembler_error error = arg->error;                              \
                    fprintf(disasm_log, "arg is %d\n", *(byte_code + ip));              \
                    disasm_code += arg->len;                                            \
                    free(arg);                                                          \
                    ERROR_PUT(error, disasm->errors, error, error);                     \
                }                                                                       \
                sprintf(disasm_code++, "\n");                                           \
                break;                                                                  \
                }                                                                                 
            #include "../include/Command_Description.txt"                  
            #undef ASM_COMMAND
            case EMPTY_COMMAND: break;
            default:
            {   
                printf("Unknown command = %d\n", byte_code[ip]);
                ERROR_PUT(1, disasm->errors, DISASM_ERROR_UNKNOWN_COMMAND, DISASM_ERROR_UNKNOWN_COMMAND);
            }
        }
    }

    LOG_FUNCTION_END;
    return DISASM_NO_ERRORS;
}

Argument* sprint_arg(char* disasm_code, int* byte_code, int command_id)
{
    Argument* arg   = (Argument*)calloc(1, sizeof(Argument));
    arg->error      = DISASM_NO_ERRORS;

    if (command_id & Num)
    {
        sprintf(disasm_code, "%lg", (double)((*byte_code)) / pow(10, ACCURACY)); 
        arg->len = strlen(disasm_code);
    }
    else if (command_id & Reg)
    {
        arg->len = 2;
        sprintf(disasm_code, "%cX", 'A' + *byte_code - 1);
    }
    else if (command_id & Mem)
    {
        sprintf(disasm_code, "[%d]", *byte_code); 
        arg->len = strlen(disasm_code);
    }
    else
    {
        arg->error = DISASM_ERROR_UNKNOWN_ARG;
    }

    return arg;
}