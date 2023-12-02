#include <stdio.h>
#include <ctype.h>
#include "..\include\InputText.h"
#include "..\include\ProcessingText.h"
#include "..\include\Sorting.h"

int alpha(struct StringInfo* ptr, int i, int format)
{

    //printf("*(ptr->address + i) = %c\n", *(ptr->address + i));

    while ((!isalpha(*((char*)ptr->address + i))) && (*((char*)ptr->address + i) != '\0')) {
        //printf("*(ptr->address + i) = %c (%d)\n", *(ptr->address + i), *(ptr->address + i));
        i += format;
    }
    return i;
}

int mystrcmptoward(void* ptr1, void* ptr2)
{
    struct StringInfo* str1 = (struct StringInfo*) ptr1;
    //printf("str1 = %s\n", str1->address);
    struct StringInfo* str2 = (struct StringInfo*) ptr2;
    //printf("str2 = %s\n", str2->address);
    int format = 1;

    int i = 0;
    int j = 0;

    i = alpha(str1, i, format);
    j = alpha(str2, j, format);

    for (; (i < str1->size) && (j < str2->size); i += format, j+= format)
    {
        if (*(str1->address + i) != *(str2->address + j))
            return *(str1->address + i) - *(str2->address + j);
    }
    return *(str1->address + i) - *(str2->address + j);
}



