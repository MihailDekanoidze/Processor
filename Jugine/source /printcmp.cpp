#include <stdio.h>
#include "..\include\Sorting.h"

void printcmp(StringInfo* str1, StringInfo* str2, int format)
{
    int iscmp = 0;
    iscmp = mystrcmp(str1, str2, format);
    if (iscmp > 0)
    {
        printf("str1 = %s > str2 = %s\n", str1->address, str2->address);
    }
    else if (iscmp == 0)
    {
        printf("str1 = %s = str2 = %s\n", str1->address, str2->address);
    }
    else
    {
        printf("str1 = %s < str2 = %s\n", str1->address, str2->address);
    }
}
