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
    
    text_info* chars_buffer         = text_info_ctor();
    text_info* command_lines        = NULL;   
    command_string_processing* CSP  = NULL;

    error = file_to_buffer(argv[1], chars_buffer);
    ERROR_CHECK(error, "Input abort: error code ")

    command_lines = text_info_ctor();
    error = lines(chars_buffer, command_lines);
    ERROR_CHECK(error, "Separation by lines abort: error code ")

    CSP = CSP_ctor(command_lines);      
    ERROR_CHECK(CSP->errors, "CSP create failed: error code ")                          

    CSP->errors = lines_to_bytecode(CSP);
    ERROR_CHECK(CSP->errors, "Code translation failed: error code ")

    error = byte_code_to_file(argv[2], CSP->byte_code);
    ERROR_CHECK(error, "File writing failed: error code ");

    PROGRAMM_FINISH;
}



