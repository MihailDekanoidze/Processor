#include <stdio.h>
#include "../include/StrFunctions.h"

int mystrcmp(char* ptr1, char* ptr2)
{
    int i = 0;

    //printf("ptr1 = %s\t ptr2 = %s\n", ptr1, ptr2);

    while ((ptr1[i] != '\0') && (ptr2[i] != '\0') && (ptr1[i] == ptr2[i]))
    {
        i++;
    }

    return ptr1[i] - ptr2[i];
}

void print_str(char* str)
{
    int i = 0;

    printf("str = %s\n", str);

    while (str[i] != '\0')
    {
        printf("%c(%d) ", str[i], str[i]);
        i++;
    }

    printf("%c(%d)\n", str[i + 1], str[i + 1]);
}
