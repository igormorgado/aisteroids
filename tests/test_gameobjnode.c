#include "test_gameobjnode.h"

const double eps = 1e-2f;

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

/*
	gameobj__print(obj1);
	gameobj__print(obj2);
	gameobj__print(obj3);
	gameobj__print((struct gameobj *) ship1);
	printf("\n%s\n", gameobj__fmt(obj1));
	printf("%s\n", gameobj__fmt(obj2));
	printf("%s\n", gameobj__fmt(obj3));
	printf("%s\n", ship__fmt(ship1));
*/

void
test__gameobjnode_create_alloc_correctly(void)
{
	SETUP_GAMEOBJNODE_TEST;
	struct gameobjnode * node1 = gameobjnode__init(obj1);
	CU_ASSERT_PTR_NOT_NULL(node1);		// node1 was created
	node1 = gameobjnode__free(node1);
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_create_points_to_correct_object(void)
{
	SETUP_GAMEOBJNODE_TEST;
	struct gameobjnode * node1 = gameobjnode__init(obj1);
	CU_ASSERT_PTR_NOT_NULL(node1->obj);		// node1 has assigned a obj
	CU_ASSERT_PTR_EQUAL(node1->obj, obj1);		// node1 object is correctone
	CU_ASSERT_PTR_NULL(node1->next);		// list reference is NULL
	CU_ASSERT_PTR_NULL(node1->prev);
	node1 = gameobjnode__free(node1);
	TEARDOWN_GAMEOBJNODE_TEST;
}


/*
 * TODO:
 * Test if free works with a node without siblings, with prev sibling, with 
 * next sibling and with both siblings
 */
void
test__gameobjnode_free_dont_return_dangling_pointer(void)
{
	SETUP_GAMEOBJNODE_TEST;
	struct gameobjnode * node1 = gameobjnode__init(obj1);
	node1 = gameobjnode__free(node1);
	CU_ASSERT_PTR_NULL(node1);			// node1 has assigned a obj
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_after_null(void)
{
	SETUP_GAMEOBJNODE_TEST;
	struct gameobjnode * node1 = gameobjnode__init(obj1);

	gameobjnode__add_after(NULL, node1);		// |-- n1 --|
	CU_ASSERT_PTR_NULL(node1->next);
	CU_ASSERT_PTR_NULL(node1->prev);

	node1 = gameobjnode__free(node1);
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_after_last_newnode_next_points_null(void)
{
	SETUP_GAMEOBJNODE_TEST;
	struct gameobjnode * node1 = gameobjnode__init(obj1);
	struct gameobjnode * node2 = gameobjnode__init(obj2);

	gameobjnode__add_after(node1, node2);		// |-- n1 --|
	CU_ASSERT_PTR_NULL(node2->next);

	node1 = gameobjnode__free(node1);
	node1 = gameobjnode__free(node2);
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_after_newnode_prev_points_to_orgnode(void)
{
	SETUP_GAMEOBJNODE_TEST;
	struct gameobjnode * node1 = gameobjnode__init(obj1);
	struct gameobjnode * node2 = gameobjnode__init(obj2);
	struct gameobjnode * node3 = gameobjnode__init(obj3);

	gameobjnode__add_after(node1, node2);		// |-- n1 <--> n2 --|
	gameobjnode__add_after(node1, node3);		// |-- n1 <--> n3 <--> n2 --|
	CU_ASSERT_PTR_EQUAL(node3->prev, node1);

	node1 = gameobjnode__free(node1);
	node2 = gameobjnode__free(node2);
	node3 = gameobjnode__free(node3);
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_after_orgnode_next_points_newnode(void)
{
	SETUP_GAMEOBJNODE_TEST;
	struct gameobjnode * node1 = gameobjnode__init(obj1);
	struct gameobjnode * node2 = gameobjnode__init(obj2);
	struct gameobjnode * node3 = gameobjnode__init(obj3);

	gameobjnode__add_after(node1, node2);		// |-- n1 <--> n2 --|
	gameobjnode__add_after(node1, node3);		// |-- n1 <--> n3 <--> n2 --|
	CU_ASSERT_PTR_EQUAL(node1->next, node3);

	node1 = gameobjnode__free(node1);
	node2 = gameobjnode__free(node2);
	node3 = gameobjnode__free(node3);
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_after_newnode_next_points_orgnode_next(void)
{
	SETUP_GAMEOBJNODE_TEST;
	struct gameobjnode * node1 = gameobjnode__init(obj1);
	struct gameobjnode * node2 = gameobjnode__init(obj2);
	struct gameobjnode * node3 = gameobjnode__init(obj3);

	gameobjnode__add_after(node1, node2);		// |-- n1 <--> n2 --|
	gameobjnode__add_after(node1, node3);		// |-- n1 <--> n3 <--> n2 --|
	CU_ASSERT_PTR_EQUAL(node3->next, node2);

	node1 = gameobjnode__free(node1);
	node2 = gameobjnode__free(node2);
	node3 = gameobjnode__free(node3);
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_after_next_orgnode_prev_points_newnode(void)
{
	SETUP_GAMEOBJNODE_TEST;
	struct gameobjnode * node1 = gameobjnode__init(obj1);
	struct gameobjnode * node2 = gameobjnode__init(obj2);
	struct gameobjnode * node3 = gameobjnode__init(obj3);

	gameobjnode__add_after(node1, node2);		// |-- n1 <--> n2 --|
	gameobjnode__add_after(node1, node3);		// |-- n1 <--> n3 <--> n2 --|
	CU_ASSERT_PTR_EQUAL(node2->prev, node3);

	node1 = gameobjnode__free(node1);
	node2 = gameobjnode__free(node2);
	node3 = gameobjnode__free(node3);
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_before_null(void)
{
	SETUP_GAMEOBJNODE_TEST;
	struct gameobjnode * node1 = gameobjnode__init(obj1);

	gameobjnode__add_before(NULL, node1);		// |-- n2 <--> n1 --|
	CU_ASSERT_PTR_NULL(node1->next);
	CU_ASSERT_PTR_NULL(node1->prev);

	node1 = gameobjnode__free(node1);
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_before_first_newnode_prev_points_null(void)
{
	SETUP_GAMEOBJNODE_TEST;
	struct gameobjnode * node1 = gameobjnode__init(obj1);
	struct gameobjnode * node2 = gameobjnode__init(obj2);

	gameobjnode__add_before(node1, node2);		// |-- n2 <--> n1 --|
	CU_ASSERT_PTR_NULL(node2->prev);

	node1 = gameobjnode__free(node1);
	node2 = gameobjnode__free(node2);
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_before_newnode_next_points_to_orgnode(void)
{
	SETUP_GAMEOBJNODE_TEST;
	struct gameobjnode * node1 = gameobjnode__init(obj1);
	struct gameobjnode * node2 = gameobjnode__init(obj2);
	struct gameobjnode * node3 = gameobjnode__init(obj3);

	gameobjnode__add_before(node1, node2);		// |-- n2 <--> n1 --|
	gameobjnode__add_before(node1, node3);		// |-- n2 <--> n3 <--> n1 --|
	CU_ASSERT_PTR_EQUAL(node3->next, node1);

	node1 = gameobjnode__free(node1);
	node2 = gameobjnode__free(node2);
	node3 = gameobjnode__free(node3);
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_before_orgnode_prev_points_newnode(void)
{
	SETUP_GAMEOBJNODE_TEST;
	struct gameobjnode * node1 = gameobjnode__init(obj1);
	struct gameobjnode * node2 = gameobjnode__init(obj2);
	struct gameobjnode * node3 = gameobjnode__init(obj3);

	gameobjnode__add_before(node1, node2);		// |-- n2 <--> n1 --|
	gameobjnode__add_before(node1, node3);		// |-- n2 <--> n3 <--> n1 --|
	CU_ASSERT_PTR_EQUAL(node1->prev, node3);

	node1 = gameobjnode__free(node1);
	node2 = gameobjnode__free(node2);
	node3 = gameobjnode__free(node3);
	TEARDOWN_GAMEOBJNODE_TEST;
}

void
test__gameobjnode_add_before_newnode_prev_points_orgnode_prev(void)
{
	SETUP_GAMEOBJNODE_TEST;
	struct gameobjnode * node1 = gameobjnode__init(obj1);
	struct gameobjnode * node2 = gameobjnode__init(obj2);
	struct gameobjnode * node3 = gameobjnode__init(obj3);

	gameobjnode__add_before(node1, node2);		// |-- n2 <--> n1 --|
	gameobjnode__add_before(node1, node3);		// |-- n2 <--> n3 <--> n1 --|
	CU_ASSERT_PTR_EQUAL(node3->prev, node2);

	node1 = gameobjnode__free(node1);
	node2 = gameobjnode__free(node2);
	node3 = gameobjnode__free(node3);
	TEARDOWN_GAMEOBJNODE_TEST;
}


void
test__gameobjnode_add_before_prev_orgnode_next_points_newnode(void)
{
	SETUP_GAMEOBJNODE_TEST;
	struct gameobjnode * node1 = gameobjnode__init(obj1);
	struct gameobjnode * node2 = gameobjnode__init(obj2);
	struct gameobjnode * node3 = gameobjnode__init(obj3);

	gameobjnode__add_before(node1, node2);		// |-- n2 <--> n1 --|
	gameobjnode__add_before(node1, node3);		// |-- n2 <--> n3 <--> n1 --|
	CU_ASSERT_PTR_EQUAL(node2->next, node3);

	node1 = gameobjnode__free(node1);
	node2 = gameobjnode__free(node2);
	node3 = gameobjnode__free(node3);
	TEARDOWN_GAMEOBJNODE_TEST;
}

/*
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

// DELETE NODE
void
test__gameobjnode_(void)
{
	SETUP_GAMEOBJNODE_TEST;
	TEARDOWN_GAMEOBJNODE_TEST;
}

// WHAT ELSE?
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
		{"gameobjnode_create_alloc_correctly",				test__gameobjnode_create_alloc_correctly			},
		{"gameobjnode_create_points_correct_object",			test__gameobjnode_create_points_to_correct_object		},
		{"gameobjnode_free_dont_return_dangling_pointer",		test__gameobjnode_free_dont_return_dangling_pointer		},
		{"gameobjnode_add_after_null",					test__gameobjnode_add_after_null				},
		{"gameobjnode_add_after_last_newnode_next_points_null",		test__gameobjnode_add_after_last_newnode_next_points_null	},
		{"gameobjnode_add_after_newnode_prev_points_to_orgnode",	test__gameobjnode_add_after_newnode_prev_points_to_orgnode	},
		{"gameobjnode_add_after_orgnode_next_points_newnode",		test__gameobjnode_add_after_orgnode_next_points_newnode		},
		{"gameobjnode_add_after_newnode_next_points_orgnode_next",	test__gameobjnode_add_after_newnode_next_points_orgnode_next	},
		{"gameobjnode_add_after_next_orgnode_prev_points_newnode",	test__gameobjnode_add_after_next_orgnode_prev_points_newnode	},
		{"gameobjnode_add_before_null",					test__gameobjnode_add_before_null				},
		{"gameobjnode_add_before_first_newnode_prev_points_null",	test__gameobjnode_add_before_first_newnode_prev_points_null	},
		{"gameobjnode_add_before_newnode_next_points_to_orgnode",	test__gameobjnode_add_before_newnode_next_points_to_orgnode	},
		{"gameobjnode_add_before_orgnode_prev_points_newnode",		test__gameobjnode_add_before_orgnode_prev_points_newnode	},
		{"gameobjnode_add_before_newnode_prev_points_orgnode_prev",	test__gameobjnode_add_before_newnode_prev_points_orgnode_prev	},
		{"gameobjnode_add_before_prev_orgnode_next_points_newnode",	test__gameobjnode_add_before_prev_orgnode_next_points_newnode	},
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
