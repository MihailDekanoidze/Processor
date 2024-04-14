#include <stdio.h>
#include "../include/SPUV3.h"

#define DEBUG_OFF


ERROR_SPU SPU_ctor(processor* SPU, text_info* byte_code)
{
    SPU->byte_code = byte_code;

    Stack* SPU_data_stack = (Stack*)calloc(1, sizeof(Stack));

    StackError stk_error = StackCtor(SPU_data_stack, base_capacity); 
    ERROR_PUT(stk_error, SPU->error, SPU_DATA_STACK_ERROR, SPU_DATA_STACK_ERROR);
    FILE* data_stk_log      = fopen("./logs/Data_Stack_log.txt", "w");
    ERROR_PUT(!data_stk_log, SPU->error, SPU_ERROR_OPEN_FILE, SPU_ERROR_OPEN_FILE);
    SPU_data_stack ->stack_log = data_stk_log;
    SPU->data_stk = SPU_data_stack;

    Stack* SPU_return_stack = (Stack*)calloc(1, sizeof(Stack));

    stk_error = StackCtor(SPU_return_stack, base_capacity); 
    ERROR_PUT(stk_error, SPU->error, SPU_RETURN_STACK_ERROR, SPU_RETURN_STACK_ERROR);
    FILE* return_stk_log      = fopen("./logs/Return_Stack_log.txt", "w");
    ERROR_PUT(!data_stk_log, SPU->error, SPU_ERROR_OPEN_FILE, SPU_ERROR_OPEN_FILE);
    SPU_return_stack->stack_log = return_stk_log;
    SPU->return_stk = SPU_return_stack;

    SPU->ram = (int*)calloc(MEMORY_CAPACITY, sizeof(int));
    ERROR_PUT(!SPU->ram, SPU->error, SPU_CALLOC, SPU_CALLOC);

    SPU->regs = (int*)calloc(REGS_COUNT, sizeof(int));
    ERROR_PUT(!SPU->ram, SPU->error, SPU_CALLOC, SPU_CALLOC);

    FILE* SPU_log = fopen("./logs/SPU_log.txt", "w");
    ERROR_PUT(!SPU_log, SPU->error, SPU_ERROR_OPEN_FILE, SPU_ERROR_OPEN_FILE);
    SPU->SPU_log = SPU_log;

    SPU->error = SPU_NO_ERROR;

    return SPU_NO_ERROR;
}

void SPU_dtor(processor* SPU)
{
    if (!SPU) return;

    StackDtor(SPU->data_stk);
    StackDtor(SPU->return_stk);

    free(SPU->ram);
    free(SPU->regs);

    SPU->error =  SPU_NO_ERROR;
    free(SPU->data_stk);
    free(SPU->return_stk);
    free(SPU);
}

ERROR_SPU byte_code_execute(processor* SPU)
{
    SPU_LOG_FUNCTION_BEGIN;

    FILE* SPU_log               = SPU->SPU_log;
    int* byte_code              = (int*)SPU->byte_code->buffer;
    size_t byte_code_elemcount  = SPU->byte_code->elemcount;
    Stack* data_stk             = SPU->data_stk;
    Stack* return_stk           = SPU->return_stk;
    size_t ip                   = 0;
    int* regs                   = SPU->regs;
    int* ram                    = SPU->ram;     
    
    int curr_command = byte_code[ip];

    while (curr_command != END_PROGRAMM)
    {
        fprintf(SPU_log, "byte_code[%zu] = %d\n", ip, byte_code[ip]);

#ifdef  DEBUG_ON
        SPU_regs_print(SPU, byte_code, ip);     
        StackPrint(data_stk);
        printf("Mem[0] = %d\n", ram[0]);
        printf("St_top = %d\n", StackTop(data_stk));   
#endif

        switch (byte_code[ip])
        {
            #define ASM_COMMAND(name, id, size, dis, ...)                                                           \
            case id:                                                                                                \
            {                                                                                                       \
                __VA_ARGS__;                                                                                        \
            }                                                                                                                                                 
            #include "../include/Command_Description.txt"                  
            #undef ASM_COMMAND
            case EMPTY_COMMAND: 
            {
                ip++; 
                break;
            }
            default:
            {   
                printf("Unknown command = %d\n", byte_code[ip++]);
                ERROR_PUT(1, SPU->error, SPU_ERROR_UNKNOWN_COMMAND, SPU_ERROR_UNKNOWN_COMMAND);
            }
        }
    }

    SPU_LOG_FUNCTION_END;
    return SPU_NO_ERROR;
}


void SPU_regs_print(processor* SPU, int* byte_code, size_t ip)
{
    printf("in byte_code[%zu] = %d\n", ip, byte_code[ip]);

    for (size_t i = 0; i < REGS_COUNT; i++)
    printf("SPU %cX = %d\n", (char)('A' + (char)i), SPU->regs[i]);
}