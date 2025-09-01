#define MUNIT_ENABLE_ASSERT_ALIASES
#include "../vendor/munit/munit.h"

// TJ seems to have added a bunch of macros to the default munit.h,
// implement those here

// -----------------------------------------
// Test suite macros

#define munit_case(NAME, FUNCNAME, ...)                                    \
	static MunitResult FUNCNAME(const MunitParameter params[], void* data) \
	{                                                                      \
		(void)params;                                                      \
		(void)data;                                                        \
		__VA_ARGS__                                                        \
		return MUNIT_OK;                                                   \
	}

#define munit_test(NAME, FN) \
	{ NAME, FN, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

#define munit_null_test \
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }

#define munit_suite(NAME, TESTS) \
	(MunitSuite) { NAME, TESTS, NULL, 1, MUNIT_SUITE_OPTION_NONE }

// -----------------------------------------
// Overwrite assertion macros, extended with "msg" parameter

#undef munit_assert_int
#define munit_assert_int(A, OP, B, MSG) \
	munit_assert_type(int, "d", A, OP, B)

#undef munit_assert_float
#define munit_assert_float(A, OP, B, MSG) \
	munit_assert_type(float, "f", A, OP, B)

#undef assert_int
#define assert_int(A, OP, B, MSG) \
	munit_assert_int(A, OP, B, MSG);

#undef assert_uint
#define assert_uint(A, OP, B, MSG) \
	munit_assert_uint(A, OP, B);

#undef assert_float
#define assert_float(A, OP, B, MSG) \
	munit_assert_float(A, OP, B, MSG);

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

// string

#undef munit_assert_string_equal
#define munit_assert_string_equal(A, B, MSG)                                     \
	do {                                                                         \
		const char* munit_tmp_a_ = (A);                                          \
		const char* munit_tmp_b_ = (B);                                          \
		if (MUNIT_UNLIKELY(strcmp(munit_tmp_a_, munit_tmp_b_) != 0)) {           \
			munit_errorf("assertion failed: string %s == %s (\"%s\" == \"%s\")", \
			             #A, #B, munit_tmp_a_, munit_tmp_b_);                    \
		}                                                                        \
		MUNIT_PUSH_DISABLE_MSVC_C4127_                                           \
	} while (0)

#undef assert_string_equal
#define assert_string_equal(A, B, MSG) munit_assert_string_equal(A, B, MSG)

// null

#undef munit_assert_null
#define munit_assert_null(PTR, MSG) \
	munit_assert_ptr(PTR, ==, NULL)

#undef munit_assert_not_null
#define munit_assert_not_null(PTR, MSG) \
	munit_assert_ptr(PTR, !=, NULL)

#undef assert_null
#define assert_null(PTR, MSG) munit_assert_null(PTR, MSG)

#undef assert_not_null
#define assert_not_null(PTR, MSG) munit_assert_not_null(PTR, MSG)

// ptr

#undef munit_assert_ptr_not_equal
#define munit_assert_ptr_not_equal(A, B, MSG) \
	munit_assert_ptr(A, !=, B)

#undef assert_ptr
#define assert_ptr(A, OP, B, MSG) munit_assert_ptr(A, OP, B)

#undef assert_ptr_null
#define assert_ptr_null(PTR, MSG) munit_assert_ptr_null(PTR)
// https://github.com/nemequ/munit/pull/73/files

#undef assert_ptr_not_null
#define assert_ptr_not_null(PTR, MSG) munit_assert_not_null(PTR, MSG)

#undef assert_ptr_equal
#define assert_ptr_equal(A, B, MSG) munit_assert_ptr_equal(A, B)

#undef assert_ptr_not_equal
#define assert_ptr_not_equal(A, B, MSG) munit_assert_ptr_not_equal(A, B, MSG)
