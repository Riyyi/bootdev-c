#include "../vendor/munit/munit.h"

// TJ seems to have added a bunch of macros to the default munit.h,
// implement those here

// -----------------------------------------
// Test suite macros

#define munit_case(NAME, FUNCNAME, BODY)                                   \
	static MunitResult FUNCNAME(const MunitParameter params[], void* data) \
	{                                                                      \
		(void)params;                                                      \
		(void)data;                                                        \
		BODY return MUNIT_OK;                                              \
	}

#define munit_test(NAME, FN) \
	{ NAME, FN, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

#define munit_null_test \
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

#define munit_suite(NAME, TESTS) \
	(MunitSuite) { NAME, TESTS, NULL, 1, MUNIT_SUITE_OPTION_NONE }

// -----------------------------------------
// Overwrite assertion macros, extended with "msg" parameter

#undef assert_int
#define assert_int(A, OP, B, MSG) \
	munit_assert_int(A, OP, B);

#undef assert_uint
#define assert_uint(A, OP, B, MSG) \
	munit_assert_uint(A, OP, B);

#undef assert_double
#define assert_double(A, OP, B, MSG) \
	munit_assert_double(A, OP, B);

#undef assert_string_equal
#define assert_string_equal(A, B, MSG) \
	munit_assert_string_equal(A, B);

#undef munit_assert_size
#define munit_assert_size(A, OP, B, MSG) \
	munit_assert_type(size_t, MUNIT_SIZE_MODIFIER "u", A, OP, B)

#undef munit_assert_uint8
#define munit_assert_uint8(A, OP, B, MSG) \
	munit_assert_type(munit_uint8_t, PRIu8, A, OP, B)
#undef munit_assert_uint16
#define munit_assert_uint16(A, OP, B, MSG) \
	munit_assert_type(munit_uint16_t, PRIu16, A, OP, B)
#undef munit_assert_uint32
#define munit_assert_uint32(A, OP, B, MSG) \
	munit_assert_type(munit_uint32_t, PRIu32, A, OP, B)
