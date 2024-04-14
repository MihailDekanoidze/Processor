#include <stdio.h>
#include <string.h>

#include "../include/CommonIncludes.h"


Errors file_to_buffer(const char* file_name, text_info* buffer, size_t elem_size)
{
    FILE* input_file = fopen(file_name, "rb");
    if(!input_file) return OPEN_FILE;

    Errors error = input_text(input_file, elem_size, buffer);

    return error;
}

Errors byte_code_to_file(const char* file_name, text_info* byte_code, size_t elem_size)
{
    FILE* output = fopen(file_name, "wb");

    if (!byte_code) return NULL_PTR;
    fwrite(byte_code->buffer, elem_size, byte_code->elemcount, output);
    fclose(output);

    return NO_ERROR;
}