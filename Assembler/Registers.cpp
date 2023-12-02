#include <stdio.h>
#include "../include/AssemblerV3.h"
#include "../include/Registers.h"


int AsmPutRegToBuffer(int * arr_code, int reg_id)
{
    switch(reg_id)
    {
        case 1:
        case 2:
        case 3:
        case 4:
            {
                *arr_code = reg_id;
                break;
            }
        default:
            {
                return ASM_ERROR_POP_REG;
            }
    }
    return 0;
}

int AsmGetRegId(char registr)
{
    return registr - 'A' + 1;
}