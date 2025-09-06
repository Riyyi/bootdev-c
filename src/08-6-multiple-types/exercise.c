#include <stdlib.h>
#include <string.h>

#include "snekstack.h"

void stack_push_multiple_types(my_stack_t *s)
{
	float *pi = (float *)malloc(sizeof(float));
	if (pi == NULL) return;
	*pi = 3.14;

	stack_push(s, pi);

	const char *text = "Sneklang is blazingly slow!";
	char *str = (char *)malloc(sizeof(char) * strlen(text));
	if (str == NULL) return;
	strcpy(str, text);

	stack_push(s, str);
}
