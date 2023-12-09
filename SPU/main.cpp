#include <stdio.h>
#include <malloc.h>
#include "../include/SPUV3.h"
#include "../include/Stack.h"

int main()
{
    const char ASM_FILE_NAME[] = "../Output/AssemblerArrCode";

    FILE* code = fopen(ASM_FILE_NAME, "rb"); // file name to constant

    //printf("ferror is %d\n", ferror(code));

    if (code == NULL)
    {
        printf("NULL");
        return SPU_ERROR_OPEN_FILE;
    }
    printf("code = %p\n", code);

    int symbol_code = 0;

    size_t size_code = 0;

    printf("size_code = %zu\n", size_code);

    size_code = fsize(code) / sizeof(int);

    printf("fsize: size_code = %zu\n", size_code);

    int* asm_code = (int*) calloc(size_code, sizeof(int));

    int fread_count = fread(asm_code, sizeof(int), size_code, code);

    //printf("fread_count : %d\n", fread_count);

    if (!fread_count)
    {
        printf("EMPTY FILE!\n");
        return SPU_ERROR_OPEN_FILE;
    }

    /*for (size_t i = 0; i < size_code; i++)
    {
        int symbol = 1;
        fscanf(code, "%d", &symbol);
        printf("symbol is %d\n", symbol);
        printf("command is %d\n", asm_code[i]);
    }


    printf("ferror is %d\n", ferror(code));

    printf("feof is : %d\n", feof(code));*/



    int curr_command = 0;

    size_t ip = 0;

    struct Processor SPU  = {}; // good

    struct Stack* stk = &SPU.stk; // хотя бы stk

    StackCtor(stk, base_capacity); 

    //printf("Begin\n");

    //StackPrint(stk);

    while (curr_command != HLT)
    {
        curr_command = asm_code[ip];
        //printf("CMD: %d\n", curr_command);

        //printf("ip = %zu\n", ip);

        elem_t result = 0;

        //StackPrint(stk);

        //printf("in while\n");

        //printf("curr_command = %d\n", curr_command);

        switch (curr_command)
        {
            case PUSH:
            {
                    //printf("case: PUSH\n");

                    elem_t tempt = asm_code[++ip];
                    char* reg = 0;

                    StackPush (stk, tempt);

                    ip++;

                    //printf("tempt = %d\n", tempt);

                    break;
            }
            case ADD:
            {
                    //printf("case: ADD\n");

                    elem_t tempt1 = 0;
                    elem_t tempt2 = 0;

                    StackPop(stk, &tempt1);
                    StackPop(stk, &tempt2);
                    StackPush(stk, tempt1 + tempt2);

                    ip++;

                    break;
            }
            case SUB:
            {
                    //printf("case: SUB\n");

                    elem_t tempt1 = 0;
                    elem_t tempt2 = 0;

                    StackPop(stk, &tempt1);
                    StackPop(stk, &tempt2);
                    StackPush(stk, tempt2 - tempt1);

                    ip++;

                    break;
            }
            case DIV:
            {
                    //printf("case: DIV\n");

                    elem_t tempt1 = 0;
                    elem_t tempt2 = 0;

                    StackPop(stk, &tempt1);
                    StackPop(stk, &tempt2);
                    StackPush(stk, tempt2 / tempt1);

                    ip++;

                    break;
            }
            case OUT:
            {
                    //printf("case: OUT\n");

                    elem_t result = 0;

                    //StackPrint(stk);
                    StackPop(stk, &result);
                    printf("\n\n<<<<<<Atention!>>>>>>\n\nResult = %d\n\n", result);
                    printf("SPU.ax = %lg\n", SPU.ax);
                    printf("SPU.bx = %lg\n", SPU.bx);
                    printf("SPU.cx = %lg\n", SPU.cx);
                    printf("SPU.dx = %lg\n", SPU.dx);
                    printf("StackSize = %zu\n", StackSize(stk));
                    StackClear(stk);

                    ip++;

                    break;
            }
            case MUL:
            {
                    elem_t tempt1 = 0;
                    elem_t tempt2 = 0;

                    StackPop(stk, &tempt1);
                    StackPop(stk, &tempt2);

                    StackPush(stk, tempt1 * tempt2);

                    ip++;

                    break;
            }
            case RPUSH:
            {
                    int reg_id = asm_code[++ip];

                    switch(reg_id) 
                    {
                        case 1:
                        {
                            StackPush(stk, SPU.ax);
                            break;
                        }
                        case 2:
                        {
                            StackPush(stk, SPU.bx);
                            break;
                        }
                        case 3:
                        {
                            StackPush(stk, SPU.cx);
                            break;
                        }
                        case 4:
                        {
                            StackPush(stk, SPU.dx);
                            break;
                        }
                        default:
                        {
                            return SPU_ERROR_RPUSH_REG;
                        }
                    }

                    ip++;

                    break;
            }
            case IN:
            {
                elem_t tempt = 0;

                printf("Enter the integer: ");
                scanf("%d", &tempt);

                //printf("tempt = %lg\n", tempt);

                StackPush(stk, tempt);

                ip++;

                break;
            }
            case POP:
            {
                int reg_id = asm_code[(++ip)++];

                //printf("\n<<<POP>>>\n");

                //printf("reg_id = %d\n", reg_id);
                elem_t reg = 0;

                StackPop(stk, &reg);

                switch(reg_id) // OPYAT'
                {
                    case 1: SPU.ax = reg; break;
                    case 2: SPU.bx = reg; break;
                    case 3: SPU.cx = reg; break;
                    case 4: SPU.dx = reg; break;
                    default:
                    {
                        return SPU_ERROR_SPU_POP_REG;
                    }
                }

                break;
            }
            case JMP_COMMAND: ip = asm_code[ip + 1]; break;
            case JA_COMMAND :
            {
                elem_t curr_loop = 0;
                elem_t count_loops = 0;

                StackPop(stk, &count_loops);
                StackPop(stk, &curr_loop);

                if (curr_loop > count_loops)
                {
                    ip = asm_code[ip + 1];
                }
                else
                {
                    ip += 2;
                }
                break;
            }
            case JB_COMMAND :
            {
                elem_t curr_loop = 0;
                elem_t count_loops = 0;

                StackPop(stk, &count_loops);
                StackPop(stk, &curr_loop);

                //printf("curr_loop = %d\n", curr_loop);
                //printf("count_loops = %d\n", count_loops);
                //printf("asm_code[ip + 1] = %d\n", asm_code[ip + 1]);

                if (curr_loop < count_loops)
                {
                    ip = asm_code[ip + 1];
                }
                else
                {
                    ip += 2;
                }
                break;
            }
            case JE_COMMAND :
            {
                elem_t curr_loop = 0;
                elem_t count_loops = 0;

                StackPop(stk, &count_loops);
                StackPop(stk, &curr_loop);

                if (curr_loop == count_loops)
                {
                    ip = asm_code[ip + 1];
                }
                else
                {
                    ip += 2;
                }
                break;
            }
            case JNA_COMMAND :
            {
                elem_t curr_loop = 0;
                elem_t count_loops = 0;

                StackPop(stk, &count_loops);
                StackPop(stk, &curr_loop);

                if (curr_loop >= count_loops)
                {
                    ip = asm_code[ip + 1];
                }
                else
                {
                    ip += 2;
                }
                break;
            }
            case JNB_COMMAND :
            {
                elem_t curr_loop = 0;
                elem_t count_loops = 0;

                StackPop(stk, &count_loops);
                StackPop(stk, &curr_loop);

                if (curr_loop <= count_loops)
                {
                    ip = asm_code[ip + 1];
                }
                else
                {
                    ip += 2;
                }
                break;
            }
            case JNE_COMMAND :
            {
                elem_t curr_loop = 0;
                elem_t count_loops = 0;

                StackPop(stk, &count_loops);
                StackPop(stk, &curr_loop);

                if (curr_loop != count_loops)
                {
                    ip = asm_code[ip + 1];
                }
                else
                {
                    ip += 2;
                }
                break;
            }
            case HLT:
            {
                    StackDtor(stk);
                    break;
            }
            default:
            {
                    printf("\n<<<UNEXPECTED EXIT>>>\n");

                    return SPU_ERROR_UNKNOWN_CURR_COMMAND;
                    break;
            }
        }
        /*StackPrint(stk);

        printf("SPU.ax = %lg\n", SPU.ax);
        printf("SPU.bx = %lg\n", SPU.bx);
        printf("SPU.cx = %lg\n", SPU.cx);
        printf("SPU.dx = %lg\n", SPU.dx);
        //printf("result = %lg\n", result);
        printf("StackSize = %zu\n\n", StackSize(stk));*/

    }

    free(asm_code);
}
