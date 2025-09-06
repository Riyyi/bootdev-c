#include "bootlib.h"
#include "vm.h"

vm_t *vm_new() {
	vm_t * vm = (vm_t *)boot_malloc(sizeof(vm_t));
	if (vm == NULL) return NULL;

	vm->frames = stack_new(8);
	vm->objects = stack_new(8);
	return vm;
}

void vm_free(vm_t *vm) {
	if (vm == NULL) return;

	stack_free(vm->frames);
	stack_free(vm->objects);
	boot_free(vm);
}
