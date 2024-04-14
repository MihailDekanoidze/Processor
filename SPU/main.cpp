#include <stdio.h>
#include <malloc.h>
#include "../include/SPUV3.h"
#include "../include/Stack.h"


// #define SPU_DEBUG 1
int main(int argc, char** argv)
{   
    Errors error = NO_ERROR;
    ERROR_SPU SPU_error = SPU_NO_ERROR;
    if (argc != 2) error = NO_DEFINED_FILE;

    ERROR_CHECK(error, "Files was not defined ", );

    text_info* byte_code = text_info_ctor();
    processor* SPU    = (processor*)calloc(1, sizeof(processor));

    error = file_to_buffer(argv[1], byte_code, sizeof(int));
    ERROR_CHECK(error, "Input abort: error code ", SPU_PROGRAMM_FINISH);

    SPU_error = SPU_ctor(SPU, byte_code);
    ERROR_CHECK(SPU_error, "SPU struct create failed: error code ", SPU_PROGRAMM_FINISH);

    SPU->error = byte_code_execute(SPU);
    ERROR_CHECK(SPU->error, "Byte_code execute failed: error code ", SPU_PROGRAMM_FINISH);
    
    SPU_PROGRAMM_FINISH;
}
