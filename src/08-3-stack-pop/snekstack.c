#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "bootlib.h"
#include "snekstack.h"

void *stack_pop(my_stack_t *stack) {
	if (stack->count == 0) return NULL;
	stack->count--;
	return stack->data[stack->count];
}

// don't touch below this line'

void stack_push(my_stack_t *stack, void *obj) {
	if (stack->count == stack->capacity) {
		stack->capacity *= 2;
		void **temp = boot_realloc(stack->data, stack->capacity * sizeof(void *));
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
	my_stack_t *stack = boot_malloc(sizeof(my_stack_t));
	if (stack == NULL) {
		return NULL;
	}

	stack->count = 0;
	stack->capacity = capacity;
	stack->data = boot_malloc(stack->capacity * sizeof(void *));
	if (stack->data == NULL) {
		boot_free(stack);
		return NULL;
	}

	return stack;
}
