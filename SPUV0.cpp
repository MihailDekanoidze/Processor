#include <stdio.h>
#include <malloc.h>
#include "StackFunctions.h"
#include "AssemblerV3.h"
#define base_capacity 70


int main()
{
    FILE* code = fopen("AssemblerArrCode.txt", "r");

    //printf("code = %p\n", code);

    int i = 0;

    int command = code[i];

    struct Stack st = {};

    StackCtor(&st, base_capacity);

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

                    int tempt = code[i + 1];
					i++;

                    StackPush (&st, tempt);

                    //printf("tempt = %d\n", tempt);

                    break;
            }
            case ADD:
            {
                    //printf("case: ADD\n");

                    int tempt1 = 0;
                    int tempt2 = 0;

                    StackPop(&st, &tempt1);
                    StackPop(&st, &tempt2);
                    StackPush(&st, tempt1 + tempt2);

                    break;
            }
            case SUB:
            {
                    //printf("case: SUB\n");

                    int tempt1 = 0;
                    int tempt2 = 0;

                    StackPop(&st, &tempt1);
                    StackPop(&st, &tempt2);
                    StackPush(&st, tempt2 - tempt1);

                    break;
            }
            case DIV:
            {
                    //printf("case: DIV\n");

                    int tempt1 = 0;
                    int tempt2 = 0;

                    StackPop(&st, &tempt1);
                    StackPop(&st, &tempt2);
                    StackPush(&st, tempt2 / tempt1);

                    break;
            }
            case OUT:
            {
                    //printf("case: OUT\n");

                    int result = 0;
                    StackPop(&st, &result);
                    printf("result = %d\n", result);
                    StackClear(&st);

                    break;
            }
            default:
            {
                    printf("\n<<<UNEXPECTED EXIT>>>\n");

                    break;
            }
        }
		i++;
    }

    StackDtor(&st);
}
