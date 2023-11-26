#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "StrFunctions.h"
#include "..\Onegin\InputText.h"
#include "..\Onegin\ProcessingText.h"
#define commandsize 4
#define push_size 4
#define add_size 3
#define div_size 3
#define sub_size 3
#define out_size 3
#define hlt_size 3
#define PUSH 1
#define ADD 2
#define SUB 3
#define DIV 4
#define OUT 5
#define HLT -1


int main()
{
    FILE* fp = fopen("Commands.txt", "r");

    struct TextInfo CommandInfo = {};

    CommandInfo = InputText(CommandInfo, fp);

    struct TextInfo CommandLines = {};

    CommandLines = Lines(CommandInfo);

    char push[] = "PUSH";
    char add[] = "ADD";
    char sub[] = "SUB";
    char div[] = "DIV";
    char out[] = "OUT";
    char hlt[] = "HLT";

    FILE* code = fopen("ASMCODE.txt", "w");

    int i = 0;

    char* line = ((StringInfo*)(CommandLines.buffer))[i].address;

    /*for (int i = 0; i < CommandLines.elemcount; i++)
    {
        printf("lines[%d] = %s\n", i, ((StringInfo*)(CommandLines.buffer))[i].address);
    }*/

    printf("\n");

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

            fprintf(code, "%d ", PUSH);
            sscanf(line + 4, "%d", &tempt);
            fprintf(code, "%d\n", tempt);

            //printf("tempt = %d\n", tempt);
        }
        else if (strncmp(line, add, add_size) == 0)
        {
            fprintf(code, "%d\n", ADD);
        }
        else if(strncmp(line, sub, sub_size) == 0)
        {
            fprintf(code, "%d\n", SUB);
        }
        else if(strncmp(line, div, div_size) == 0)
        {
            fprintf(code, "%d\n", DIV);
        }
        else if(strncmp(line, out, out_size) == 0)
        {
            fprintf(code, "%d\n", OUT);
        }
        else if(strncmp(line, hlt, hlt_size) == 0)
        {
            fprintf(code, "%d\n", HLT);
        }
    }

    fclose(fp);

    fclose(code);
}


