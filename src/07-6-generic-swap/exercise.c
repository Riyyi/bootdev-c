#include <stdlib.h>
#include <string.h>

#include "bootlib.h"

void swap(void *vp1, void *vp2, size_t size) {
	if (vp1 == vp2) return;

	void *tmp = boot_malloc(size);
	if (tmp == NULL) return;
	memcpy(tmp, vp1, size);
	memcpy(vp1, vp2, size);
	memcpy(vp2, tmp, size);
	boot_free(tmp);
}
