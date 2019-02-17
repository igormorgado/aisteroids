#include "test_gameobjnode.h"

const double eps = 1e-2f;

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

void
test__gameobjnode_create_alloc_correctly(void)
{
	SETUP_GAMEOBJNODE_TEST;
	// gameobj__print(obj1);
	// gameobj__print(obj2);
	// gameobj__print(obj3);
	// gameobj__print((struct gameobj *) ship1);
	// printf("\n%s\n", gameobj__fmt(obj1));
	// printf("%s\n", gameobj__fmt(obj2));
	// printf("%s\n", gameobj__fmt(obj3));
	// printf("%s\n", ship__fmt(ship1));
	TEARDOWN_GAMEOBJNODE_TEST;
}

/*
void
test__gameobjnode_create_points_to_correct_object(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_free_dont_return_dangling_pointer(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_first_is_first(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_last_is_last(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_next_returns_if_exist(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_next_returns_null_if_dont_exist(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_prev_returns_if_exist(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_prev_returns_null_if_dont_exist(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_next_by_key_match(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_next_by_key_is_null_if_dont_exist(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_next_by_objtype_match(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_next_by_objtype_is_null_if_dont_exist(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_next_by_objflag_match(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_next_by_objflag_is_null_if_dont_exist(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_after_points_correctly_to_prev(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_after_points_to_original_next(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_after_null_correctly_points_refs_to_null(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_before_points_correctly_to_next(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_before_points_to_original_prev(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_before_null_correctly_points_refs_to_null(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

// DELETE NODE
void
test__gameobjnode_(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}
*/

int
main (void)
{
	CU_TestInfo gameobjnode_tests[] = {
		{ "gameobjnode_create_alloc_correctly", test__gameobjnode_create_alloc_correctly},
		CU_TEST_INFO_NULL,
	};

	CU_SuiteInfo main_suites[] = {
		{ "gameobjnode_tests", init_suite, clean_suite, NULL, NULL, gameobjnode_tests },
		CU_SUITE_INFO_NULL,
	};

	if (CU_initialize_registry() != CUE_SUCCESS)
		return CU_get_error();

	CU_ErrorCode error = CU_register_suites(main_suites);
	if (error != CUE_SUCCESS)
	{
		fprintf(stderr, "Could not register suites. Error: %d\n", error);
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_basic_show_failures(CU_get_failure_list());

	CU_cleanup_registry();
	return CU_get_error();
}
