#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Console.h>
//#include <CUnit/Automated.h>

#include "debug.h"
#include "ship.h"
#include "test_main.h"
#include "mocks.h"
#include "gameobj.h"
#include "gameobjnode.h"
#include "gameobjlist.h"

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

void 
test__gameobj_create(void)
{
	struct gameobj * obj1 = gameobj__init();
	*obj1 = (struct gameobj) TEST_SAMPLE_GAMEOBJECT;

	CU_ASSERT_DOUBLE_EQUAL(obj1->position.x, 1.1f, 0.001f);
	CU_ASSERT_EQUAL(obj1->angle, 3);
	CU_ASSERT_TRUE(obj1->active);
}

void
test__gameobj_free(void)
{
	struct gameobj * obj1 = gameobj__init();
	*obj1 = (struct gameobj) TEST_SAMPLE_GAMEOBJECT;
	gameobj__free(obj1);
	CU_ASSERT_PTR_NULL(obj1)
}

int main (void)
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "gameobj_tests", init_suite, clean_suite );
   if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ( (NULL == CU_add_test(pSuite, "gameobj__create", test__gameobj_create)) ||
        (NULL == CU_add_test(pSuite, "gameobj__free", test__gameobj_free)) 
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run all tests using the basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");
/*
   // Run all tests using the automated interface
   CU_automated_run_tests();
   CU_list_tests_to_file();

   // Run all tests using the console interface
   CU_console_run_tests();
*/
   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}

// 
//     /* GAME OBJ STRUCT TESTS */
//     struct gameobj_params param_obj1 = TEST_SAMPLE_GAMEOBJECT;
//     obj1->position->x = 1.1;
//     obj1->position->y = 1.2;
//     obj1->position->z = 0.0;
// 
//     struct gameobj_params param_obj2 = {
//         .size = 2,
//         .acceleration = 0.2,
//         .angle = 3,
//         .ang_velocity = 0.8,
//         .active = true,
//         .life_timer = 5000,
//         .type = 0
//     };
//     struct gameobj * obj2 = gameobj__init(param_obj2);
//     obj2->position->x = 2.1;
//     obj2->position->y = 2.2;
//     obj2->position->z = 0.0;
// 
// 
// 
//     struct gameobj_params param_obj3 = {
//         .size = 3,
//         .acceleration = 0.2,
//         .angle = 3,
//         .ang_velocity = 0.8,
//         .active = true,
//         .life_timer = 5000,
//         .type = 0
//     };
//     struct gameobj * obj3 = gameobj__init(param_obj3);
//     obj3->position->x = 3.1;
//     obj3->position->y = 3.2;
//     obj3->position->z = 0.0;
// 
//     struct ship_params param_ship = {
//         .base.size = 3,
//         .base.acceleration = 2.2,
//         .base.angle = 3,
//         .base.ang_velocity = 0.8,
//         .base.active = true,
//         .base.life_timer = 5000,
//         .base.type = 0,
// 	.active_bullet_count = 0
//     };
//     struct ship * ship1 = ship__init(param_ship);
//     ship1->base.position->x = 4.1;
//     ship1->base.position->y = 4.2;
//     ship1->base.position->z = 0.0;
//     // ship1->base.velocity->x = 0.0;
//     // ship1->base.velocity->y = 0.0;
//     // ship1->base.velocity->z = 0.0;
// 
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
// 
//     // gameobjlist__print(mylist);
// 
//     float dt = 0.5;
//     ship__update(ship1, dt);
//     // gameobj__print((struct gameobj *) ship1);
//     // gameobjlist__print(mylist);
// 
//     gameobjlist__free(mylist);
//     gameobj__free(obj1);
//     gameobj__free(obj2);
//     gameobj__free(obj3);
//     ship__free(ship1);
// 
// }
// 
