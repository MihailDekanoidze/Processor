#ifndef STACK_H
#define STACK_H

typedef int elem_t;

#define CAPACITY_REDUCE_LEVEL 50

enum ERROR
{
    NO_ERRORS = 0,

    OUT_OF_MEMORY = 1,

    EMPTY_STACK = 2
};


struct Stack  {
                    elem_t* ptr;
                    size_t size;
                    size_t capacity;
                    enum ERROR error;
                };


//int push(void* data, int capacity);

void StackPrint(struct Stack *st);

void StackCtor(struct Stack* st, const size_t capacity);

void StackPush(struct Stack* st, const elem_t elem);

void StackPop(struct Stack* st, elem_t* value);

void StackClear(struct Stack* st);

int StackIsEmpty(struct Stack* st);

elem_t StackGet(struct Stack* st);

size_t StackSize(struct Stack* st);

void StackDtor(struct Stack* st);

#endif // STACK_H
