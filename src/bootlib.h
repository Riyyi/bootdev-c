#pragma once

#include <stdbool.h>
#include <stddef.h>

void *boot_malloc(size_t size);
void *boot_calloc (size_t num, size_t size);
void *boot_realloc(void* ptr, size_t size);
void boot_free (void *ptr);

// -----------------------------------------

bool boot_all_freed();
bool boot_is_freed(void *ptr);
int boot_realloc_count();
int boot_alloc_size();
