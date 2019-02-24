#include <stdlib.h>
#include <time.h>
#include "test_gameobjlist.h"

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

void
test__gameobjlist_init_creates_an_empty_list(void)
{
	struct gameobjlist * list1 = gameobjlist__init();
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 0);
	CU_ASSERT_PTR_NULL(list1->front);
	CU_ASSERT_PTR_NULL(list1->back);
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
test__gameobjlist_push_front_points_front_correctly(void)
{
	SETUP_GAMEOBJLIST_TEST;
	
	struct gameobjlist * list1 = gameobjlist__init();
	gameobjlist__push_front(list1, obj1);
	CU_ASSERT_PTR_EQUAL(list1->front->obj, obj1);
	CU_ASSERT_PTR_NULL(list1->front->next);
	CU_ASSERT_PTR_NULL(list1->front->prev);

	list1 = gameobjlist__free(list1);

	TEARDOWN_GAMEOBJLIST_TEST;
}

void
test__gameobjlist_push_front_keeps_next_prev_references_correct(void)
{
	SETUP_GAMEOBJLIST_TEST;
	
	struct gameobjlist * list1 = gameobjlist__init();

	gameobjlist__push_front(list1, obj1);
	CU_ASSERT_PTR_EQUAL(list1->front->obj, obj1);
	CU_ASSERT_PTR_NULL(list1->front->next);
	CU_ASSERT_PTR_NULL(list1->front->prev);

	gameobjlist__push_front(list1, obj2);
	CU_ASSERT_PTR_EQUAL(list1->front->obj, obj2);
	CU_ASSERT_PTR_NULL(list1->front->prev);			// This should be always NULL
	CU_ASSERT_PTR_EQUAL(list1->front->next->obj, obj1);
	CU_ASSERT_PTR_NULL(list1->front->next->next);
	CU_ASSERT_PTR_EQUAL(list1->front->next->prev->obj, obj2);
	CU_ASSERT_PTR_EQUAL(list1->front->next->prev, list1->front);
	list1 = gameobjlist__free(list1);

	TEARDOWN_GAMEOBJLIST_TEST;

}

void
test__gameobjlist_count_increases_pushing_front(void)
{
	SETUP_GAMEOBJLIST_TEST;

	struct gameobjlist * list1 = gameobjlist__init();

	gameobjlist__push_front(list1, obj1);
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 1);

	gameobjlist__push_front(list1, obj2);
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 2);

	gameobjlist__push_front(list1, obj3);
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 3);

	gameobjlist__push_front(list1,(struct gameobj *) ship1);
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 4);

	list1 = gameobjlist__free(list1);
	TEARDOWN_GAMEOBJLIST_TEST;
}

void
test__gameobjlist_pop_front_last_element_makes_back_null(void)
{
	SETUP_GAMEOBJLIST_TEST;
	struct gameobjlist * list1 = gameobjlist__init();
	struct gameobj * pobj;

	gameobjlist__push_front(list1, obj1);
	pobj = gameobjlist__pop_front(list1);
	CU_ASSERT_PTR_EQUAL(obj1, pobj);
	CU_ASSERT_PTR_NOT_NULL(pobj);
	CU_ASSERT_PTR_NULL(list1->front);
	CU_ASSERT_PTR_NULL(list1->back);

	list1 = gameobjlist__free(list1);
	TEARDOWN_GAMEOBJLIST_TEST;
}

void
test__gameobjlist_pop_front_returns_pushed_front(void)
{
	SETUP_GAMEOBJLIST_TEST;

	struct gameobjlist * list1 = gameobjlist__init();

	struct gameobj * pobj;
	
	// One
	gameobjlist__push_front(list1, obj1);
	pobj = gameobjlist__pop_front(list1);
	CU_ASSERT_PTR_EQUAL(obj1, pobj);
	CU_ASSERT_PTR_NOT_NULL(pobj);

	// Two
	gameobjlist__push_front(list1, obj1);
	gameobjlist__push_front(list1, obj2);
	pobj = gameobjlist__pop_front(list1);
	CU_ASSERT_PTR_EQUAL(obj2, pobj);
	CU_ASSERT_PTR_NOT_NULL(pobj);

	// Three
	gameobjlist__push_front(list1, obj1);
	gameobjlist__push_front(list1, obj2);
	gameobjlist__push_front(list1, (struct gameobj *) ship1);
	pobj = gameobjlist__pop_front(list1);
	CU_ASSERT_PTR_EQUAL(ship1, pobj);
	CU_ASSERT_PTR_NOT_NULL(pobj);

	// Three to one
	gameobjlist__push_front(list1, obj1);
	gameobjlist__push_front(list1, obj2);
	gameobjlist__push_front(list1, (struct gameobj *) ship1);
	pobj = gameobjlist__pop_front(list1);
	pobj = gameobjlist__pop_front(list1);
	pobj = gameobjlist__pop_front(list1);
	CU_ASSERT_PTR_EQUAL(obj1, pobj);
	CU_ASSERT_PTR_NOT_NULL(obj1);
	CU_ASSERT_PTR_NOT_NULL(pobj);

	list1 = gameobjlist__free(list1);
	TEARDOWN_GAMEOBJLIST_TEST;
}

void
test__gameobjlist_pop_front_empty_list_returns_null(void)
{
	SETUP_GAMEOBJLIST_TEST;

	struct gameobjlist * list1 = gameobjlist__init();
	struct gameobj * pobj;
	
	gameobjlist__push_front(list1, obj1);
	pobj = gameobjlist__pop_front(list1);
	CU_ASSERT_PTR_NOT_NULL(pobj);
	pobj = gameobjlist__pop_front(list1);
	CU_ASSERT_PTR_NULL(pobj);
	pobj = gameobjlist__pop_front(list1);
	CU_ASSERT_PTR_NULL(pobj);

	list1 = gameobjlist__free(list1);
	TEARDOWN_GAMEOBJLIST_TEST;
}

void
test__gameobjlist_peek_front_returns_pushed_front(void)
{
	SETUP_GAMEOBJLIST_TEST;

	struct gameobjlist * list1 = gameobjlist__init();

	struct gameobj * pobj;
	
	// One
	gameobjlist__push_front(list1, obj1);
	pobj = gameobjlist__peek_front(list1);
	CU_ASSERT_PTR_EQUAL(obj1, pobj);
	CU_ASSERT_PTR_NOT_NULL(pobj);

	// Two
	gameobjlist__push_front(list1, obj2);
	pobj = gameobjlist__peek_front(list1);
	CU_ASSERT_PTR_EQUAL(obj2, pobj);
	CU_ASSERT_PTR_NOT_NULL(pobj);


	list1 = gameobjlist__free(list1);
	TEARDOWN_GAMEOBJLIST_TEST;
}

void
test__gameobjlist_peek_front_dont_change_list_size(void)
{
	SETUP_GAMEOBJLIST_TEST;

	struct gameobjlist * list1 = gameobjlist__init();
	struct gameobj * pobj;
	
	// One
	gameobjlist__push_front(list1, obj1);
	pobj = gameobjlist__peek_front(list1);
	CU_ASSERT_PTR_EQUAL(obj1, pobj);
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 1);

	// Two
	gameobjlist__push_front(list1, obj2);
	pobj = gameobjlist__peek_front(list1);
	CU_ASSERT_PTR_EQUAL(obj2, pobj);
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 2);

	list1 = gameobjlist__free(list1);
	TEARDOWN_GAMEOBJLIST_TEST;
}

void
test__gameobjlist_push_back_points_back_correctly(void)
{
	SETUP_GAMEOBJLIST_TEST;
	
	struct gameobjlist * list1 = gameobjlist__init();
	gameobjlist__push_back(list1, obj1);
	CU_ASSERT_PTR_EQUAL(list1->back->obj, obj1);
	CU_ASSERT_PTR_NULL(list1->back->next);
	CU_ASSERT_PTR_NULL(list1->back->prev);

	list1 = gameobjlist__free(list1);

	TEARDOWN_GAMEOBJLIST_TEST;
}

void
test__gameobjlist_push_back_keeps_prev_next_references_correct(void)
{
	SETUP_GAMEOBJLIST_TEST;
	
	struct gameobjlist * list1 = gameobjlist__init();

	gameobjlist__push_back(list1, obj1);
	CU_ASSERT_PTR_EQUAL(list1->back->obj, obj1);
	CU_ASSERT_PTR_NULL(list1->back->next);
	CU_ASSERT_PTR_NULL(list1->back->prev);

	gameobjlist__push_back(list1, obj2);
	CU_ASSERT_PTR_EQUAL(list1->back->obj, obj2);
	CU_ASSERT_PTR_NULL(list1->back->next);			// This should be always NULL
	CU_ASSERT_PTR_EQUAL(list1->back->prev->obj, obj1);
	CU_ASSERT_PTR_NULL(list1->back->prev->prev);
	CU_ASSERT_PTR_EQUAL(list1->back->prev->next->obj, obj2);
	CU_ASSERT_PTR_EQUAL(list1->back->prev->next, list1->back);

	list1 = gameobjlist__free(list1);

	TEARDOWN_GAMEOBJLIST_TEST;

}

void
test__gameobjlist_count_increases_pushing_back(void)
{
	SETUP_GAMEOBJLIST_TEST;

	struct gameobjlist * list1 = gameobjlist__init();

	gameobjlist__push_back(list1, obj1);
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 1);

	gameobjlist__push_back(list1, obj2);
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 2);

	gameobjlist__push_back(list1, obj3);
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 3);

	gameobjlist__push_back(list1,(struct gameobj *) ship1);
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 4);

	list1 = gameobjlist__free(list1);
	TEARDOWN_GAMEOBJLIST_TEST;
}

void
test__gameobjlist_pop_back_last_element_makes_front_null(void)
{
	SETUP_GAMEOBJLIST_TEST;
	struct gameobjlist * list1 = gameobjlist__init();
	struct gameobj * pobj;

	gameobjlist__push_back(list1, obj1);
	pobj = gameobjlist__pop_back(list1);
	CU_ASSERT_PTR_EQUAL(obj1, pobj);
	CU_ASSERT_PTR_NOT_NULL(pobj);
	CU_ASSERT_PTR_NULL(list1->back);
	CU_ASSERT_PTR_NULL(list1->front);

	list1 = gameobjlist__free(list1);
	TEARDOWN_GAMEOBJLIST_TEST;
}

void
test__gameobjlist_pop_back_returns_pushed_back(void)
{
	SETUP_GAMEOBJLIST_TEST;

	struct gameobjlist * list1 = gameobjlist__init();
	struct gameobj * pobj;
	
	gameobjlist__push_back(list1, obj1);

	pobj = gameobjlist__pop_back(list1);

	CU_ASSERT_PTR_EQUAL(obj1, pobj);
	CU_ASSERT_PTR_NOT_NULL(pobj);

	
	// Two
	gameobjlist__push_back(list1, obj1);
	gameobjlist__push_back(list1, obj2);
	pobj = gameobjlist__pop_back(list1);
	CU_ASSERT_PTR_EQUAL(obj2, pobj);
	CU_ASSERT_PTR_NOT_NULL(pobj);

	// Three
	gameobjlist__push_back(list1, obj1);
	gameobjlist__push_back(list1, obj2);
	gameobjlist__push_back(list1, (struct gameobj *) ship1);
	pobj = gameobjlist__pop_back(list1);
	CU_ASSERT_PTR_EQUAL(ship1, pobj);
	CU_ASSERT_PTR_NOT_NULL(pobj);

	// Three to one
	gameobjlist__push_back(list1, obj1);
	gameobjlist__push_back(list1, obj2);
	gameobjlist__push_back(list1, (struct gameobj *) ship1);
	pobj = gameobjlist__pop_back(list1);
	pobj = gameobjlist__pop_back(list1);
	pobj = gameobjlist__pop_back(list1);
	CU_ASSERT_PTR_EQUAL(obj1, pobj);
	CU_ASSERT_PTR_NOT_NULL(obj1);
	CU_ASSERT_PTR_NOT_NULL(pobj);

	list1 = gameobjlist__free(list1);
	TEARDOWN_GAMEOBJLIST_TEST;
}

void
test__gameobjlist_pop_back_empty_list_returns_null(void)
{
	SETUP_GAMEOBJLIST_TEST;

	struct gameobjlist * list1 = gameobjlist__init();
	struct gameobj * pobj;
	
	gameobjlist__push_back(list1, obj1);
	pobj = gameobjlist__pop_back(list1);
	CU_ASSERT_PTR_NOT_NULL(pobj);
	pobj = gameobjlist__pop_back(list1);
	CU_ASSERT_PTR_NULL(pobj);
	pobj = gameobjlist__pop_back(list1);
	CU_ASSERT_PTR_NULL(pobj);

	list1 = gameobjlist__free(list1);
	TEARDOWN_GAMEOBJLIST_TEST;
}

void
test__gameobjlist_peek_back_returns_pushed_back(void)
{
	SETUP_GAMEOBJLIST_TEST;

	struct gameobjlist * list1 = gameobjlist__init();

	struct gameobj * pobj;
	
	// One
	gameobjlist__push_back(list1, obj1);
	pobj = gameobjlist__peek_back(list1);
	CU_ASSERT_PTR_EQUAL(obj1, pobj);
	CU_ASSERT_PTR_NOT_NULL(pobj);

	// Two
	gameobjlist__push_back(list1, obj2);
	pobj = gameobjlist__peek_back(list1);
	CU_ASSERT_PTR_EQUAL(obj2, pobj);
	CU_ASSERT_PTR_NOT_NULL(pobj);


	list1 = gameobjlist__free(list1);
	TEARDOWN_GAMEOBJLIST_TEST;
}

void
test__gameobjlist_peek_back_dont_change_list_size(void)
{
	SETUP_GAMEOBJLIST_TEST;

	struct gameobjlist * list1 = gameobjlist__init();
	struct gameobj * pobj;
	
	// One
	gameobjlist__push_back(list1, obj1);
	pobj = gameobjlist__peek_back(list1);
	CU_ASSERT_PTR_EQUAL(obj1, pobj);
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 1);

	// Two
	gameobjlist__push_back(list1, obj2);
	pobj = gameobjlist__peek_back(list1);
	CU_ASSERT_PTR_EQUAL(obj2, pobj);
	CU_ASSERT_EQUAL(gameobjlist__size(list1), 2);

	list1 = gameobjlist__free(list1);
	TEARDOWN_GAMEOBJLIST_TEST;
}

int
main (void)
{
	srand(time(NULL));
	CU_TestInfo gameobjlist_tests[] = {
		{"gameobjlist_init_creates_an_empty_list", test__gameobjlist_init_creates_an_empty_list},
		{"gameobjlist_free_clear_the_list", test__gameobjlist_free_clear_the_list},
		{"gameobjlist_push_front_points_front_correctly", test__gameobjlist_push_front_points_front_correctly},
		{"gameobjlist_count_increases_pushing_front", test__gameobjlist_count_increases_pushing_front},
		{"gameobjlist_push_front_keeps_next_prev_references_correct", test__gameobjlist_push_front_keeps_next_prev_references_correct},
		{"gameobjlist_pop_front_returns_pushed_front", test__gameobjlist_pop_front_returns_pushed_front},
		{"gameobjlist_pop_front_last_element_makes_back_null", test__gameobjlist_pop_front_last_element_makes_back_null},
		{"gameobjlist_pop_front_empty_list_returns_null", test__gameobjlist_pop_front_empty_list_returns_null},
		{"gameobjlist_peek_front_returns_pushed_front", test__gameobjlist_peek_front_returns_pushed_front},
		{"gameobjlist_peek_front_dont_change_list_size", test__gameobjlist_peek_front_dont_change_list_size},
		{"gameobjlist_push_back_keeps_prev_next_references_correct", test__gameobjlist_push_back_keeps_prev_next_references_correct},
		{"gameobjlist_pop_back_last_element_makes_front_null", test__gameobjlist_pop_back_last_element_makes_front_null},
		{"gameobjlist_pop_back_returns_pushed_back", test__gameobjlist_pop_back_returns_pushed_back},
		{"gameobjlist_pop_back_empty_list_returns_null", test__gameobjlist_pop_back_empty_list_returns_null},
		{"gameobjlist_peek_back_returns_pushed_back", test__gameobjlist_peek_back_returns_pushed_back},
		{"gameobjlist_peek_back_dont_change_list_size", test__gameobjlist_peek_back_dont_change_list_size},
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
