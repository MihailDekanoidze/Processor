#include <stdio.h>
#include <malloc.h>

#include "../include/CommonIncludes.h"
#include "../include/DisassemblerV3.h"

int main(int argc, char** argv)
{
    Errors error = NO_ERROR;
    if (argc != 3) error = NO_DEFINED_FILE;

    ERROR_CHECK(error, "Files was not defined ", );

    text_info* byte_code = text_info_ctor();
    main_info* disasm    = NULL;

    error = file_to_buffer(argv[1], byte_code, sizeof(int));
    ERROR_CHECK(error, "Input abort: error code ", DISASM_PROGRAMM_FINISH);

    disasm = main_info_ctor(byte_code);
    if (!disasm) error = NULL_PTR;
    ERROR_CHECK(error, "Main_info disasm create failed: error code ", DISASM_PROGRAMM_FINISH);
    disasm->errors = byte_code_disasm(disasm);
    ERROR_CHECK(disasm->errors, "Main_info disasm create failed: error code ", DISASM_PROGRAMM_FINISH);

    error = byte_code_to_file(argv[2], disasm->disasm_code, sizeof(char));
    ERROR_CHECK(error, "File writing failed: error code ", DISASM_PROGRAMM_FINISH);
    
    DISASM_PROGRAMM_FINISH;
}