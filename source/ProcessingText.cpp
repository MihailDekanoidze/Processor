#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include "../include/ProcessingText.h"
#include "../include/InputText.h"

size_t StringCount(char* buffer, size_t charread)
{
    size_t stringcount = 0;

    for (size_t i = 0; i < charread; i++)
    {
        if ((buffer[i] == '\n') || (buffer[i] == '\0'))
            stringcount++;
    }

    //printf("stringcount = %d\n", stringcount);

    return stringcount;
}


struct TextInfo Lines(TextInfo text)
{
    struct TextInfo linesinfo = {};

    char* buffer = (char*)text.buffer;

    size_t charread = text.elemcount;

    size_t stringcount = StringCount(buffer, charread) + 1;

    printf("stringcount  = %zu\n", stringcount);

    struct StringInfo* lines = (struct StringInfo*) calloc(stringcount, sizeof(struct StringInfo));
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

    /*for (int i = 0; i < stringcount - 1; i++)
    {
        printf("lines[%d] = %s\n", i, lines[i].address);
    }*/


    linesinfo.buffer = (void*)lines;
    linesinfo.elemcount = stringcount;

    if (linesinfo.buffer == NULL)
    {
        printf("linesinfo.buffer = NULL\n");
    }

    return linesinfo;
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


struct TextInfo Needsort (TextInfo strings)
{
    struct TextInfo needsortinfo = {};

    size_t countsort = CountSort((StringInfo*)strings.buffer, strings.elemcount);
    size_t stringcount = strings.elemcount;
    struct StringInfo* lines = (StringInfo*)strings.buffer;
    struct StringInfo* needsort = (struct StringInfo*) calloc(countsort, sizeof(struct StringInfo));

    size_t strsort = 0;

    for (size_t i = 0; i < stringcount; i++)
    {
        if (isstr(lines[i].address))
        {
            needsort[strsort].address = lines[i].address;
            needsort[strsort].size = lines[i].size;
            strsort++;
        }
    }


    /*for (int i = 0; i < countsort; i++)
    {
        printf("address of {line[%d] = %s} is %p\n", i, needsort[i].address, needsort[i].address);
    }

    for (int i = 0; i < countsort; i++)
    {
        printf("needsort[%d] = %p\n", i, needsort[i].address);
    }*/

    needsortinfo.buffer = (void*)needsort;
    needsortinfo.elemcount = countsort;

    return needsortinfo;
}
