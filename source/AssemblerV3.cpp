#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "..\include\AssemblerV3.h"


int main()
{
    FILE* fp = fopen("Commands.txt", "r");

    if (fp == NULL)
    {
        return OPEN_FILE;
    }

    struct TextInfo CommandInfo = {};

    CommandInfo = InputText(CommandInfo, fp);

    struct TextInfo CommandLines = {};

    CommandLines = Lines(CommandInfo);

    int* arr_code = (int*) calloc(CommandLines.elemcount * 2, sizeof(int));

    size_t ip = 0;

    char push[] = "PUSH";
    char add[] = "ADD";
    char sub[] = "SUB";
    char div[] = "DIV";
    char out[] = "OUT";
    char hlt[] = "HLT";
    char in[] = "IN";
    char pop[] = "POP";
    char mul[] = "MUL";

    int i = 0;

    char* line = ((StringInfo*)(CommandLines.buffer))[i].address;

    /*for (int i = 0; i < CommandLines.elemcount; i++)
    {
        printf("lines[%d] = %s\n", i, ((StringInfo*)(CommandLines.buffer))[i].address);
    }

    printf("\n");*/

    i = 0;

    for (; i < CommandLines.elemcount; i++)
    {
        //printf("in while\n");

        //printf("buffer = %s\n", buffer);
        //printf("mystrcmp(buffer, push) = %d\n", mystrcmp(buffer, push));
        //printf("mystrcmp(buffer, add) = %d\n", mystrcmp(buffer, add));
        //print_str(buffer);
        //printf("strncmp(line, push, push_size) = %d\n", strncmp(line, push, push_size));

        char* line = ((StringInfo*)(CommandLines.buffer))[i].address;

        if (strncmp(line, push, push_size) == 0)
        {
            int tempt = 0;
            char reg[2] ={};

            if (sscanf(line + push_size, "%d", &tempt) == 0)
            {
                arr_code[ip] = RPUSH;
                ip++;
                sscanf(line + push_size, "%s", reg);
                int reg_id = reg[0] - 'A' + 1;
                switch(reg_id)
                {
                    case 1:
                        {
                            arr_code[ip] = 1;
                            break;
                        }
                    case 2:
                        {
                            arr_code[ip] = 2;
                            break;
                        }
                    case 3:
                        {
                            arr_code[ip] = 3;
                            break;
                        }
                    case 4:
                        {
                            arr_code[ip] = 4;
                            break;
                        }
                    default:
                        {
                            return PUSH_REG;
                        }
                }
                ip++;
            }
            else
            {
                arr_code[ip] = PUSH;
                ip++;

                arr_code[ip] = tempt;
                ip++;
            }

            //printf("tempt = %d\n", tempt);
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

            char reg[2] = {};

            sscanf(line + pop_size, "%s", reg);

            int reg_id = reg[0] - 'A' + 1;

            switch(reg_id)
            {
                case 1:
                    {
                        arr_code[ip] = 1;
                        break;
                    }
                case 2:
                    {
                        arr_code[ip] = 2;
                        break;
                    }
                case 3:
                    {
                        arr_code[ip] = 3;
                        break;
                    }
                case 4:
                    {
                        arr_code[ip] = 4;
                        break;
                    }
                default:
                    {
                        return POP_REG;
                    }
            }
            ip++;
        }
    }

    fclose(fp);

    FILE* ArrCode = fopen("AssemblerArrCode.txt", "w");

    if (ArrCode == NULL)
    {
        return OPEN_FILE;
    }

    //printf("ip = %d\n", ip);

    /*for (size_t j = 0; j < ip; j++)
    {
        printf("%d ", arr_code[j]);
    }*/

    for (size_t j = 0; j < ip; j++)
    {
        switch (arr_code[j])
        {
            case PUSH:
            {
                    //printf("case: PUSH\n");

                    fprintf(ArrCode, "%d %d\n", arr_code[j], arr_code[j + 1]);
                    j++;

                    //printf("tempt = %d\n", tempt);

                    break;
            }
            case RPUSH:
            {
                    //printf("case: PUSH\n");

                    fprintf(ArrCode, "%d %d\n", arr_code[j], arr_code[j + 1]);
                    j++;

                    //printf("tempt = %d\n", tempt);

                    break;
            }
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

    fclose(ArrCode);
}


