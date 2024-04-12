#include <stdio.h>
#include <malloc.h>
#include "../include/DisassemblerV3.h"
#include "../include/Disasmreg.h"

int main()
{
    FILE* code = fopen("../Output/AssemblerArrCode", "rb");
        // use onegin, put both files to the buffer first!

    if (code == NULL)
    {
        return DISASM_ERROR_OPEN_FILE;
    }

    FILE* disasm = fopen("../Output/DISASMCODE.txt", "w");

    if (disasm  == NULL)
    {
        return DISASM_ERROR_OPEN_FILE;
    }

    size_t size_code = fsize(code) / sizeof(int);

    //printf("fsize: size_code = %zu\n", size_code);

    int* asm_code = (int*) calloc(size_code, sizeof(int));

    int fread_count = fread(asm_code, sizeof(int), size_code, code);

    if (!fread_count)
    {
        return DISASM_ERROE_BYTE_CODE;
    }

    size_t ip = 0;

    int command = 0;

    while (command != HLT) // do while()
    {
    //printf("CMD: %d\n", command);
    //printf("in while\n");

    int command = 0;

    for (size_t ip = 0; ip < size_code; ip++)
    {
        command = asm_code[ip];

        command = asm_code[ip];

        switch (command)
        {
            case COMMENT:
            {
                break;
            }
            case JMP_COMMAND:
            {
                fprintf(disasm, "%s ", jmp); 

                int tempt = asm_code[++ip];
                
                fprintf(disasm, "%d\n", tempt);

                break;
            }
            case JA_COMMAND:
            {
                fprintf(disasm, "%s ", ja); 

                int tempt = asm_code[++ip];

                fprintf(disasm, "%d\n", tempt);

                break;
            }
            case JB_COMMAND:
            {
                fprintf(disasm, "%s ", jb); 

                int tempt = asm_code[++ip];

                fprintf(disasm, "%d\n", tempt);

                break;
            }
            case JE_COMMAND:
            {
                fprintf(disasm, "%s ", je); 

                int tempt = asm_code[++ip];

                fprintf(disasm, "%d\n", tempt);

                break;
            }
            case JNA_COMMAND:
            {
                fprintf(disasm, "%s ", jna);

                int tempt = asm_code[++ip];
                
                fprintf(disasm, "%d\n", tempt);

                break;
            }
            case JNB_COMMAND:
            {
                fprintf(disasm, "%s ", jnb); 

                int tempt = asm_code[++ip];
                
                fprintf(disasm, "%d\n", tempt);

                break;
            }
            case JNE_COMMAND:   
            {
                fprintf(disasm, "%s ", jne); 

                int tempt = asm_code[++ip];
                
                fprintf(disasm, "%d\n", tempt);

                break;
            }         
            case PUSH:
            {
                fprintf(disasm, "%s ", push); 

                int tempt = asm_code[++ip];
                
                fprintf(disasm, "%d\n", tempt);

                break;
            }
            case ADD: fprintf(disasm, "ADD\n"); break;
            case SUB: fprintf(disasm, "SUB\n"); break;
            case DIV: fprintf(disasm, "DIV\n"); break;
            case MUL: fprintf(disasm, "MUL\n"); break;
            case OUT: fprintf(disasm, "OUT\n"); break;
			case IN:  fprintf(disasm, "IN\n");  break;
            case HLT:  fprintf(disasm, "HLT\n");  break;
            case RPUSH:
            {
                    fprintf(disasm, "%s ", push);

                    int tempt = asm_code[++ip];
                
                    // функцию
                    if (DisasmPutRegtoFile(disasm, tempt) != 0)
                    {
                        return DISASM_ERROR_RPUSH_REG;
                    }

                    break;
            }
			case POP:
            {
                    fprintf(disasm, "%s ", pop);

                    int tempt = asm_code[++ip];
                
                    if (DisasmPutRegtoFile(disasm, tempt) != 0)
                    {
                        return DISASM_ERROR_RPUSH_REG;
                    }

                    break;
            }
            default:
            {
                    printf("Command is %d\n", command);
                    printf("\n<<<UNEXPECTED EXIT>>>\n");

                    return DISASM_ERROR_UNKNOWN_COMMAND;

                    break;
            }
        }
        ip++;
    }

    fclose(disasm);

    fclose(code);
}