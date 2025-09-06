#include <stdlib.h>

#include "bootlib.h"
#include "munit.h"
#include "snekobject.h"

munit_case(RUN, test_create_empty_array, {
	snek_object_t *obj = new_snek_array(2);

	assert_int(obj->kind, ==, ARRAY, "Must set type to ARRAY");
	assert_int(obj->data.v_array.size, ==, 2, "Must set size to 2");

	boot_free(obj->data.v_array.elements);
	boot_free(obj);
	assert(boot_all_freed());
});

munit_case(SUBMIT, test_used_calloc, {
	snek_object_t *obj = new_snek_array(2);

	assert_ptr_null(obj->data.v_array.elements[0], "Should use calloc");
	assert_ptr_null(obj->data.v_array.elements[1], "Should use calloc");

	boot_free(obj->data.v_array.elements);
	boot_free(obj);
	assert(boot_all_freed());
});

int main() {
	MunitTest tests[] = {
		munit_test("/empty", test_create_empty_array),
		munit_test("/calloc", test_used_calloc),
		munit_null_test,
	};

	MunitSuite suite = munit_suite("object-array", tests);

	return munit_suite_main(&suite, NULL, 0, NULL);
}
