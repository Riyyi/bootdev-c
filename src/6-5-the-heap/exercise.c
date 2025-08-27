#include "exercise.h"
#include <stdio.h>
#include <stdlib.h>

char* get_full_greeting(char* greeting, char* name, int size)
{
	char full_greeting[100];
	snprintf(full_greeting, 100, "%s %s", greeting, name);
	return full_greeting;
}
