#ifndef SPU_V3_H
#define SPU_V3_H

#include <stdio.h>
#include <malloc.h>
#include "Stack.h"
#include "InputText.h"
#include "CommonIncludes.h"

#define REGS_COUNT 4
#define MEMORY_CAPACITY 100
#define END_PROGRAMM    7
#define SPU_LOG_FUNCTION_BEGIN fprintf(SPU->SPU_log, "Function %s begin\n", __PRETTY_FUNCTION__);
#define SPU_LOG_FUNCTION_END   fprintf(SPU->SPU_log, "Function %s end\n",   __PRETTY_FUNCTION__);

const int base_capacity = 5; 
typedef int elem_t;

//binary file 


struct processor            //array reg
{   
    text_info*      byte_code;
    Stack*          data_stk;
    Stack*          return_stk;
    int*            regs;
    int*            ram;
    int             error;
    FILE*           SPU_log;
};      



enum ERROR_SPU 
{
    SPU_NO_ERROR                    = 0,
    SPU_ERROR_OPEN_FILE             = 1,
    SPU_ERROR_PUSH_REG              = 2,
    SPU_ERROR_POP_REG               = 3,
    SPU_ERROR_RPUSH_REG             = 4,
    SPU_ERROR_SPU_POP_REG           = 5,
    SPU_ERROR_UNKNOWN_COMMAND       = 6,
    SPU_ERROR_BYTE_CODE             = 7,
    SPU_EMPTY_ARG                   = 8,
    SPU_STACK_CALLOC                = 9,
    SPU_DATA_STACK_ERROR            = 10,
    SPU_RETURN_STACK_ERROR          = 11,
    SPU_CALLOC                      = 12,
    SPU_ERROR_JMP_IP                = 13,
    SPU_ERROR_MEMORY_ACCESS         = 14
};


#define SPU_PROGRAMM_FINISH             \
        text_info_dtor(byte_code);      \
        SPU_dtor(SPU);               


ERROR_SPU       SPU_ctor(processor* SPU, text_info* byte_code);
void            SPU_dtor(processor*);
ERROR_SPU       byte_code_execute(processor*);
void            SPU_regs_print(const processor* SPU);
void            SPU_info_printf(const processor* SPU);
void            SPU_ram_print(const processor* SPU, const size_t memory_count);
#endif //SPU_V3_H