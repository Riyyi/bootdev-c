#include <stdlib.h>

#include "snekobject.h"

snek_object_t *new_snek_integer(int value) {
	snek_object_t *number = (snek_object_t *)malloc(sizeof(snek_object_t));
	if (number == NULL) return NULL;
	number->kind = INTEGER;
	number->data.v_int = value;
	return number;
}
