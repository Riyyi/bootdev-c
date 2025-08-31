#include <stdlib.h>
#include <string.h>

#include "exercise.h"

token_t** create_token_pointer_array(token_t* tokens, size_t count) {
	token_t** token_pointers = malloc(count * sizeof(token_t*));
	if (token_pointers == NULL) {
		exit(1);
	}

	for (size_t i = 0; i < count; ++i) {
		token_t *token_pointer = (token_t *)malloc(sizeof(token_t));
		token_pointers[i] = token_pointer;
		token_pointers[i]->literal = tokens[i].literal;
		token_pointers[i]->column = tokens[i].column;
		token_pointers[i]->line = tokens[i].line;
	}
	return token_pointers;
}
