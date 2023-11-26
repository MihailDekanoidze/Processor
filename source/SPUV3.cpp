#include <stdio.h>
#include <malloc.h>
#include "..\..\Stack\Stack.h"
#define base_capacity 70


typedef double elem_t;

enum command_size
{
    push_size = 4,
    add_size = 3,
    div_size = 3,
    sub_size = 3,
    out_size = 3,
    hlt_size = 3,
    in_size = 2,
    pop_size = 3,
    mul_size = 3
};

enum command
{
    PUSH = 1,
    ADD = 2,
    SUB = 3,
    DIV = 4,
    OUT = 5,
    HLT = -1,
    IN = 6,
    MUL = 7,
    POP = 32,
    RPUSH = 17
};

struct Processor
{
    struct Stack st;
    double ax;
    double bx;
    double cx;
    double dx;
};

enum ERROR_SPU
{
    OPEN_FILE = 1,
    PUSH_REG = 2,
    POP_REG = 3,
    RPUSH_REG = 4,
    SPU_POP_REG = 5,
    UNKNOWN_COMMAND = 6
};

int main()
{
    FILE* code = fopen("AssemblerArrCode.txt", "r");

    if (code == NULL)
    {
        return OPEN_FILE;
    }
    //printf("code = %p\n", code);

    int command = 0;

    fscanf(code, "%d", &command);

    struct Processor SPU  = {};

    struct Stack* st = &SPU.st;

    StackCtor(st, base_capacity);

    while (command != HLT)
    {
        //printf("CMD: %d\n", command);
        //printf("in while\n");

        //printf("command = %d\n", command);

        switch (command)
        {
            case PUSH:
            {
                    //printf("case: PUSH\n");

                    elem_t tempt = 0;
                    char* reg = 0;

                    fscanf(code, "%lg", &tempt);
                    StackPush (st, tempt);

                    //printf("tempt = %d\n", tempt);

                    break;
            }
            case ADD:
            {
                    //printf("case: ADD\n");

                    elem_t tempt1 = 0;
                    elem_t tempt2 = 0;

                    StackPop(st, &tempt1);
                    StackPop(st, &tempt2);
                    StackPush(st, tempt1 + tempt2);

                    break;
            }
            case SUB:
            {
                    //printf("case: SUB\n");

                    elem_t tempt1 = 0;
                    elem_t tempt2 = 0;

                    StackPop(st, &tempt1);
                    StackPop(st, &tempt2);
                    StackPush(st, tempt2 - tempt1);

                    break;
            }
            case DIV:
            {
                    //printf("case: DIV\n");

                    elem_t tempt1 = 0;
                    elem_t tempt2 = 0;

                    StackPop(st, &tempt1);
                    StackPop(st, &tempt2);
                    StackPush(st, tempt2 / tempt1);

                    break;
            }
            case OUT:
            {
                    //printf("case: OUT\n");

                    elem_t result = 0;
                    StackPop(st, &result);
                    printf("SPU.ax = %lg\n", SPU.ax);
                    printf("SPU.bx = %lg\n", SPU.bx);
                    printf("SPU.cx = %lg\n", SPU.cx);
                    printf("SPU.dx = %lg\n", SPU.dx);
                    printf("result = %lg\n", result);
                    StackClear(st);
                    SPU ={};


                    break;
            }
            case MUL:
            {
                    elem_t tempt1 = 0;
                    elem_t tempt2 = 0;

                    StackPop(st, &tempt1);
                    StackPop(st, &tempt2);

                    StackPush(st, tempt1 * tempt2);

                    break;
            }
            case RPUSH:
            {
                    int reg_id = 0;

                    fscanf(code, "%d", &reg_id);

                    switch(reg_id)
                    {
                        case 1:
                        {
                            StackPush(st, SPU.ax);
                            break;
                        }
                        case 2:
                        {
                            StackPush(st, SPU.bx);
                            break;
                        }
                        case 3:
                        {
                            StackPush(st, SPU.cx);
                            break;
                        }
                        case 4:
                        {
                            StackPush(st, SPU.dx);
                            break;
                        }
                        default:
                        {
                            return RPUSH_REG;
                        }
                    }
                    break;
            }
            case IN:
            {
                elem_t tempt = 0;

                printf("Enter the double: ");
                scanf("%lg", &tempt);

                //printf("tempt = %lg\n", tempt);

                StackPush(st, tempt);

                break;
            }
            case POP:
            {
                int reg_id = 0;

                //printf("\n<<<POP>>>\n");

                if (fscanf(code, "%d", &reg_id) == 0)
                {
                    printf("reg_id did not get\n");
                    return 1;
                }

                //printf("reg_id = %d\n", reg_id);

                switch(reg_id)
                {
                    case 1:
                    {
                        StackPop(st, &SPU.ax);
                        //printf("ax = %lg\n", SPU.ax);
                        break;
                    }
                    case 2:
                    {
                        StackPop(st, &SPU.bx);
                        //printf("bx = %lg\n", SPU.bx);
                        break;
                    }
                    case 3:
                    {
                        StackPop(st, &SPU.cx);
                        //printf("cx = %lg\n", SPU.cx);
                        break;
                    }
                    case 4:
                    {
                        StackPop(st, &SPU.dx);
                        //printf("dx = %lg\n", SPU.dx);
                        break;
                    }
                    default:
                    {
                        return SPU_POP_REG;
                    }
                }

                break;
            }
            default:
            {
                    printf("\n<<<UNEXPECTED EXIT>>>\n");

                    return UNKNOWN_COMMAND;
                    break;
            }
        }

        fscanf(code, "%d", &command);
    }

    StackDtor(st);
}
