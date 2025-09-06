#pragma once
#include <stddef.h>
#include <stdlib.h>

typedef struct Stack {
	size_t count;
	size_t capacity;
	void **data;
} my_stack_t;

my_stack_t *stack_new(size_t capacity);

void stack_push(my_stack_t *stack, void *obj);
void *stack_pop(my_stack_t *stack);

void stack_free(my_stack_t *stack);
void stack_remove_nulls(my_stack_t *stack);
