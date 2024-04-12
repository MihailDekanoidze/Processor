#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include "../include/InputText.h"
#include "../include/ProcessingText.h"


size_t StringCount(char* buffer, size_t charread)
{
    size_t stringcount = 0;

    for (size_t i = 0; i < charread; i++)
    {
        if ((buffer[i] == '\n') || (buffer[i] == '\0'))
            stringcount++;
    }

    return stringcount;
}

Errors lines(text_info* char_text, text_info* lines_text)
{
    char* buffer = (char*)char_text->buffer;
    size_t charread = char_text->elemcount;
    size_t stringcount = StringCount(buffer, charread) + 1;

    struct StringInfo* lines = (struct StringInfo*) calloc(stringcount, sizeof(struct StringInfo));

    if (!lines) return CALLOC;

    size_t ptrlines = 1;
    size_t size = 0;
    lines[0].address = buffer;

    for (size_t i = 0; i < charread; i++)
    {
        if (buffer[i] == '\n')
        {
            lines[ptrlines].address = buffer + i + 1;
            lines[ptrlines - 1].size = i - size;
            buffer[i] = '\0';
            size = i;
            ptrlines++;
        }
    }

    /*for (int i = 0; i < stringcount; i++)
    {
        printf("lines[%d] = %p\n", i, lines[i].address);
    }*/

    /*for (int i = 0; i < stringcount; i++)
    {
        printf("lines[%d] = %s\n", i, lines[i].address);
    }*/


    lines_text->buffer = (void*)lines;
    lines_text->elemcount = stringcount;

    return NO_ERROR;
}

bool isstr(char* begin)
{
    int flag = 0;
    int i = 0;
    while (begin[i] != '\0')
    {
        if ((islower(begin[i])) || (isupper(begin[i])))
            flag = 1;
        i++;
    }
    if (flag)
        return true;
    else
        return false;
}

size_t CountSort(struct StringInfo* lines, size_t stringcount)
{
    size_t countsort = 0;

    for (size_t i = 0; i < stringcount; i++)
    {
        if (isstr(lines[i].address))
        {
            countsort++;
        }
    }

    return countsort;
}


