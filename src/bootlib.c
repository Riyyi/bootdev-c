#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "bootlib.h"

typedef struct Allocation {
	void* ptr;
	size_t size;
	bool freed;
	struct Allocation *next;
} Allocation;

static Allocation *allocations = NULL; // backwards linked list
static int allocated_count = 0;
static int reallocated_count = 0;
static int total_size = 0;

void *create_allocation(void *allocated, size_t size);
Allocation *find_allocation(void *ptr);

void *boot_malloc(size_t size)
{
	void *allocated = malloc(size);
	if (allocated == NULL) return NULL;

	return create_allocation(allocated, size);
}

void *boot_calloc (size_t num, size_t size)
{
	void *allocated = calloc(num, size);
	if (allocated == NULL) return NULL;

	return create_allocation(allocated, num * size);
}

void *boot_realloc(void* ptr, size_t size)
{
	if (ptr == NULL) return NULL;

	void *allocated = realloc(ptr, size);
	if (allocated == NULL) return NULL;

	reallocated_count++;

	Allocation *allocation = find_allocation(ptr);
	if (allocated == ptr) { // realloc resized the existing ptr's memory block
		allocation->size = size;
		total_size += size - allocation->size;
		return allocated;
	}
	allocation->freed = true;
	allocated_count--;
	total_size -= allocation->size;

	return create_allocation(allocated, size);
}

void boot_free (void *ptr)
{
	if (ptr == NULL) return;

	free(ptr);

	Allocation *allocation = find_allocation(ptr);
	allocation->freed = true;
	allocated_count--;
	total_size -= allocation->size;
}

// -----------------------------------------

bool boot_all_freed()
{
	return allocated_count == 0;
}

bool boot_is_freed(void *ptr)
{
	return find_allocation(ptr)->freed;
}

int boot_realloc_count()
{
	return reallocated_count;
}

int boot_alloc_size()
{
	return total_size;
}

// -----------------------------------------

void *create_allocation(void *allocated, size_t size)
{
	if (allocated == NULL) return NULL;

	total_size += size;

	Allocation *allocation = (Allocation *)malloc(sizeof(Allocation));
	if (allocation == NULL) return NULL;
	allocation->ptr = allocated;
	allocation->size = size;
	allocation->freed = false;
	allocation->next = allocations;
	allocations = allocation;

	allocated_count++;

	return allocated;
}

Allocation *find_allocation(void *ptr)
{
	if (allocations == NULL) return NULL;

	Allocation *current = allocations;
	while (true) {
		if (current == NULL) return NULL;
		if (current->ptr == ptr) return current;
		current = current->next;
	}

	return NULL;
}
