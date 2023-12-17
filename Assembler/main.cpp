#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "../include/Registers.h"
#include "../include/AssemblerV3.h"


int main()
{
    FILE* AsmLog = fopen("AssemblerV3.log", "w"); 

    FILE* source_code = fopen("../Input/Commands.txt", "r");
    if (source_code == NULL)
    {
        return ASM_ERROR_OPEN_FILE;
    }

    struct TextInfo* CommandInfo = InputText(source_code);

    if (!CommandInfo)
    {
        return ASM_ERROR_COMMAND_EMPTY;
    }

    fclose(source_code);

    struct TextInfo* ArrLines = Lines(CommandInfo);

    if (ArrLines->buffer == NULL)
    {
        return ASM_ERROR_COMMAND_EMPTY;
    }

    struct TextInfo CommandLines = {    
                                    ArrLines->buffer,
                                    ArrLines->elemcount
                                    };


    size_t arr_size = CommandLines.elemcount * ASM_N_OF_COMMANDS;

    int* tempt = (int*) calloc(arr_size, sizeof(int));

    if (tempt == NULL) return ASM_ERROR_CALLOC;

    int* arr_code = tempt;

    size_t ip = 0;
 
    size_t curr_line = 0; 


    for (size_t i = 0; i < CommandLines.elemcount; i++)
    {
        fprintf(AsmLog, "AssmLoglines[%-2zu] = %s\n", i, ((StringInfo*)(CommandLines.buffer))[i].address);
    }

    fprintf(AsmLog, "\n");

    for (curr_line = 0; curr_line < CommandLines.elemcount; curr_line++)
    {
        char* line = ((StringInfo*)(CommandLines.buffer))[curr_line].address;

        fprintf(AsmLog, "line = %s\n", line);
        if (strncmp(line, push, push_size) == 0)
        {
            int arg = 0;
            char reg[50] ={}; 

            if (sscanf(line + push_size, "%d", &arg) == 0)
            {
                arr_code[ip++] = RPUSH;

                sscanf(line + push_size, "%s", reg);
                fprintf(AsmLog, "reg_sscaned = %s\n", reg);

                int reg_id = AsmGetRegId(reg[0]);
                fprintf(AsmLog, "reg_id of %s = %d\n", reg, reg_id);
                switch(reg_id)
                {
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                        {
                            arr_code[ip++] = reg_id;
                            break;
                        }
                    default:
                        {
                            return ASM_ERROR_PUSH_REG;
                        }
                }
            }
            else
            {
                arr_code[ip++] = PUSH;

                arr_code[ip++] = arg;
            }

            fprintf(AsmLog, "arg = %d\n", arg);
        }
        else if (strncmp(line, add, add_size) == 0)
        {
            arr_code[ip++] = ADD;
        }
        else if(strncmp(line, sub, sub_size) == 0)
        {
            arr_code[ip++] = SUB;
        }
        else if(strncmp(line, div, div_size) == 0)
        {
            arr_code[ip++] = DIV;
        }
        else if(strncmp(line, out, out_size) == 0)
        {
            arr_code[ip++] = OUT;
        }
        else if(strncmp(line, hlt, hlt_size) == 0)
        {
            arr_code[ip++] = HLT;
        }
        else if(strncmp(line, in, in_size) == 0)
        {
            arr_code[ip++] = IN;
        }
        else if(strncmp(line, mul, mul_size) == 0)
        {
            arr_code[ip++] = MUL;
        }
        else if(strncmp(line, pop, pop_size) == 0)
        {
            arr_code[ip++] = POP;

            char reg[50] = {};

            sscanf(line + pop_size, "%s", reg);

            fprintf(AsmLog, "reg_sscaned = %s\n", reg);

            int reg_id = AsmGetRegId(reg[0]); 

            AsmPutRegToBuffer(&arr_code[ip++], reg_id);
        }
        else if(strncmp(line, jmp, jmp_size) == 0)
        {
            int arg = 0;
            arr_code[ip++] = JMP_COMMAND;
            sscanf(line + jmp_size, "%d", &arg);
            arr_code[ip++] = arg;
        }
        else if(strncmp(line, jb, jb_size) == 0)
        {
            int arg = 0;
            arr_code[ip++] = JB_COMMAND;
            sscanf(line + jb_size, "%d", &arg);
            arr_code[ip++] = arg;
        }
        else if(strncmp(line, jnb, jnb_size) == 0)
        {
            int arg = 0;
            arr_code[ip++] = JNB_COMMAND;
            sscanf(line + jnb_size, "%d", &arg);
            arr_code[ip++] = arg;
        }
        else if(strncmp(line, ja, ja_size) == 0)
        {
            int arg = 0;
            arr_code[ip++] = JA_COMMAND;
            sscanf(line + ja_size, "%d", &arg);
            arr_code[ip++] = arg;
        }
        else if(strncmp(line, jna, jna_size) == 0)
        {
            int arg = 0;
            arr_code[ip++] = JNA_COMMAND;
            sscanf(line + jna_size, "%d", &arg);
            arr_code[ip++] = arg;
        }
        else if(strncmp(line, je, je_size) == 0)
        {
            int arg = 0;
            arr_code[ip++] = JE_COMMAND;
            sscanf(line + je_size, "%d", &arg);
            arr_code[ip++] = arg;
        }
        else if(strncmp(line, jne, jne_size) == 0)
        {
            int arg = 0;
            arr_code[ip++] = JNE_COMMAND;
            sscanf(line + jne_size, "%d", &arg);
            arr_code[ip++] = arg;
        }
        else if(strncmp(line, call, call_size) == 0)
        {
            int arg = 0;
            arr_code[ip++] = CALL;
            sscanf(line + call_size, "%d", &arg);
            arr_code[ip++] = arg;
        }
        else if(strncmp(line, org, org_size) == 0)
        {
            int arg = 0;

            sscanf(line + org_size, "%d", &arg);

            arr_size += arg;

            int* tempt = (int*)realloc(arr_code, sizeof(tempt[0])*(arr_size + 2));

            if (tempt == NULL)
            {
                return ASM_ERROR_CALLOC;
            }

            arr_code = tempt;

            while (ip != arg)
            {
                arr_code[++ip] = 0;
            }

        }
        else if(strncmp(line, ret, ret_size) == 0)
        {
            arr_code[ip++] = RET;
        }
    }

    arr_size = ip;



    FILE* ArrCode = fopen("../Output/AssemblerArrCode", "wb");
    if (ArrCode == NULL)
    {
        return ASM_ERROR_OPEN_FILE;
    }


    fprintf(AsmLog, "ip = %zu\n", ip);

    for (size_t j = 0; j < ip; j++)
    {
        fprintf(AsmLog, "%-2d :", arr_code[j]);
        fprintf(AsmLog, "[%zu]\n", j);
    }

    fprintf(AsmLog, "\n");

    fwrite(arr_code, sizeof(int), arr_size, ArrCode);


    free(CommandInfo->buffer);

    free(CommandInfo);

    free(arr_code);

    free(ArrLines);

    free(CommandLines.buffer);


    fclose(ArrCode);
}



