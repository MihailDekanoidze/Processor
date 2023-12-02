#include <stdio.h>
#include <malloc.h>
#include "../include/DisassemblerV3.h"
#include "../include/Disasmreg.h"

int main()
{
    FILE* code/*file*/ = fopen("../Output/AssemblerArrCode.txt", "r");
        // use onegin, put both files to the buffer first!

    if (code == NULL)
    {
        return DISASM_ERROR_OPEN_FILE;
    }

    FILE* disasm = fopen("../Output/DISASMCODE.txt", "w");

    if (disasm  == NULL)
    {
        //fclose(code); 89872139226 - тел если проблемы с кодом 
        return DISASM_ERROR_OPEN_FILE;
    }

    int command = 0; // -100 

    if (fscanf(code, "%d", &command) != 1)
    {
        return DISASM_ERROE_BYTE_CODE;
    }

    while (command != HLT) // do while()
    {
    //printf("CMD: %d\n", command);
    //printf("in while\n");

    //printf("command = %d\n", command);

        switch (command)
        {
            case JMP_COMMAND:
            {
                fprintf(disasm, "JMP "); // add "PUSH" as constant to common.h

                int tempt = 0;

                if (fscanf(code, "%d", &tempt) != 1)
                {
                    return DISASM_ERROE_BYTE_CODE;
                }
                fprintf(disasm, "%d\n", tempt);

                //printf("tempt = %d\n", tempt);

                break;
            }
            case JA_COMMAND:
            {
                fprintf(disasm, "JA "); // add "PUSH" as constant to common.h

                int tempt = 0;

                if (fscanf(code, "%d", &tempt) != 1)
                {
                    return DISASM_ERROE_BYTE_CODE;
                }
                fprintf(disasm, "%d\n", tempt);

                //printf("tempt = %d\n", tempt);

                break;
            }
            case JB_COMMAND:
            {
                fprintf(disasm, "JB "); // add "PUSH" as constant to common.h

                int tempt = 0;

                if (fscanf(code, "%d", &tempt) != 1)
                {
                    return DISASM_ERROE_BYTE_CODE;
                }
                fprintf(disasm, "%d\n", tempt);

                //printf("tempt = %d\n", tempt);

                break;
            }
            case JE_COMMAND:
            {
                fprintf(disasm, "JE "); // add "PUSH" as constant to common.h

                int tempt = 0;

                if (fscanf(code, "%d", &tempt) != 1)
                {
                    return DISASM_ERROE_BYTE_CODE;
                }
                fprintf(disasm, "%d\n", tempt);

                //printf("tempt = %d\n", tempt);

                break;
            }
            case JNA_COMMAND:
            {
                fprintf(disasm, "JNA "); // add "PUSH" as constant to common.h

                int tempt = 0;

                if (fscanf(code, "%d", &tempt) != 1)
                {
                    return DISASM_ERROE_BYTE_CODE;
                }
                fprintf(disasm, "%d\n", tempt);

                //printf("tempt = %d\n", tempt);

                break;
            }
            case JNB_COMMAND:
            {
                fprintf(disasm, "JNB "); // add "PUSH" as constant to common.h

                int tempt = 0;

                if (fscanf(code, "%d", &tempt) != 1)
                {
                    return DISASM_ERROE_BYTE_CODE;
                }
                fprintf(disasm, "%d\n", tempt);

                //printf("tempt = %d\n", tempt);

                break;
            }
            case JNE_COMMAND:   
            {
                fprintf(disasm, "JNE "); // add "PUSH" as constant to common.h

                int tempt = 0;

                if (fscanf(code, "%d", &tempt) != 1)
                {
                    return DISASM_ERROE_BYTE_CODE;
                }
                fprintf(disasm, "%d\n", tempt);

                //printf("tempt = %d\n", tempt);

                break;
            }         
            case PUSH:
            {
                fprintf(disasm, "PUSH "); // add "PUSH" as constant to common.h

                int tempt = 0;

                if (fscanf(code, "%d", &tempt) != 1)
                {
                    return DISASM_ERROE_BYTE_CODE;
                }
                fprintf(disasm, "%d\n", tempt);

                //printf("tempt = %d\n", tempt);

                break;
            }
            case ADD: fprintf(disasm, "ADD\n"); break;
            case SUB: fprintf(disasm, "SUB\n"); break;
            case DIV: fprintf(disasm, "DIV\n"); break;
            case MUL: fprintf(disasm, "MUL\n"); break;
            case OUT: fprintf(disasm, "OUT\n"); break;
			case IN:  fprintf(disasm, "IN\n");  break;
            case RPUSH:
            {
                    fprintf(disasm, "PUSH ");

                    int tempt = 0;

                    if (fscanf(code, "%d", &tempt) != 1)
                    {
                        return DISASM_ERROE_BYTE_CODE;
                    }
                    // функцию
                    if (DisasmPutRegtoFile(disasm, tempt) != 0)
                    {
                        return DISASM_ERROR_RPUSH_REG;
                    }

                    //printf("tempt = %d\n", tempt);

                    break;
            }
			case POP:
            {
                    fprintf(disasm, "POP ");

                    int tempt = 0;

                    if (fscanf(code, "%d", &tempt) != 1)
                    {
                        return DISASM_ERROE_BYTE_CODE;
                    }
                    if (DisasmPutRegtoFile(disasm, tempt) != 0)
                    {
                        return DISASM_ERROR_RPUSH_REG;
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
        if (fscanf(code, "%d", &command) != 1)
        {
            return DISASM_ERROE_BYTE_CODE;
        }
    }

    fprintf(disasm, "HLT\n");

    fclose(disasm);

    fclose(code);
}