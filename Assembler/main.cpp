#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "../include/Registers.h"
#include "../include/AssemblerV3.h"
//#include "../include/FileProcessing.h"


int main()
{
    FILE* AsmLog = fopen("AssemblerV3.log", "w"); 

    struct TextInfo CommandLines = {};

    FILE* source_code = fopen("../Input/Commands.txt", "r");
    if (source_code == NULL)
    {
        return ASM_ERROR_OPEN_FILE;
    }

    struct TextInfo CommandInfo = {};

    //printf("before InputText\n");

    CommandInfo = InputText(CommandInfo, source_code);

    //printf("After InputText\n");

    fclose(source_code);

    struct TextInfo ArrLines = Lines(CommandInfo);

    printf("16\n");

    if (ArrLines.buffer == NULL)
    {
        printf("ArrLines ptr = NULL\n");
    }

    CommandLines.buffer = ArrLines.buffer;
    CommandLines.elemcount = ArrLines.elemcount;


    printf("21\n");

    int* tempt = (int*) calloc(CommandLines.elemcount * ASM_N_OF_COMMANDS, sizeof(int));

    if (tempt == NULL) return ASM_ERROR_CALLOC;

    int* arr_code = tempt;

    size_t ip = 0;
 
    size_t curr_line = 0; 


    for (size_t i = 0; i < CommandLines.elemcount; i++)
    {
        fprintf(AsmLog, "AssmLoglines[%-2zu] = %s\n", i, ((StringInfo*)(CommandLines.buffer))[i].address);
    }
    //fprintf...
    fprintf(AsmLog, "\n");

    for (curr_line = 0; curr_line < CommandLines.elemcount; curr_line++)
    {


        //fprintf(AsmLog, "buffer = %s\n", buffer);
        //fprintf(AsmLog, "mystrcmp(buffer, push) = %d\n", mystrcmp(buffer, push));
        //printf(AsmLog, "mystrcmp(buffer, add) = %d\n", mystrcmp(buffer, add));
        //print_str(buffer);
        //printf("strncmp(line, push, push_size) = %d\n", strncmp(line, push, push_size));

        char* line = ((StringInfo*)(CommandLines.buffer))[curr_line].address;

        fprintf(AsmLog, "line = %s\n", line);
        if (strncmp(line, push, push_size) == 0)
        {
            int arg = 0;
            char reg[50] ={}; // ?????????? buffer -> 50 ax\0<----- bx

            if (sscanf(line + push_size, "%d", &arg) == 0)
            {
                arr_code[ip] = RPUSH;
                ip++;
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
                            arr_code[ip] = reg_id;
                            break;
                        }
                    default:
                        {
                            return ASM_ERROR_PUSH_REG;
                        }
                }
                ip++;
            }
            else
            {
                arr_code[ip] = PUSH;
                ip++;

                arr_code[ip] = arg;
                ip++;
            }

            fprintf(AsmLog, "arg = %d\n", arg);
        }
        else if (strncmp(line, add, add_size) == 0)
        {
            arr_code[ip] = ADD;
            ip++;
        }
        else if(strncmp(line, sub, sub_size) == 0)
        {
            arr_code[ip] = SUB;
            ip++;
        }
        else if(strncmp(line, div, div_size) == 0)
        {
            arr_code[ip] = DIV;
            ip++;
        }
        else if(strncmp(line, out, out_size) == 0)
        {
            arr_code[ip] = OUT;
            ip++;
        }
        else if(strncmp(line, hlt, hlt_size) == 0)
        {
            arr_code[ip] = HLT;
            ip++;
        }
        else if(strncmp(line, in, in_size) == 0)
        {
            arr_code[ip] = IN;
            ip++;
        }
        else if(strncmp(line, mul, mul_size) == 0)
        {
            arr_code[ip] = MUL;
            ip++;
        }
        else if(strncmp(line, pop, pop_size) == 0)
        {
            //printf("POP = %d\n", POP);

            //printf("arr_code[%d] = %d\n", ip, arr_code[ip]);

            arr_code[ip] = POP;

            //printf("arr_code[%d] = %d\n", ip, arr_code[ip]);

            ip++;

            //printf("arr_code[%d] = %d\n", ip, arr_code[ip]);

            char reg[50] = {};

            sscanf(line + pop_size, "%s", reg);

            fprintf(AsmLog, "reg_sscaned = %s\n", reg);

            int reg_id = AsmGetRegId(reg[0]); // в функцию AsmGetRegId(char* ...)

            // В функцию - AsmPutRegToBuffer(buffer, reg_id)
            AsmPutRegToBuffer(&arr_code[ip], reg_id);
            ip++;
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
    }



    FILE* ArrCode = fopen("../Output/AssemblerArrCode.txt", "w");
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

    for (size_t j = 0; j < ip; j++)
    {

    }


    for (size_t j = 0; j < ip; j++)
    {
        switch (arr_code[j])
        {
            case PUSH:
            case RPUSH:
            case JA_COMMAND:
            case JE_COMMAND:
            case JB_COMMAND:
            case JMP_COMMAND:
            case JNA_COMMAND:
            case JNB_COMMAND:
            case JNE_COMMAND:
            case POP:
            {
                    //printf("case: PUSH\n");

                    fprintf(ArrCode, "%d %d\n", arr_code[j], arr_code[j + 1]);
                    j++;

                    //printf("tempt = %d\n", tempt);

                    break;
            }
            default:
            {
                    fprintf(ArrCode, "%d\n", arr_code[j]);

                    break;
            }
        }
    }

    free(CommandInfo.buffer);

    free(arr_code);

    free(CommandLines.buffer);


    fclose(ArrCode);
}



