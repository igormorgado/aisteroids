#include "test_gameobj.h"

const double eps = 1e-2f;

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

void 
test__gameobj_create_initalization(void)
{
	SETUP_GAMEOBJ1_TEST;

	CU_ASSERT_DOUBLE_EQUAL(obj1->position.x, 1.1f, eps);
	CU_ASSERT_DOUBLE_EQUAL(obj1->angle, 3.0f, eps);
	CU_ASSERT_TRUE(obj1->active);

	TEARDOWN_GAMEOBJ1_TEST;
}

void
test__gameobj_free_returns_null(void)
{
	SETUP_GAMEOBJ1_TEST;
	TEARDOWN_GAMEOBJ1_TEST;

	CU_ASSERT_PTR_NULL(obj1)
}

void
test__gameobj_zero_is_zero(void)
{
	SETUP_GAMEOBJ1_TEST;

	gameobj__zero(obj1);
	CU_ASSERT_EQUAL(obj1->usecnt, 0);
	CU_ASSERT_DOUBLE_EQUAL(obj1->size, 0.0f, eps);
	CU_ASSERT_DOUBLE_EQUAL(obj1->angle, 0.0f, eps);
	CU_ASSERT_DOUBLE_EQUAL(obj1->ang_velocity, 0.0f, eps);
	CU_ASSERT_DOUBLE_EQUAL(obj1->life_timer, 0.0f, eps);
	CU_ASSERT_EQUAL(obj1->type, 0);
	CU_ASSERT_EQUAL(obj1->obj_flags, OBJ_RESET);
	CU_ASSERT_FALSE(obj1->active);

	TEARDOWN_GAMEOBJ1_TEST;
}

void
test__gameobj_update_changes_velocity(void)
{
	SETUP_GAMEOBJ1_TEST;

	float dt = 1.0f;
	gameobj__update(obj1, dt);
	CU_ASSERT_DOUBLE_EQUAL(obj1->velocity.x, .5f, eps);
	CU_ASSERT_DOUBLE_EQUAL(obj1->velocity.y, .5f, eps);
	CU_ASSERT_DOUBLE_EQUAL(obj1->velocity.z, .5f, eps);

	TEARDOWN_GAMEOBJ1_TEST;
}

void
test__gameobj_update_changes_position(void)
{
	SETUP_GAMEOBJ1_TEST;

	float dt = 0.5f;
	gameobj__update(obj1, dt);
	CU_ASSERT_DOUBLE_EQUAL(obj1->position.x, 1.225f, eps);
	CU_ASSERT_DOUBLE_EQUAL(obj1->position.y, 2.224f, eps);
	CU_ASSERT_DOUBLE_EQUAL(obj1->position.z, 0.0f, eps);

	TEARDOWN_GAMEOBJ1_TEST;
}

void
test__gameobj_update_changes_rotation(void)
{
	SETUP_GAMEOBJ1_TEST;

	float dt = 1.0f;
	gameobj__update(obj1, dt);
	CU_ASSERT_DOUBLE_EQUAL(obj1->angle, 3.5f, eps);
	
	TEARDOWN_GAMEOBJ1_TEST;
}

void
test__gameobj_update_active_if_lifetime_positive(void)
{
	SETUP_GAMEOBJ1_TEST;

	float dt = 4.0f;
	CU_ASSERT_TRUE(obj1->active);
	gameobj__update(obj1, dt);
	CU_ASSERT_TRUE(obj1->active);

	TEARDOWN_GAMEOBJ1_TEST;
}

void
test__gameobj_update_deactive_if_lifetime_zero(void)
{
	SETUP_GAMEOBJ1_TEST;

	float dt = 5.0f;
	CU_ASSERT_TRUE(obj1->active);
	gameobj__update(obj1, dt);
	CU_ASSERT_FALSE(obj1->active);

	TEARDOWN_GAMEOBJ1_TEST;
}

void
test__gameobj_update_deactive_if_lifetime_negative(void)
{
	SETUP_GAMEOBJ1_TEST;

	float dt = 5.0f + eps;
	CU_ASSERT_TRUE(obj1->active);
	gameobj__update(obj1, dt);
	CU_ASSERT_FALSE(obj1->active);

	TEARDOWN_GAMEOBJ1_TEST;
}

void
test__gameobj_update_dont_change_time_if_notimer_set(void)
{
	SETUP_GAMEOBJ2_TEST;

	float dt = 1.0f;
	float life_timer = obj2->life_timer;
	gameobj__update(obj2, dt);
	CU_ASSERT_DOUBLE_EQUAL(obj2->life_timer, life_timer, eps);

	TEARDOWN_GAMEOBJ2_TEST;
}

int
main (void)
{
	CU_TestInfo gameobj_tests[] = {
		{ "gameobj__create_initialization", test__gameobj_create_initalization },
		{ "gameobj__free_returns_null", test__gameobj_free_returns_null },
		{ "gameobj__zero_is_zero", test__gameobj_zero_is_zero },
		{ "gameobj__update_changes_velocity", test__gameobj_update_changes_velocity },
		{ "gameobj__update_changes_position", test__gameobj_update_changes_position },
		{ "gameobj__update_changes_rotation", test__gameobj_update_changes_rotation },
		{ "gameobj__update_active_if_lifetime_positive", test__gameobj_update_active_if_lifetime_positive },
		{ "gameobj__update_deactive_if_lifetime_zero", test__gameobj_update_deactive_if_lifetime_zero },
		{ "gameobj__update_deactive_if_lifetime_negative", test__gameobj_update_deactive_if_lifetime_negative },
		{ "gameobj__update_dont_change_time_if_notimer_set", test__gameobj_update_dont_change_time_if_notimer_set},
		CU_TEST_INFO_NULL,
	};


	CU_SuiteInfo main_suites[] = {
		{ "gameobj_tests", init_suite, clean_suite, NULL, NULL, gameobj_tests },
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
