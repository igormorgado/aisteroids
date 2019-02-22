#include <stdlib.h>
#include <time.h>
#include "test_gameobjlist.h"

const double eps = 1e-2f;

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

void
test__gameobjlist_init_creates_an_empty_list(void)
{
	struct gameobjlist * list1 = gameobjlist__init();
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 0);
	CU_ASSERT_PTR_NULL(list1->head);
	CU_ASSERT_PTR_NULL(list1->tail);
	list1 = gameobjlist__free(list1);
}

void
test__gameobjlist_free_clear_the_list(void)
{
	struct gameobjlist * list1 = gameobjlist__init();
	list1 = gameobjlist__free(list1);
	CU_ASSERT_PTR_NULL(list1);
}

void
test__gameobjlist_push_head_points_head_correctly(void)
{
	SETUP_GAMEOBJLIST_TEST;
	
	struct gameobjlist * list1 = gameobjlist__init();
	gameobjlist__push_head(list1, obj1);
	CU_ASSERT_PTR_EQUAL(list1->head->obj, obj1);
	CU_ASSERT_PTR_NULL(list1->head->next);
	CU_ASSERT_PTR_NULL(list1->head->prev);

	list1 = gameobjlist__free(list1);

	TEARDOWN_GAMEOBJLIST_TEST;
}

void
test__gameobjlist_push_head_keeps_next_prev_references_correct(void)
{
	SETUP_GAMEOBJLIST_TEST;
	
	struct gameobjlist * list1 = gameobjlist__init();

	gameobjlist__push_head(list1, obj1);

	CU_ASSERT_PTR_EQUAL(list1->head->obj, obj1);
	CU_ASSERT_PTR_NULL(list1->head->next);
	CU_ASSERT_PTR_NULL(list1->head->prev);

	gameobjlist__push_head(list1, obj2);
	CU_ASSERT_PTR_EQUAL(list1->head->obj, obj2);
	CU_ASSERT_PTR_NULL(list1->head->prev);
	CU_ASSERT_PTR_EQUAL(list1->head->next->obj, obj1);
	CU_ASSERT_PTR_NULL(list1->head->next->next);
	CU_ASSERT_PTR_EQUAL(list1->head->next->prev->obj, obj2);
	CU_ASSERT_PTR_EQUAL(list1->head->next->prev, list1->head);
	list1 = gameobjlist__free(list1);

	TEARDOWN_GAMEOBJLIST_TEST;

}
void
test__gameobjlist_count_increases_pushing_head(void)
{
	SETUP_GAMEOBJLIST_TEST;

	struct gameobjlist * list1 = gameobjlist__init();

	gameobjlist__push_head(list1, obj1);
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 1);

	gameobjlist__push_head(list1, obj2);
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 2);

	gameobjlist__push_head(list1, obj3);
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 3);

	gameobjlist__push_head(list1,(struct gameobj *) ship1);
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 4);

	list1 = gameobjlist__free(list1);
	TEARDOWN_GAMEOBJLIST_TEST;
}

void
test__gameobjlist_pop_head_returns_pushed_head(void)
{
	SETUP_GAMEOBJLIST_TEST;

	struct gameobjlist * list1 = gameobjlist__init();

	struct gameobj * pobj;
	
	// One
	gameobjlist__push_head(list1, obj1);
	pobj = gameobjlist__pop_head(list1);
	CU_ASSERT_PTR_EQUAL(obj1, pobj);
	CU_ASSERT_PTR_NOT_NULL(pobj);

	// Two
	gameobjlist__push_head(list1, obj1);
	gameobjlist__push_head(list1, obj2);
	pobj = gameobjlist__pop_head(list1);
	CU_ASSERT_PTR_EQUAL(obj2, pobj);
	CU_ASSERT_PTR_NOT_NULL(pobj);

	// Three
	gameobjlist__push_head(list1, obj1);
	gameobjlist__push_head(list1, obj2);
	gameobjlist__push_head(list1, (struct gameobj *) ship1);
	pobj = gameobjlist__pop_head(list1);
	CU_ASSERT_PTR_EQUAL(ship1, pobj);
	CU_ASSERT_PTR_NOT_NULL(pobj);

	// Three to one
	gameobjlist__push_head(list1, obj1);
	gameobjlist__push_head(list1, obj2);
	gameobjlist__push_head(list1, (struct gameobj *) ship1);
	pobj = gameobjlist__pop_head(list1);
	pobj = gameobjlist__pop_head(list1);
	pobj = gameobjlist__pop_head(list1);
	CU_ASSERT_PTR_EQUAL(obj1, pobj);
	CU_ASSERT_PTR_NOT_NULL(obj1);
	CU_ASSERT_PTR_NOT_NULL(pobj);

	list1 = gameobjlist__free(list1);
	TEARDOWN_GAMEOBJLIST_TEST;
}

// void
// test__gameobjlist_count_increases_pushing_tail(void)
// {
// 
// }
// 
// 
// void
// test__gameobjlist_count_decreases_poping_head(void)
// {
// 
// }
// 
// void
// test__gameobjlist_count_decreases_poping_tail(void)
// {
// 
// }



int
main (void)
{
	srand(time(NULL));
	CU_TestInfo gameobjlist_tests[] = {
		{"gameobjlist_init_creates_an_empty_list", test__gameobjlist_init_creates_an_empty_list},
		{"gameobjlist_free_clear_the_list", test__gameobjlist_free_clear_the_list},
		{"gameobjlist_push_head_points_head_correctly", test__gameobjlist_push_head_points_head_correctly},
		{"gameobjlist_count_increases_pushing_head", test__gameobjlist_count_increases_pushing_head},
		{"gameobjlist_push_head_keeps_next_prev_references_correct", test__gameobjlist_push_head_keeps_next_prev_references_correct},
		{"gameobjlist_pop_head_returns_pushed_head", test__gameobjlist_pop_head_returns_pushed_head},
		CU_TEST_INFO_NULL,
	};

	CU_SuiteInfo main_suites[] = {
		{"gameobjlist_tests", init_suite, clean_suite, NULL, NULL, gameobjlist_tests},
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
