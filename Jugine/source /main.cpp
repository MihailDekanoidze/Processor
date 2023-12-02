#include <stdio.h>
#include <TXLib.h>
#include <malloc.h>

#include "..\include\InputText.h"
#include "..\include\ProcessingText.h"
#include "..\include\Sorting.h"


int main()
{
    FILE* fp = fopen("Onegin.txt", "r");

    if (fp == NULL)
    {
        printf("Could not open the file\n");
        return 1;
    }

    struct TextInfo text = {};

    text = InputText(text, fp);


    if (text.buffer == NULL)
    {
        printf("File read error\n");

        fclose(fp);

        return 1;
    }

    fclose(fp);


    struct TextInfo linesinfo = {};

    linesinfo = Lines(text);

    //struct StingInfo* lines = (struct StingInfo*) linesinfo.buffer;
    //int stringcount = linesinfo.elemcount;

    struct TextInfo needsortinfo = {};

    needsortinfo = Needsort(linesinfo);


    //struct StringInfo* needsort = (struct StringInfo*)needsortinfo.buffer;
    //int countsort = needsortinfo.elemcount;

    /*printcmp(&needsort[0], &needsort[1], 1);
    printcmp(&needsort[2], &needsort[2], 1);

    printcmp(&needsort[0], &needsort[1], -1);
    printcmp(&needsort[2], &needsort[2], -1);*/

    //printf("%s\n", ((StringInfo*)((char*)needsortinfo.buffer + 1 * sizeof(StringInfo)))->address);

    bubblesort((void*) needsortinfo.buffer, sizeof(StringInfo), needsortinfo.elemcount, mystrcmptoward);


    FILE* toward = fopen("OneginSortedToward.txt", "w");

    for (int i = 0; i < needsortinfo.elemcount; i++)
    {
        fprintf(toward, "%s\n", ((StringInfo*)((char*)needsortinfo.buffer + i * sizeof(StringInfo)))->address);
    }

    fclose(toward);

    bubblesort((void*) needsortinfo.buffer, sizeof(StringInfo), needsortinfo.elemcount, mystrcmpbackward);

    //selectionsort(needsort, countsort, format);

    FILE* backward = fopen("OneginSortedBackward.txt", "w");

    for (int i = 0; i < needsortinfo.elemcount; i++)
    {
        fprintf(backward, "%s\n", ((StringInfo*)((char*)needsortinfo.buffer + i * sizeof(StringInfo)))->address);
    }

    fclose(backward);
}
