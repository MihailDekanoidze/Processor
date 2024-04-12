#ifndef SPU_V3_H
#define SPU_V3_H

#include <stdio.h>
#include <malloc.h>
#include "Stack.h"
#include "InputText.h"
#include "CommonIncludes.h"

#define REGS_COUNT 4


const int base_capacity = 5; 


typedef int elem_t;


struct byte_code_info
{
    text_info*  byte_code;
    ERROR_SPU   error;
};

//binary file 


struct Processor            //array reg
{
    Stack* data_stk;
    Stack* return_stk;
    int* regs;
    int* ram;
    int errors;
};



enum ERROR_SPU 
{
    SPU_NO_ERROR                    = 0,
    SPU_ERROR_OPEN_FILE             = 1,
    SPU_ERROR_PUSH_REG              = 2,
    SPU_ERROR_POP_REG               = 3,
    SPU_ERROR_RPUSH_REG             = 4,
    SPU_ERROR_SPU_POP_REG           = 5,
    SPU_ERROR_UNKNOWN_CURR_COMMAND  = 6,
    SPU_ERROR_BYTE_CODE             = 7,
    SPU_EMPTY_ARG                   = 8,
    SPU_DATA_STACK_ERROR            = 9,
    SPU_RETURN_STACK_ERROR          = 10
};


Processor*      SPU_ctor(void);
void            SPU_dtor(Processor*);
byte_code_info* byte_code_input(const char* file_name);
void            SPU_regs_print(const Processor* SPU);
void            SPU_info_printf(const Processor* SPU);
void            SPU_ram_print(const Processor* SPU, const size_t memory_count);
#endif //SPU_V3_H