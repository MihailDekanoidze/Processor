#ifndef PROCESSING_TEXT_H
#define PROCESSING_TEXT_H

#include "CommonIncludes.h"

struct StringInfo {
    char* address;
    size_t size;
};

size_t StringCount(char* buffer, size_t charread);
Errors lines(text_info* char_text, text_info* lines_text);
bool isstr(char* begin);
size_t CountSort(struct StringInfo* lines, size_t stringcount);
struct TextInfo Needsort (TextInfo);

#endif //PROCESSING_TEXT_H
