#include <stddef.h>

typedef struct Stack {
	size_t count;
	size_t capacity;
	void **data;
} my_stack_t; // NOTE: renamed due to std naming conflict on macOS

my_stack_t *stack_new(size_t capacity);
void stack_push(my_stack_t *stack, void *obj);
