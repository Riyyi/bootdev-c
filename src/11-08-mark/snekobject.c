#include "bootlib.h"
#include "snekobject.h"

void snek_object_free(snek_object_t *obj) {
	switch (obj->kind) {
		case INTEGER:
		case FLOAT:
			break;
		case STRING:
			boot_free(obj->data.v_string);
			break;
		case VECTOR3: {
			break;
		}
		case ARRAY: {
			boot_free(obj->data.v_array.elements);
			break;
		}
	}
	boot_free(obj);
}
