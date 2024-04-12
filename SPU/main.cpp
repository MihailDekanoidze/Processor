#include <stdio.h>
#include <malloc.h>
#include "../include/SPUV3.h"
#include "../include/Stack.h"


// #define SPU_DEBUG 1
int main(int argc, char** argv)
{   
    if (!argc)
    {
        printf("No any files!\n");
        return 1;
    }

    byte_code_info* asm_code = byte_code_input(argv[1]);

    if (asm_code->error)
    {
        return asm_code->error;
    }

    int curr_command = 0;
    size_t ip = 0;
    struct Processor* SPU  = SPU_ctor();

    int* asm_code
    char zero_flag =  0;
        
    while (curr_command != HLT)
    {
        int check_zero_flag = asm_code[ip] & (1 << 10);

        //printf("check_zero_flag = %d\n", check_zero_flag);

        //printf("zero_flag = %d\n", zero_flag);

        //printf("curr_command = %d\n", asm_code[ip]);

        if ((check_zero_flag && !zero_flag) || (!check_zero_flag))
        {
            curr_command = (asm_code[ip]);

            //printf("ip = %zu\n", ip);
            //printf("Command = %d\n", asm_code[ip]);

            elem_t result = 1;

            switch (curr_command)
            {
                case PUSH:
                {
                        elem_t tempt = asm_code[++ip];

                        StackPush (stk, tempt);

                        ip++;

                        break;
                }
                case ADD:
                {
                        elem_t tempt1 = 0;
                        elem_t tempt2 = 0;

                        StackPop(stk, &tempt1);
                        StackPop(stk, &tempt2);

                        result = tempt1 + tempt2;

                        StackPush(stk, result);

                        ip++;

                        break;
                }
                case SUB:
                {
                        elem_t tempt1 = 0;
                        elem_t tempt2 = 0;

                        StackPop(stk, &tempt1);
                        StackPop(stk, &tempt2);

                        result = tempt2 - tempt1;

                        StackPush(stk, result);

                        ip++;

                        break;
                }
                case DIV:
                {
                        elem_t tempt1 = 0;
                        elem_t tempt2 = 0;

                        StackPop(stk, &tempt1);
                        StackPop(stk, &tempt2);

                        result = tempt2 / tempt1;

                        StackPush(stk, result);

                        ip++;

                        break;
                }
                case OUT:
                {
                        result = 0;

                        StackPop(stk, &result);
                        printf("\n\n<<<<<<Atention!>>>>>>\n\nResult = %d\n\n", result);
                        printf("SPU.ax = %d\n", SPU.ax);
                        printf("SPU.bx = %d\n", SPU.bx);
                        printf("SPU.cx = %d\n", SPU.cx);
                        printf("SPU.dx = %d\n", SPU.dx);
                        printf("StackSize = %zu\n", StackSize(stk));

                        ip++;

                        break;
                }
                case MUL:
                {
                        elem_t tempt1 = 0;
                        elem_t tempt2 = 0;

                        StackPop(stk, &tempt1);
                        StackPop(stk, &tempt2);

                        result = tempt1 * tempt2;
                        StackPush(stk, result);

                        ip++;

                        break;
                }
                case RPUSH:
                {
                        int reg_id = asm_code[(++ip)];

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
                    int arg_scaned = scanf("%d", &tempt);

                    if (!arg_scaned)
                    {
                        printf("Неудалось считать аршумент\n");
                        return SPU_EMPTY_ARG;
                    }

                    StackPush(stk, tempt);

                    ip++;

                    break;
                }
                case RPOP:
                {
                    int reg_id = asm_code[(++ip)++];

                    elem_t reg = 0;

                    StackPop(stk, &reg);

                    switch(reg_id) 
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
                case PUSH_RAM:
                {
                    size_t memory_address = (size_t)asm_code[ip + 1];
                    StackPush(stk, memory_address)
                }
                case JMP_COMMAND: ip = (size_t)asm_code[ip + 1]; break;
                case JA_COMMAND :
                {
                    elem_t curr_loop = 0;
                    elem_t count_loops = 0;

                    StackPop(stk, &count_loops);
                    StackPop(stk, &curr_loop);

                    if (curr_loop > count_loops)
                    {
                        ip = (size_t)asm_code[ip + 1];
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

                    if (curr_loop < count_loops)
                    {
                        ip = (size_t)asm_code[ip + 1];
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
                        ip = (size_t)asm_code[ip + 1];
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
                        ip = (size_t)asm_code[ip + 1];
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
                        ip = (size_t)asm_code[ip + 1];
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
                        ip = (size_t)asm_code[ip + 1];
                    }
                    else
                    {
                        ip += 2;
                    }
                    break;
                }
                case CALL:
                {
                    StackPush(&return_stk, int(ip + 2));

                    ip = (size_t)asm_code[ip + 1];

                    //printf("current ip = %zu\n", ip);

                    break;
                }
                case RET:
                {
                    elem_t return_ptr = 0;

                    StackPop(&return_stk, &return_ptr);

                    ip = (size_t)return_ptr; 
                    
                    break;
                }
                case HLT:
                {
                        StackDtor(stk);
                        StackDtor(&return_stk);
                        break;
                }
                default:
                {
                        printf("\n<<<UNEXPECTED EXIT>>>\n");
                        printf("Unkown command is %d\n", curr_command);
                        /*for (size_t i = ip ; i < fread_count; i++)           \
                        {                                                   \
                            printf("asm_code[%zu] = %d\n", i, asm_code[i]); \
                        }*/
                        //printf("next  command is %d\n", asm_code[ip + 1]);

                        return SPU_ERROR_UNKNOWN_CURR_COMMAND;
                        break;
                }
            }

            zero_flag = !result;


            //StackPrint(stk);

            //printf("if After command[%d] zero_flag is %d\n", curr_command, zero_flag);
    
        }
        else
        {
            zero_flag = 0;
            //printf("else After command[%d] zero_flag is %d\n", curr_command, zero_flag);
    
            ip++;
        }

    }

    SPU_dtor(SPU);
}
