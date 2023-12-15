#include <stdio.h>
#include "..\include\InputText.h"
#include "..\include\ProcessingText.h"
#include "..\include\Sorting.h"



int posmin(struct StringInfo* data, int begin, int length, int format)
{
    int posmin = begin;
    for (int i = begin; i < length; i++)
    {
        if (mystrcmp(&data[posmin], &data[i], format) > 0)
        {
            posmin = i;
        }
    }
    return posmin;
}

void selectionsort(struct StringInfo* data, int length, int format)
{
    for (int i = 0; i < length; i++)
    {
        int datamin = posmin(data, i, length, format);
        if (mystrcmp(&data[i], &data[datamin], format) > 0)
        {
            swap(&data[i], &data[datamin], sizeof(data[i]));
        }
    }
}
