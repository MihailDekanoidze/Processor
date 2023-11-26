#include <stdio.h>
#include <malloc.h>
#include "..\..\Stack\Stack.h"
#include "..\include\StrFunctions.h"
#define commandsize 4


int main()
{
    FILE* fp = fopen("CommandInterpreter.txt", "r");

    struct Stack st = {};

    const size_t capacity = 10;

    //printf("capacity = %zu\n", capacity);

    StackCtor(&st, capacity);

    elem_t* ptr = st.ptr;

    char* buffer = (char*) calloc(commandsize, sizeof(char));

    char push[] = "PUSH";
    char add[] = "ADD";
    char sub[] = "SUB";
    char div[] = "DIV";
    char out[] = "OUT";
    char hlt[] = "HLT";

    while (mystrcmp(buffer, hlt) != 0)
    {
        //printf("in while\n");
        fscanf(fp, "%s", buffer);
        //printf("buffer = %s\n", buffer);
        if (mystrcmp(buffer, push) == 0)
        {
            int tempt = 0;
            fscanf(fp, "%d", &tempt);
            StackPush (&st, tempt);
            //printf("tempt = %d\n", tempt);
        }
        else if (mystrcmp(buffer, add) == 0)
        {
            int tempt1 = 0;
            int tempt2 = 0;

            StackPop(&st, &tempt1);
            StackPop(&st, &tempt2);
            StackPush(&st, tempt1 + tempt2);
        }
        else if(mystrcmp(buffer, sub) == 0)
        {
            int tempt1 = 0;
            int tempt2 = 0;

            StackPop(&st, &tempt1);
            StackPop(&st, &tempt2);
            StackPush(&st, tempt2 - tempt1);
        }
        else if(mystrcmp(buffer, div) == 0)
        {
            int tempt1 = 0;
            int tempt2 = 0;

            StackPop(&st, &tempt1);
            StackPop(&st, &tempt2);
            StackPush(&st, tempt2 / tempt1);
        }
        else if(mystrcmp(buffer, out) == 0)
        {
            int result = 0;
            StackPop(&st, &result);
            printf("result = %d\n", result);
            StackClear(&st);
        }
    }

    StackDtor(&st);

}
