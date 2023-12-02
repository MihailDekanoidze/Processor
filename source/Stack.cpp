#include <stdio.h>
#include <malloc.h>
#include "../include/Stack.h"


void StackPrint(struct Stack *st)
{
    printf("\n\nInformation of stack\n");
    printf("Capacity of stack = %zu\n", st->capacity);
    printf("Size of stack = %zu\n", st->size);
    printf("Address of struct stack = %p\n", st);
    printf("Address of stack data = %p\n", st->ptr);

    switch (st->error)
    {
        case OUT_OF_MEMORY:
        {
                printf("Out of memory\n");
                break;
        }
        case EMPTY_STACK:
        {
                printf("Attempt to delete element in empty stack\n");
                break;
        }
        case NO_ERRORS:
        {
            printf("No errors\n");
            break;
        }
        default:
        {
                printf("Unexpected error\n");
                break;
        }
    }
    if (st->size == 0)
        printf("Empty stack");
    for (size_t i = 0; i < st->size; i++)
    {
        printf("st[%zu] = %d\n", i, st->ptr[i]);
    }

    printf("\n\n");
}

void StackCtor(struct Stack* st, const size_t capacity) // return enum / -1
{
    st->ptr = (elem_t*) calloc(capacity, sizeof (st->ptr[0])); // calloc != NULL
    st->size = 0;
    st->capacity = capacity;
}

void StackPush(struct Stack* st, const elem_t elem)
{
    if (st->capacity == st->size)
    {
        elem_t* tempt_address = (elem_t*) realloc(st->ptr, st->capacity * 2 * sizeof(elem_t)); //
        if (tempt_address == NULL)
        {
            st->error = OUT_OF_MEMORY;

            return;
        }
        st->ptr = tempt_address;
        st->capacity *= 2;
    }

    st->ptr[st->size++] = elem;
}

void StackPop(struct Stack* st, elem_t* value)
{
    //printf("In StackPop!\n");
    if (st->size == 0)
    {
        st->error = EMPTY_STACK;
        return;
    }
    //printf("st->size = %zu\n", st->size);
    st->ptr[st->size] = 0;

    *value = st->ptr[--st->size];


    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    /*if (st->size + 1 < st->capacity / 2)
    {
        elem_t* temp_address = (elem_t*)realloc(st->ptr, st->capacity / 2 * sizeof(elem_t));
        if (temp_address == NULL)
        {
            st->error = OUT_OF_MEMORY;

            return;
        }
        st->ptr = temp_address;
        st->capacity /= 2;
    }*/

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void StackDtor(struct Stack* st)
{
    StackClear(st);
    st->capacity = 0;
    st->error = NO_ERRORS;
    free(st->ptr);
    st->size = 0;

}

size_t StackSize(struct Stack* st)
{
    return st->size;
}

elem_t StackGet(struct Stack* st)
{
    if (!StackIsEmpty(st))
        return st->ptr[st->size -1];
    else
        return 0;
}

int StackIsEmpty(struct Stack* st)
{
    if (st->size == 0)
        return 0;
    else
        return 1;
}

void StackClear(struct Stack* st)
{
    for (size_t i = 0; i < st->size; i++)
    {
        st->ptr[i] = 0;
    }
    st->size = 0;
}
