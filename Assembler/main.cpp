#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "../include/AssemblerV3.h"
#include "../include/InputText.h"
#include "../include/ProcessingText.h"

int main(int argc, char** argv)
{
    Errors error = NO_ERROR;
    if (!argc)
    {
        printf("Files was not defined!\n");
        return 1;
    }
    
    text_info* chars_buffer = text_info_ctor();

    error = file_to_buffer(argv[1], chars_buffer);

    if (error)
    {
        text_info_dtor(chars_buffer);
        printf("Input abort: error code %d\n", error);
        return 2;
    }

    text_info* command_lines = text_info_ctor();
    error = lines(chars_buffer, command_lines);

    if (error)
    {
        text_info_dtor(chars_buffer);
        text_info_dtor(command_lines);
        printf("Separation by lines abort: error code %d\n", error);
        return 2;
    }

    command_string_processing* CSP = CSP_ctor(command_lines);                                
    if (CSP->errors)                                                         // TODO : define
    {
        printf("CSP create failed: error code %d\n", CSP->errors);
        PROGRAMM_FINISH;
        return 3;
    }

    CSP->errors = lines_to_bytecode(CSP);
    if(CSP->errors)
    {
        printf("Code translation failed: error code %d\n", CSP->errors);
        PROGRAMM_FINISH;
        return 4;
    }

    for (size_t i = 0; i < CSP->arr_code_size; i++)
    {
        printf("byte_code[%zu] = %d\n", i, ((int*)CSP->arr_code)[i]);
    }

    PROGRAMM_FINISH;
}



