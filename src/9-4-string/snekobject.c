#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "bootlib.h"
#include "snekobject.h"

snek_object_t *new_snek_string(char *value) {
	snek_object_t *obj = (snek_object_t *)boot_malloc(sizeof(snek_object_t));
	if (obj == NULL) return NULL;

	size_t size = strlen(value);
	char *str = (char *)boot_malloc(sizeof(char) * size + 1);
	if (str == NULL) {
		boot_free(obj);
		return NULL;
	}

	strcpy(str, value);
	obj->kind = STRING;
	obj->data.v_string = str;
	return obj;
}

// don't touch below this line

snek_object_t *new_snek_integer(int value) {
	snek_object_t *obj = boot_malloc(sizeof(snek_object_t));
	if (obj == NULL) {
		return NULL;
	}

	obj->kind = INTEGER;
	obj->data.v_int = value;
	return obj;
}

snek_object_t *new_snek_float(float value) {
	snek_object_t *obj = boot_malloc(sizeof(snek_object_t));
	if (obj == NULL) {
		return NULL;
	}

	obj->kind = FLOAT;
	obj->data.v_float = value;
	return obj;
}
