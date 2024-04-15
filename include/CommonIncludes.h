#ifndef COMMON_INCLUDES_H
#define COMMON_INCLUDES_H

const int Num   = (1 << 8);
const int Reg   = (1 << 9);
const int Mem   = (1 << 10);
const int Frac  = (1 << 11);

#include "InputText.h"

#define INT_LEN  10
#define ACCURACY 2
#define EMPTY_COMMAND 0

#define ERROR_PUT(condition, dest, error, ret_val)                                      \
        if (condition)                                                                  \
        {                                                                               \
            printf("error in line %d, in fuction %s\n", __LINE__, __PRETTY_FUNCTION__); \
            dest = error;                                                               \
            return ret_val;                                                             \
        }while(0)                                           


#define ERROR_CHECK(error, messege, actions)    \
if (error)                                      \
{                                               \
    printf(messege);                            \
    int curr_error = error;                     \
    printf("%d\n", error);                      \
    actions;                                    \
    return curr_error;                          \
} while(0)



Errors file_to_buffer(const char* file_name, text_info* buffer, size_t elem_size);
Errors byte_code_to_file(const char* file_name, text_info* byte_code, size_t elem_size);


#endif //COMMON_INCLUDES_H


