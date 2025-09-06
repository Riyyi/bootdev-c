#include "bootlib.h"
#include "vm.h"
#include "stack.h"

void trace(vm_t *vm) {
	if (vm == NULL) return;

	my_stack_t *gray_objects = stack_new(8);
	if (gray_objects == NULL) return;

	for (int i = 0; i < vm->objects->count; i++) {
		snek_object_t *obj = (snek_object_t *)vm->objects->data[i];
		if (obj->is_marked) {
			stack_push(gray_objects, obj);
		}
	}

	while (true) {
		snek_object_t *obj = (snek_object_t *)stack_pop(gray_objects);
		if ( obj == NULL) break;
		trace_blacken_object(gray_objects, obj);
	}
	stack_free(gray_objects);
}

void trace_blacken_object(my_stack_t *gray_objects, snek_object_t *obj) {
	if (gray_objects == NULL || obj == NULL) return;

	switch (obj->kind) {
		case INTEGER:
		case FLOAT:
		case STRING:
			break;
		case VECTOR3: {
			snek_vector_t vec = obj->data.v_vector3;
			trace_mark_object(gray_objects, vec.x);
			trace_mark_object(gray_objects, vec.y);
			trace_mark_object(gray_objects, vec.z);
			break;
		}
		case ARRAY: {
			snek_array_t arr = obj->data.v_array;
			for (int i = 0; i < arr.size; i++) {
				trace_mark_object(gray_objects, arr.elements[i]);
			}
			break;
		}
		default:
			break;
	};
}

void trace_mark_object(my_stack_t *gray_objects, snek_object_t *obj) {
	if (gray_objects == NULL || obj == NULL) return;
	if (obj->is_marked) return;

	obj->is_marked = true;
	stack_push(gray_objects, obj);
}

// don't touch below this line

void mark(vm_t *vm) {
	for (size_t i = 0; i < vm->frames->count; i++) {
		frame_t *frame = vm->frames->data[i];
		for (size_t j = 0; j < frame->references->count; j++) {
			snek_object_t *obj = frame->references->data[j];
			obj->is_marked = true;
		}
	}
}

void frame_reference_object(frame_t *frame, snek_object_t *obj) {
	stack_push(frame->references, obj);
}

vm_t *vm_new() {
	vm_t *vm = boot_malloc(sizeof(vm_t));
	if (vm == NULL) {
		return NULL;
	}

	vm->frames = stack_new(8);
	vm->objects = stack_new(8);
	return vm;
}

void vm_free(vm_t *vm) {
	// Free the stack frames, and then their container
	for (int i = 0; i < vm->frames->count; i++) {
		frame_free(vm->frames->data[i]);
	}
	stack_free(vm->frames);

	// Free the objects, and then their container
	for (int i = 0; i < vm->objects->count; i++) {
		snek_object_free(vm->objects->data[i]);
	}
	stack_free(vm->objects);

	boot_free(vm);
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

void vm_track_object(vm_t *vm, snek_object_t *obj) {
	stack_push(vm->objects, obj);
}
