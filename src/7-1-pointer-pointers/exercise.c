#include "stdlib.h"

#include "exercise.h"
void allocate_int(int **pointer_pointer, int value) {
	int *number = (int *)malloc(sizeof(int));
	*pointer_pointer = number;
	**pointer_pointer = value;
}
