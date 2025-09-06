#include "bootlib.h"
#include "vm.h"
#include "stack.h"

void vm_free(vm_t *vm) {
	if (vm == NULL) return;

	for (int i = 0; i < vm->frames->count; i++) {
		frame_free(vm->frames->data[i]);
	}
	stack_free(vm->frames);

	for (int i = 0; i < vm->objects->count; i++) {
		snek_object_free(vm->objects->data[i]);
	}
	stack_free(vm->objects);

	boot_free(vm);
}

// don't touch below this line

vm_t *vm_new() {
	vm_t *vm = boot_malloc(sizeof(vm_t));
	if (vm == NULL) {
		return NULL;
	}

	vm->frames = stack_new(8);
	vm->objects = stack_new(8);
	return vm;
}

void vm_track_object(vm_t *vm, snek_object_t *obj) {
	stack_push(vm->objects, obj);
}

void vm_frame_push(vm_t *vm, frame_t *frame) {
	stack_push(vm->frames, frame);
}

frame_t *vm_new_frame(vm_t *vm) {
	frame_t *frame = boot_malloc(sizeof(frame_t));
	frame->references = stack_new(8);

	vm_frame_push(vm, frame);
	return frame;
}

void frame_free(frame_t *frame) {
	stack_free(frame->references);
	boot_free(frame);
}
