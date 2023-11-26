#include <stdio.h>
#include <malloc.h>
#include "..\..\Stack\Stack.h"

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

enum ERROR_DISASM
{
    OPEN_FILE = 3,
    PUSH_REG = 4,
    POP_REG = 5,
    RPUSH_REG = 6,
    SPU_POP_REG = 7,
    UNKNOWN_COMMAND = 8
};


int main()
{
    FILE* code = fopen("AssemblerArrCode.txt", "r");

    if (code == NULL)
    {
        return OPEN_FILE;
    }

    FILE* disasm = fopen("DISASMCODE.txt", "w");

    if (disasm  == NULL)
    {
        return OPEN_FILE;
    }

    int command = 0;

    fscanf(code, "%d", &command);

    while (command != HLT)
    {
    //printf("CMD: %d\n", command);
    //printf("in while\n");

    //printf("command = %d\n", command);

    switch (command)
    {
            case PUSH:
            {
                    fprintf(disasm, "PUSH ");

                    int tempt = 0;

                    fscanf(code, "%d", &tempt);
                    fprintf(disasm, "%d\n", tempt);

                    //printf("tempt = %d\n", tempt);

                    break;
            }
            case ADD:
            {
                    fprintf(disasm, "ADD\n");

                    break;
            }
            case SUB:
            {
                    fprintf(disasm, "SUB\n");

                    break;
            }
            case DIV:
            {
                    fprintf(disasm, "DIV\n");

                    break;
            }
           case MUL:
            {
                    fprintf(disasm, "MUL\n");

                    break;
            }
            case OUT:
            {
                    fprintf(disasm, "OUT\n");

                    break;
            }
			case IN:
            {
                    fprintf(disasm, "IN\n");

                    break;
            }
			case RPUSH:
            {
                    fprintf(disasm, "PUSH ");

                    int tempt = 0;

                    fscanf(code, "%d", &tempt);
                    switch(tempt)
					{
						case 1:
						{
							fprintf(disasm, "AX\n");
							break;
						}
						case 2:
						{
							fprintf(disasm, "BX\n");
							break;
						}
						case 3:
						{
							fprintf(disasm, "CX\n");
							break;
						}
						case 4:
						{
							fprintf(disasm, "DX\n");
							break;
						}
						default:
						{
							return 1;
						}
					}

                    //printf("tempt = %d\n", tempt);

                    break;
            }
			case POP:
            {
                    fprintf(disasm, "POP ");

                    int tempt = 0;

                    fscanf(code, "%d", &tempt);
                    switch(tempt)
					{
						case 1:
						{
							fprintf(disasm, "AX\n");
							break;
						}
						case 2:
						{
							fprintf(disasm, "BX\n");
							break;
						}
						case 3:
						{
							fprintf(disasm, "CX\n");
							break;
						}
						case 4:
						{
							fprintf(disasm, "DX\n");
							break;
						}
						default:
						{
							return 1;
						}
					}

                    //printf("tempt = %d\n", tempt);

                    break;
            }
            default:
            {
                    printf("\n<<<UNEXPECTED EXIT>>>\n");

                    break;
            }
    }

    fscanf(code, "%d", &command);
    }

    fprintf(disasm, "HLT\n");

    fclose(disasm);

    fclose(code);
}
