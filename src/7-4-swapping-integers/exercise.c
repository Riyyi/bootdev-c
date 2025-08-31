void swap_ints(int *a, int *b) {
	if (a == b) return;

	// Either:

	int tmp = *a;
	*a = *b;
	*b = tmp;

	// Or:

	// Below works, but is kind of a meme answer
	// *a ^= *b;
	// *b ^= *a;
	// *a ^= *b;
}
