#include "stack.h"

typedef struct VirtualMachine {
	my_stack_t *frames;
	my_stack_t *objects;
} vm_t;

vm_t *vm_new();
void vm_free(vm_t *vm);
