#include <stdio.h>
#include "..\include\InputText.h"
#include "..\include\ProcessingText.h"
#include "..\include\Sorting.h"

void bubblesort(void* data, int elemsize, int length, int(*compare)(void* str1, void* str2))
{
    //printf("I am in bubblesort\n");
    for (int pass = 0; pass < length; pass++)
    {
        int nswaps = 0;
        for (int j = 0; j < length - 1; j++)
        {
            //printf("For str1 = %s and str2 = %s : \n", ((StringInfo*)data + j)->address, ((StringInfo*)data + j + 1)->address);
            //printf("compare(&(data[j]), &(data[j + 1]), format) = %d\n", compare((void*)((char*)data + j * elemsize), (void*)((char*)data + (j + 1) * elemsize), 1));

            //printf("Compare between: %s and %s\n", ((StringInfo*)((char*)data + j * elemsize))->address, ((StringInfo*)((char*)data + (j + 1) * elemsize))->address);

            if (compare((void*)((char*)data + j * elemsize), (void*)((char*)data + (j + 1) * elemsize)) > 0)
            {
                swap((void*) ((char*)data + j * elemsize), (void*) ((char*)data + (j + 1) * elemsize), elemsize);
                nswaps++;
            }
        }
        if (nswaps == 0)
            break;
    }
    //printf("I finished bubblesort\n");
}
