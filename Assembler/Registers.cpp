#include <stdio.h>
#include "../include/AssemblerV3.h"
#include "../include/Registers.h"


int asm_put_reg_to_buffer(int * arr_code, int reg_id)
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

int asm_get_reg_id(char registr)
{
    return registr - 'A' + 1;
}