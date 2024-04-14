#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/CommonIncludes.h"
#include "../include/InputText.h"
#include "../include/ProcessingText.h"
#include "../include/AssemblerV3.h"

command_string_processing* CSP_ctor(text_info* command_lines)
{
    command_string_processing* CSP = (command_string_processing*)calloc(1, sizeof(command_string_processing));
    if (!CSP) return CSP;

    FILE* asm_log = fopen("Asm_log.txt", "w");

    ERROR_PUT(!asm_log, CSP->errors, ASM_ERROR_OPEN_FILE, CSP);

    CSP->assembler_log = asm_log;
    CSP->command_lines = command_lines;

    CSP->byte_code          = text_info_ctor();
    ERROR_PUT(!CSP->byte_code, CSP->errors, ASM_ERROR_CALLOC, CSP);

    CSP->byte_code->buffer  = calloc(command_lines->elemcount * 2, sizeof(int));
    CSP->byte_code->elemcount = command_lines->elemcount * 2;
    ERROR_PUT(!CSP->byte_code->buffer, CSP->errors, ASM_ERROR_CALLOC, CSP);

    CSP->errors = ASM_NO_ERRORS;

    return CSP;
}



assembler_error lines_to_bytecode(struct command_string_processing* CSP)
{
    LOG_FUNCTION_BEGIN;
    text_info* CommandLines = CSP->command_lines;
    FILE* AsmLog = CSP->assembler_log;
    int* asm_code = (int*)CSP->byte_code->buffer;
    size_t ip = 0;

    for (size_t curr_line = 0; curr_line < CommandLines->elemcount; curr_line++)
    {
        //fprintf(AsmLog, "mystrcmp(buffer, push) = %d\n", mystrcmp(buffer, push));
        //printf(AsmLog, "mystrcmp(buffer, add) = %d\n", mystrcmp(buffer, add));
        //print_str(buffer);
        //printf("strncmp(line, push, push_size) = %d\n", strncmp(line, push, push_size));

        char* line = ((StringInfo*)(CommandLines->buffer))[curr_line].address;

        fprintf(AsmLog, "line = %s\n", line);

        #define ASM_COMMAND(name, id, size, ...)                                    \
        if (strncmp(name, line, size) == 0)                                         \
        {                                                                           \
            int command_id = id;                                                    \
            if (id & (1 << 7))                                                      \
            {                                                                       \
                Argument* arg = get_arg(line + size, AsmLog);                       \
                ERROR_PUT(!arg, CSP->errors, ASM_ERROR_CALLOC, ASM_ERROR_CALLOC);   \
                                                                                    \
                assembler_error error = arg->error;                                 \
                command_id = (command_id & (Num - 1))  | arg->format;               \
                asm_code[ip++]   = command_id;                                      \
                asm_code[ip++]   = arg->val;                                        \
                fprintf(AsmLog, "command = %d\narg = %d\n", command_id, arg->val);  \
                free(arg);                                                          \
                                                                                    \
                ERROR_PUT(error, CSP->errors, error, error);                        \
            }                                                                       \
            else                                                                    \
            {                                                                       \
                fprintf(AsmLog, "command = %d\n", command_id);                      \
                asm_code[ip++]   = command_id;                                      \
            }                                                                       \
        }else                                                                           

        #include "../include/Command_Description.txt"
                                        
        #undef ASM_COMMAND
        
        if (strncmp("NOPE", line, 4) == 0)
        {
            Argument* arg = get_arg(line + 4, AsmLog);
            ERROR_PUT(!arg, CSP->errors, ASM_ERROR_CALLOC, ASM_ERROR_CALLOC);
            size_t new_size = CSP->byte_code->elemcount + (size_t)arg->val;

            assembler_error error = arg->error;
            ip = (size_t)arg->val;
            free(arg);
            ERROR_PUT(error, CSP->errors, error, error);

            fprintf(AsmLog, "new size = %zu\n", new_size);

            int* new_arr = (int*)realloc(CSP->byte_code->buffer, new_size * sizeof(int));
            ERROR_PUT(!new_arr, CSP->errors, ASM_ERROR_CALLOC, ASM_ERROR_CALLOC);
            
            memset(new_arr + CSP->byte_code->elemcount, 0, (new_size - CSP->byte_code->elemcount) * sizeof(int));
            CSP->byte_code->buffer      = new_arr;
            CSP->byte_code->elemcount   = new_size;
            asm_code = new_arr; 
        }
        else if((isspace(*line)) || (!(*line))){}
        else 
        {
            printf("line is %s(%d)\n", line, *line);
            ERROR_PUT(1, CSP->errors, ASM_ERROR_UNKNOWN_COMMAND, ASM_ERROR_UNKNOWN_COMMAND);
        }

    }
    LOG_FUNCTION_END;
    return ASM_NO_ERRORS;
}

Argument* get_arg(const char* source, FILE* AsmLog)
{
    Argument* arg = (Argument*) calloc(1, sizeof(Argument));
    if (!arg) return arg;

    while(isspace(*source)) source++;
    arg->error = ASM_NO_ERRORS;

    fprintf(AsmLog, "arg  = %s\n", source);
    if (isdigit(*source) || (*source == '-'))
    {
        arg->format = Num;
        int iscorrect_num = sscanf(source, "%d", &arg->val);

        ERROR_PUT(!iscorrect_num, arg->error, ASM_ERROR_INCORRECT_NUM, arg);
    }
    else if (*source == '[')
    {
        arg->format = Mem;
        int iscorrect_num = sscanf(source + 1, "%d", &arg->val);
        ERROR_PUT(!iscorrect_num, arg->error, ASM_ERROR_INCORRECT_NUM, arg);  
    }
    else
    {
        int reg = asm_get_reg_id(*source);
        if ((reg < 5) && (reg > 0))
        {
            arg->format = Reg;
            arg->val    = reg;
        }
        else 
        {
            ERROR_PUT(1, arg->error, ASM_ERROR_UNKNOWN_REG, arg);
        }
    }

    fprintf(AsmLog, "arg format = %d\n", arg->format);
    fprintf(AsmLog, "arg val = %d\n", arg->val);
    fprintf(AsmLog, "arg error = %d\n", arg->error);

    return arg;
}


void CSP_dtor(command_string_processing* CSP)
{
    if (!CSP) 
    {
        printf("Null ptr was given by %s\n", __PRETTY_FUNCTION__);
        return;
    }

    text_info_dtor(CSP->byte_code);
    fclose(CSP->assembler_log);

    free(CSP);
}


