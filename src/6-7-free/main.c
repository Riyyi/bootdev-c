#include <stdio.h>
#include <stdlib.h>
#include "exercise.h"

int main() {
	const int num_lists = 500;
	for (int i = 0; i < num_lists; i++) {
		int *lst = allocate_scalar_list(50000, 2);
		if (lst == NULL) {
			printf("Failed to allocate list\n");
			return 1;
		} else {
			// printf("Allocated list %d\n", i);
		}
		free(lst);
	}

	printf("Allocated %d lists\n", num_lists);

	return 0;
}
