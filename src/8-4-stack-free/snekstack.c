#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "snekstack.h"

void stack_free(my_stack_t *stack) {
	if (stack == NULL) return;

	if (stack->data != NULL) {
		free(stack->data);
		stack->data = NULL;
	}

	free(stack);
}

// don't touch below this line

void *stack_pop(my_stack_t *stack) {
	if (stack->count == 0) {
		return NULL;
	}

	stack->count--;
	return stack->data[stack->count];
}

void stack_push(my_stack_t *stack, void *obj) {
	if (stack->count == stack->capacity) {
		stack->capacity *= 2;
		void **temp = realloc(stack->data, stack->capacity * sizeof(void *));
		if (temp == NULL) {
			stack->capacity /= 2;
			exit(1);
		}
		stack->data = temp;
	}
	stack->data[stack->count] = obj;
	stack->count++;
	return;
}

my_stack_t *stack_new(size_t capacity) {
	my_stack_t *stack = malloc(sizeof(my_stack_t));
	if (stack == NULL) {
		return NULL;
	}

	stack->count = 0;
	stack->capacity = capacity;
	stack->data = malloc(stack->capacity * sizeof(void *));
	if (stack->data == NULL) {
		free(stack);
		return NULL;
	}

	return stack;
}
