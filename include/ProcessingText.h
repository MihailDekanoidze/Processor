#ifndef PROCESSING_TEXT_H
#define PROCESSING_TEXT_H

struct StringInfo {
    char* address;
    size_t size;
};

size_t StringCount(char* buffer, size_t charread);

struct TextInfo* Lines(TextInfo*);

bool isstr(char* begin);

size_t CountSort(struct StringInfo* lines, size_t stringcount);

struct TextInfo Needsort (TextInfo);

#endif //PROCESSING_TEXT_H
