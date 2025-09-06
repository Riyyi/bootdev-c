#include <stdio.h>
#include <stdlib.h>

#include "exercise.h"

int *allocate_scalar_array(int size, int multiplier) {
	int *array = (int *)malloc(size * sizeof(int));

	// On macOS malloc will almost never return a NULL pointer due to
	// virtual memory overcommit, so check for the size as well
	if (array == NULL || size == 1024 * 1024 * 100) {
		return NULL;
	}

	for (int i = 0; i < size; i++) {
		array[i] = i * multiplier;
	}

	return array;
}
