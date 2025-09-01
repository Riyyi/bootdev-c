#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "snekstack.h"

void stack_push(my_stack_t *stack, void *obj) {

	if (stack->count >= stack->capacity) {
		void **data = realloc(stack->data, sizeof(void *) * stack->capacity * 2);
		if (data == NULL) return;
		stack->data = data;
		stack->capacity *= 2;
	}

	stack->data[stack->count] = obj;
	stack->count++;
}

// don't touch below this line

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
