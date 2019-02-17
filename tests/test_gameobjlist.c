#include "test_gameobjlist.h"

const double eps = 1e-2f;

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

void
test__gameobjlist_(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

int
main (void)
{
	CU_TestInfo gameobjlist_tests[] = {
		{ "gameobjlist_", test__gameobjlist_},
		CU_TEST_INFO_NULL,
	};

	CU_SuiteInfo main_suites[] = {
		{ "gameobjlist_tests", init_suite, clean_suite, NULL, NULL, gameobjlist_tests },
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
