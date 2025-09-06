#include "assert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bootlib.h"
#include "snekobject.h"

snek_object_t *_new_snek_object();

snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y, snek_object_t *z)
{
	if (x == NULL || y == NULL || z == NULL) return NULL;

	snek_object_t *obj = _new_snek_object();
	if (obj == NULL) {
		return NULL;
	}

	obj->kind = VECTOR3;
	obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};
	refcount_inc(x);
	refcount_inc(y);
	refcount_inc(z);
	return obj;
}

void refcount_free(snek_object_t *obj)
{
	switch (obj->kind) {
	case INTEGER:
	case FLOAT:
		break;
	case STRING:
		boot_free(obj->data.v_string);
		break;
	case VECTOR3: {
		refcount_dec(obj->data.v_vector3.x);
		refcount_dec(obj->data.v_vector3.y);
		refcount_dec(obj->data.v_vector3.z);
		break;
	}
	default:
		assert(false);
	}

	boot_free(obj);
}

// don't touch below this line

void refcount_inc(snek_object_t *obj) {
	if (obj == NULL) {
		return;
	}

	obj->refcount++;
	return;
}

void refcount_dec(snek_object_t *obj) {
	if (obj == NULL) {
		return;
	}
	obj->refcount--;
	if (obj->refcount == 0) {
		return refcount_free(obj);
	}
	return;
}

snek_object_t *_new_snek_object() {
	snek_object_t *obj = boot_calloc(1, sizeof(snek_object_t));
	if (obj == NULL) {
		return NULL;
	}

	obj->refcount = 1;

	return obj;
}

snek_object_t *new_snek_array(size_t size) {
	snek_object_t *obj = _new_snek_object();
	if (obj == NULL) {
		return NULL;
	}

	snek_object_t **elements = boot_calloc(size, sizeof(snek_object_t *));
	if (elements == NULL) {
		boot_free(obj);
		return NULL;
	}

	obj->kind = ARRAY;
	obj->data.v_array = (snek_array_t){.size = size, .elements = elements};

	return obj;
}

snek_object_t *new_snek_integer(int value) {
	snek_object_t *obj = _new_snek_object();
	if (obj == NULL) {
		return NULL;
	}

	obj->kind = INTEGER;
	obj->data.v_int = value;
	return obj;
}

snek_object_t *new_snek_float(float value) {
	snek_object_t *obj = _new_snek_object();
	if (obj == NULL) {
		return NULL;
	}

	obj->kind = FLOAT;
	obj->data.v_float = value;
	return obj;
}

snek_object_t *new_snek_string(char *value) {
	snek_object_t *obj = _new_snek_object();
	if (obj == NULL) {
		return NULL;
	}

	int len = strlen(value);
	char *dst = boot_malloc(len + 1);
	if (dst == NULL) {
		boot_free(obj);
		return NULL;
	}

	strcpy(dst, value);

	obj->kind = STRING;
	obj->data.v_string = dst;
	return obj;
}
