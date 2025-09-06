#include <stdio.h>
#include <stdlib.h>

#include "munit.h"
#include "snekobject.h"

munit_case(RUN, correctly_free, {
	snek_object_t *first = new_snek_array(1);
	snek_object_t *second = new_snek_array(1);
	// refcounts: first = 1, second = 1
	snek_array_set(first, 0, second);
	// refcounts: first = 1, second = 2
	snek_array_set(second, 0, first);
	// refcounts: first = 2, second = 2
	refcount_dec(first);
	refcount_dec(second);
	assert_int(first->refcount, ==, 1, "Refcount first should be 1");
	assert_int(second->refcount, ==, 1, "Refcount second should be 1");
});

int main() {
	MunitTest tests[] = {
		munit_test("/correctly_free", correctly_free),
		munit_null_test,
	};

	MunitSuite suite = munit_suite("refcount", tests);

	return munit_suite_main(&suite, NULL, 0, NULL);
}
