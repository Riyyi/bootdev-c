void swap_strings(char **a, char **b) {
	if (a == b) return;

	char *tmp = *a;
	*a = *b;
	*b = tmp;
}
