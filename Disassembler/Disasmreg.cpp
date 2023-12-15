#include <stdio.h>
#include "../include/Disasmreg.h"
#include "../include/DisassemblerV3.h"

int DisasmPutRegtoFile(FILE* disasm, int tempt)
{
    switch(tempt)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        {
            fprintf(disasm, "%cX\n", 'A' + tempt - 1);
            break;
        }
        default:
        {
            return DISASM_ERROR_PUSH_REG;
        }
    }
    return 0;
}