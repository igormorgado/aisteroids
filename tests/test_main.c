#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/TestDB.h>
//#include <CUnit/Automated.h>

#include "debug.h"
#include "ship.h"
#include "test_main.h"
#include "mocks.h"
#include "gameobj.h"
#include "gameobjnode.h"
#include "gameobjlist.h"

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

/*
 * SHIP FUNCTIONS
 */
void 
test__ship_create_initalization(void)
{
	SETUP_SHIP1_TEST;

	CU_ASSERT_DOUBLE_EQUAL(ship1->base.position.x, 3.5f, eps);
	CU_ASSERT_DOUBLE_EQUAL(ship1->base.angle, 3.1f, eps);
	CU_ASSERT_TRUE(ship1->base.active);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_free_returns_null(void)
{
	SETUP_SHIP1_TEST;
	TEARDOWN_SHIP1_TEST;

	CU_ASSERT_PTR_NULL(ship1)
}

void
test__ship_update_changes_velocity(void)
{
	SETUP_SHIP1_TEST;

	float dt = 1.0f;
	ship__update(ship1, dt);
	CU_ASSERT_DOUBLE_EQUAL(ship1->base.velocity.x, 0.2f, eps);
	CU_ASSERT_DOUBLE_EQUAL(ship1->base.velocity.y, 0.2f, eps);
	CU_ASSERT_DOUBLE_EQUAL(ship1->base.velocity.z, 0.2f, eps);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_update_changes_position(void)
{
	SETUP_SHIP1_TEST;

	float dt = 1.0f;
	ship__update(ship1, dt);
	CU_ASSERT_DOUBLE_EQUAL(ship1->base.position.x, 3.70f, eps);
	CU_ASSERT_DOUBLE_EQUAL(ship1->base.position.y, 3.40f, eps);
	CU_ASSERT_DOUBLE_EQUAL(ship1->base.position.z, 0.0f, eps);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_update_changes_rotation(void)
{
	SETUP_SHIP1_TEST;

	float dt = 1;
	ship__update(ship1, dt);
	CU_ASSERT_DOUBLE_EQUAL(ship1->base.angle, 3.8f, eps);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_has_ship_flag(void)
{
	SETUP_SHIP1_TEST;

	CU_ASSERT_EQUAL(ship1->base.obj_flags & OBJ_SHIP, OBJ_SHIP);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_update_active_if_lifetime_positive(void)
{
	SETUP_SHIP1_TEST;

	float dt = 4;
	CU_ASSERT_TRUE(ship1->base.active);
	ship__update(ship1, dt);
	CU_ASSERT_TRUE(ship1->base.active);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_update_deactive_if_lifetime_zero(void)
{
	SETUP_SHIP1_TEST;

	float dt = 5.0f;
	CU_ASSERT_TRUE(ship1->base.active);
	ship__update(ship1, dt);
	CU_ASSERT_FALSE(ship1->base.active);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_update_deactive_if_lifetime_negative(void)
{
	SETUP_SHIP1_TEST;

	float dt = 5.0f + eps;
	CU_ASSERT_TRUE(ship1->base.active);
	ship__update(ship1, dt);
	CU_ASSERT_FALSE(ship1->base.active);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_thrust_works_as_expected(void)
{
	SETUP_SHIP1_TEST;

	CU_ASSERT_FALSE(ship1->thrust);
	CU_ASSERT_FALSE(ship1->rev_thrust);
	ship__thrust_on(ship1);
	CU_ASSERT_TRUE(ship1->thrust);
	CU_ASSERT_FALSE(ship1->rev_thrust);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_rev_thrust_works_as_expected(void)
{
	SETUP_SHIP1_TEST;

	CU_ASSERT_FALSE(ship1->thrust);
	CU_ASSERT_FALSE(ship1->rev_thrust);
	ship__thrust_reverse(ship1);
	CU_ASSERT_FALSE(ship1->thrust);
	CU_ASSERT_TRUE(ship1->rev_thrust);

	TEARDOWN_SHIP1_TEST;
}


void
test__ship_deactivate_thrust_works_as_expected(void)
{
	SETUP_SHIP1_TEST;

	ship__thrust_on(ship1);
	ship__thrust_off(ship1);
	CU_ASSERT_FALSE(ship1->thrust);
	CU_ASSERT_FALSE(ship1->rev_thrust);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_stop(void)
{
	SETUP_SHIP1_TEST;

	float dt = 1;
	ship__update(ship1, dt);
	ship__stop(ship1);
	ship__update(ship1, dt);
	CU_ASSERT_DOUBLE_EQUAL(ship1->base.velocity.x, 0.f, eps);
	CU_ASSERT_DOUBLE_EQUAL(ship1->base.velocity.y, 0.f, eps);
	CU_ASSERT_DOUBLE_EQUAL(ship1->base.velocity.z, 0.f, eps);
	CU_ASSERT_DOUBLE_EQUAL(ship1->base.acceleration, 0.f, eps);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_turn_stop(void)
{
	SETUP_SHIP1_TEST;

	float dt = 1;
	ship__update(ship1, dt);
	ship__turn_stop(ship1);
	ship__update(ship1, dt);
	CU_ASSERT_DOUBLE_EQUAL(ship1->base.ang_velocity, 0.f, eps);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_score_up(void)
{
	SETUP_SHIP1_TEST;

	CU_ASSERT_EQUAL(ship1->score, 0);
	ship__increment_score(ship1, 100);
	CU_ASSERT_EQUAL(ship1->score, 100);

	TEARDOWN_SHIP1_TEST;
}


void
test__ship_get_powerup(void)
{
	SETUP_SHIP1_TEST;

	CU_ASSERT_EQUAL(ship1->shot_power_level, 0);
	ship__get_powerup(ship1, 1);
	CU_ASSERT_EQUAL(ship1->shot_power_level, 1);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_get_shot_level(void)
{
	SETUP_SHIP1_TEST;

	ship1->shot_power_level = 1;
	CU_ASSERT_EQUAL(ship__get_shot_level(ship1), 1);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_inc_num_bullets(void)
{
	SETUP_SHIP1_TEST;

	CU_ASSERT_EQUAL(ship1->active_bullet_count, 2);
	ship__inc_num_bullets(ship1, 8);
	CU_ASSERT_EQUAL(ship1->active_bullet_count, 10);

	TEARDOWN_SHIP1_TEST;
}

void 
test__ship_get_num_bullets(void)
{
	SETUP_SHIP1_TEST;

	ship1->active_bullet_count = 10;
	CU_ASSERT_EQUAL(ship__get_num_bullets(ship1), 10);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_make_invincible(void)
{
	SETUP_SHIP1_TEST;

	ship__make_invincible(ship1, 10.0f);
	CU_ASSERT_DOUBLE_EQUAL(ship1->invincibility_timer, 10.f, eps);

	TEARDOWN_SHIP1_TEST;
}

void 
test__ship_reduce_invincible(void) 
{
	SETUP_SHIP1_TEST;

	float dt = 10.0f;
	ship__make_invincible(ship1, 11.0f);
	ship__update(ship1, dt);
	CU_ASSERT_DOUBLE_EQUAL(ship1->invincibility_timer, 1.0f, eps);

	TEARDOWN_SHIP1_TEST;
}

void 
test__ship_zero_invincible(void) 
{
	SETUP_SHIP1_TEST;

	float dt = 10.0f;
	ship__make_invincible(ship1, 10.0f);
	ship__update(ship1, dt);
	CU_ASSERT_DOUBLE_EQUAL(ship1->invincibility_timer, 0.0f, eps);

	TEARDOWN_SHIP1_TEST;
}

void 
test__ship_invincible_never_negative(void) 
{
	SETUP_SHIP1_TEST;

	float dt = 15.0f;
	ship__make_invincible(ship1, 10.0f);
	ship__update(ship1, dt);
	ship__update(ship1, dt);
	CU_ASSERT_DOUBLE_EQUAL(ship1->invincibility_timer, 0.0f, eps);
	ship__update(ship1, dt);
	CU_ASSERT_DOUBLE_EQUAL(ship1->invincibility_timer, 0.0f, eps);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_terminate_bullet(void) 
{
	SETUP_SHIP1_TEST;

	ship1->active_bullet_count = 10;
	ship__terminate_bullet(ship1);
	CU_ASSERT_EQUAL(ship__get_num_bullets(ship1), 9);

	TEARDOWN_SHIP1_TEST;
}

void
test__ship_terminate_bullet_never_negative(void) 
{
	SETUP_SHIP1_TEST;

	ship1->active_bullet_count = 1;
	ship__terminate_bullet(ship1);
	ship__terminate_bullet(ship1);
	CU_ASSERT_EQUAL(ship__get_num_bullets(ship1), 0);

	TEARDOWN_SHIP1_TEST;
}

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
		CU_TEST_INFO_NULL,
	};

	CU_TestInfo ship_tests[] = {
		{ "ship__create_initialization", test__ship_create_initalization },
		{ "ship__free_returns_null", test__ship_free_returns_null },
		{ "ship__update_changes_velocity", test__ship_update_changes_velocity}, 
		{ "ship__update_changes_position", test__ship_update_changes_position}, 
		{ "ship__update_changes_rotation", test__ship_update_changes_rotation}, 
		{ "ship__has_ship_flag", test__ship_has_ship_flag}, 
		{ "ship__update_active_if_lifetime_positive", test__ship_update_active_if_lifetime_positive}, 
		{ "ship__update_deactive_if_lifetime_zero", test__ship_update_deactive_if_lifetime_zero}, 
		{ "ship__update_deactive_if_lifetime_negative", test__ship_update_deactive_if_lifetime_negative}, 
		{ "ship__thrust_works_as_expected", test__ship_thrust_works_as_expected}, 
		{ "ship__rev_thrust_works_as_expected", test__ship_rev_thrust_works_as_expected}, 
		{ "ship__deactivate_thrust_works_as_expected", test__ship_deactivate_thrust_works_as_expected}, 
		{ "ship__stop", test__ship_stop}, 
		{ "ship__turn_stop", test__ship_turn_stop}, 
		{ "ship__score_up", test__ship_score_up}, 
		{ "ship__get_powerup", test__ship_get_powerup}, 
		{ "ship__get_shot_level", test__ship_get_shot_level}, 
		{ "ship__inc_num_bullets", test__ship_inc_num_bullets}, 
		{ "ship__get_num_bullets", test__ship_get_num_bullets}, 
		{ "ship__make_invincible", test__ship_make_invincible}, 
		{ "ship__reduce_invincible", test__ship_reduce_invincible}, 
		{ "ship__zero_invincible", test__ship_zero_invincible}, 
		{ "ship__invincible_never_negative", test__ship_invincible_never_negative}, 
		{ "ship__terminate_bullet", test__ship_terminate_bullet}, 
		{ "ship__terminate_bullet_never_negative", test__ship_terminate_bullet_never_negative},
		CU_TEST_INFO_NULL,
	};

	CU_TestInfo gameobjnode_tests[] = {
		{ "gameobjnode_create_alloc_correctly", test__gameobjnode_create_alloc_correctly},
		CU_TEST_INFO_NULL,
	};

	// CU_TestInfo gameobjlist_tests[] = {
	// };

	CU_SuiteInfo main_suites[] = {
		{ "gameobj_tests", init_suite, clean_suite, NULL, NULL, gameobj_tests },
		{ "ship_tests", init_suite, clean_suite, NULL, NULL, ship_tests },
		{ "gameobjnode_tests", init_suite, clean_suite, NULL, NULL, gameobjnode_tests },
		// { "gameobjlist_tests", init_suite, clean_suite, NULL, NULL, gameobjlist_tests }
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
//     
//     /* Creates a list to hold the obj */
//     struct gameobjlist * mylist = gameobjlist__init();
//     
//     gameobjlist__add(mylist, obj1);
//     // debug_print("List size %zu\n", mylist->size);
//     gameobjlist__add(mylist, obj2);
//     // debug_print("List size %zu\n", mylist->size);
//     gameobjlist__add(mylist, obj3);
//     // debug_print("List size %zu\n", mylist->size);
//     gameobjlist__add(mylist, (struct gameobj *) ship1);
//     // debug_print("List size %zu\n", mylist->size);
// 
//     ship__free(ship1);
