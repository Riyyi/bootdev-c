#include "snekstack.h"
#include "stdlib.h"

void scary_double_push(my_stack_t *s) {
	stack_push(s, (void *)1337);
	int *number = malloc(sizeof(int));
	if (number == NULL) return;
	*number = 1024;
	stack_push(s, number);
}
