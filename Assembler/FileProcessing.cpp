#include <stdio.h>
#include <malloc.h>
#include "../include/InputText.h"
#include "../include/ProcessingText.h"
#include "../include/AssemblerV3.h"
#include "../include/FileProcessing.h"

struct Buffers{
    struct TextInfo* buffer1;
    struct TextInfo* buffer2;
}

int FileProcessing(const char* Commands, Buffers* CommandLines)
{
    //printf("in  FileProcessing\n");
    FILE* source_code = fopen(Commands, "r");
    if (source_code == NULL)
    {
        return ASM_ERROR_OPEN_FILE;
    }

    struct TextInfo CommandInfo = {};

    //printf("before InputText\n");

    CommandInfo = InputText(CommandInfo, source_code);

    //printf("After InputText\n");

    fclose(source_code);

    struct TextInfo ArrLines = Lines(CommandInfo);

    free(CommandInfo.buffer);

    if (ArrLines.buffer == NULL)
    {
        printf("ArrLines ptr = NULL\n");
    }

    if (CommandLines == NULL)
    {
        printf("CommandLines  is NULL\n");
    }
    CommandLines->buffer = ArrLines.buffer;
    CommandLines->elemcount = ArrLines.elemcount;

    //printf("After CommandLines\n");


    return 0;
}