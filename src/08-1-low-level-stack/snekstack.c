#include <stdlib.h>

#include "bootlib.h"
#include "snekstack.h"

my_stack_t *stack_new(size_t capacity)
{
	my_stack_t *stack = (my_stack_t *)boot_malloc(sizeof(my_stack_t));
	if (stack == NULL) return NULL;
	stack->count = 0;
	stack->capacity = capacity;
	stack->data = boot_malloc(sizeof(void*) * capacity);
	if (stack->data == NULL) {
		boot_free(stack);
		return NULL;
	}

	return stack;
}
