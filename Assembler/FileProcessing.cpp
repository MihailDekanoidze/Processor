#include <stdio.h>



#include "../include/CommonIncludes.h"
#include "../include/InputText.h"
#include "../include/ProcessingText.h"
#include "../include/AssemblerV3.h"



Errors file_to_buffer(const char* file_name, text_info* buffer)
{
    FILE* input_file = fopen(file_name, "rb");
    if(!input_file) return OPEN_FILE;    

    return (input_text(input_file, sizeof(char), buffer));
}

Errors byte_code_to_file(const char* file_name, text_info* byte_code)
{
    FILE* output = fopen(file_name, "wb");

    if (!byte_code) return NULL_PTR;
    fwrite(byte_code->buffer, sizeof(int), byte_code->elemcount, output);
    fclose(output);

    return NO_ERROR;
}