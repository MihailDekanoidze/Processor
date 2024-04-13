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

    if (!CSP) 
    {
        CSP->errors = ASM_ERROR_CALLOC;
        return CSP;
    }

    FILE* asm_log = fopen("Asm_log.txt", "w");

    if (!asm_log)
    {
        CSP->errors = ASM_ERROR_OPEN_FILE;
       return CSP;
    }

    CSP->assembler_log = asm_log;
    CSP->command_lines = command_lines;

    CSP->byte_code          = text_info_ctor();
    CSP->byte_code->buffer  = calloc(command_lines->elemcount * 2, sizeof(int));

    if(!CSP->byte_code->buffer)
    {
        CSP->errors = ASM_ERROR_CALLOC; 
        return CSP;
    }

    CSP->byte_code->elemcount = command_lines->elemcount * 2;
    CSP->errors = ASM_NO_ERRORS;

    return CSP;
}



assembler_error lines_to_bytecode(struct command_string_processing* CSP)
{
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

        #define ASM_COMMAND(name, id, size)                                 \
        if (strncmp(name, line, size) == 0)                                 \
        {                                                                   \
            int command_id = id;                                            \
            if (id & (1 << 7))                                              \
            {                                                               \
                Argument* arg = get_arg(line + size, AsmLog);                       \
                if (arg->error != ASM_NO_ERRORS)                            \
                {                                                           \
                    printf("Incorrect arg in line %zu\n", curr_line + 1);   \
                    assembler_error error = arg->error;                     \
                    free(arg);                                              \
                    return error;                                           \
                }                                                           \
                command_id |= arg->format;                                  \
                asm_code[ip++]   = command_id;                              \
                asm_code[ip++]   = arg->val;                                \
                free(arg);                                                  \
            }                                                               \
            else                                                            \
            {                                                               \
                asm_code[ip++]   = command_id;                              \
            }                                                               \
        }                                                           
                                                                                                                                                                
        #include "../include/Command_Description.txt"
                                        
        #undef ASM_COMMAND
        
        if (strncmp("NOPE", line, 4) == 0)
        {
            Argument* arg = get_arg(line + 4, AsmLog);
            size_t new_size = CSP->byte_code->elemcount + (size_t)arg->val;

            fprintf(AsmLog, "new size = %zu\n", new_size);
            int* new_arr = (int*)realloc(CSP->byte_code->buffer, new_size * sizeof(int));
            
            if(!new_arr) return ASM_ERROR_CALLOC;

            CSP->byte_code->buffer      = new_arr;
            CSP->byte_code->elemcount   = new_size;
            asm_code = new_arr; 
            free(arg);
        }

    }

    return ASM_NO_ERRORS;
}

Argument* get_arg(const char* source, FILE* AsmLog)
{
    Argument* arg = (Argument*) calloc(1, sizeof(Argument));
    while(isspace(*source)) source++;
    assembler_error error = ASM_NO_ERRORS;

    fprintf(AsmLog, "arg  = %s\n", source);
    if (isdigit(*source))
    {
        arg->format = Num;
        int iscorrect_num = sscanf(source, "%d", &arg->val);
        if (!iscorrect_num) error = ASM_ERROR_INCORRECT_NUM;
    }
    else if (*source == '[')
    {
        arg->format = Mem;
        int iscorrect_num = sscanf(source + 1, "%d", &arg->val);
        if (!iscorrect_num) error = ASM_ERROR_INCORRECT_NUM;   
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
            error = ASM_ERROR_UNKNOWN_REG;
        }
    }

    arg->error = error;

    fprintf(AsmLog, "arg format = %d\n", arg->format);
    fprintf(AsmLog, "arg val = %d\n", arg->val);
    fprintf(AsmLog, "arg error = %d\n", error);

    return arg;
}


void CSP_dtor(command_string_processing* CSP)
{
    if (!CSP) return;

    text_info_dtor(CSP->byte_code);
    fclose(CSP->assembler_log);

    free(CSP);
}


