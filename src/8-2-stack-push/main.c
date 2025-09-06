#include "bootlib.h"
#include "munit.h"
#include "snekstack.h"

munit_case(RUN, create_stack, {
	my_stack_t *s = stack_new(10);
	assert_int(s->capacity, ==, 10, "Sets capacity to 10");
	assert_int(s->count, ==, 0, "No elements in the stack yet");
	assert_ptr_not_null(s->data, "Allocates the stack data");

	// Clean up our allocated data.
	boot_free(s->data);
	boot_free(s);

	// Should be nothing left that is allocated.
	assert(boot_all_freed());
});

munit_case(RUN, push_stack, {
	my_stack_t *s = stack_new(2);
	assert_ptr_not_null(s, "Must allocate a new stack");

	assert_int(s->capacity, ==, 2, "Sets capacity to 2");
	assert_int(s->count, ==, 0, "No elements in the stack yet");
	assert_ptr_not_null(s->data, "Allocates the stack data");

	int a = 1;

	stack_push(s, &a);
	stack_push(s, &a);

	assert_int(s->capacity, ==, 2, "Sets capacity to 2");
	assert_int(s->count, ==, 2, "2 elements in the stack");
	assert_ptr_equal(s->data[0], &a, "element inserted into stack");

	// Clean up our allocated data.
	boot_free(s->data);
	boot_free(s);

	// Should be nothing left that is allocated.
	assert(boot_all_freed());
});

munit_case(SUBMIT, push_double_capacity, {
	my_stack_t *s = stack_new(2);
	assert_ptr_not_null(s, "Must allocate a new stack");

	assert_int(s->capacity, ==, 2, "Sets capacity to 2");
	assert_int(s->count, ==, 0, "No elements in the stack yet");
	assert_ptr_not_null(s->data, "Allocates the stack data");

	int a = 1;

	stack_push(s, &a);
	stack_push(s, &a);

	assert_int(s->capacity, ==, 2, "Sets capacity to 2");
	assert_int(s->count, ==, 2, "2 elements in the stack");

	stack_push(s, &a);
	assert_int(s->capacity, ==, 4, "Capacity is doubled");
	assert_int(s->count, ==, 3, "3 elements in the stack");

	// Should reallocate memory.
	assert_int_equal(boot_realloc_count(), 1, "Must reallocate memory for stack");

	// Clean up our allocated data.
	boot_free(s->data);
	boot_free(s);

	// Should be nothing left that is allocated.
	assert(boot_all_freed());
});



int main() {
	MunitTest tests[] = {
		munit_test("/create_stack", create_stack),
		munit_test("/push_stack", push_stack),
		munit_test("/push_double_capacity", push_double_capacity),
		munit_null_test,
	};

	MunitSuite suite = munit_suite("snekstack", tests);

	return munit_suite_main(&suite, NULL, 0, NULL);
}
