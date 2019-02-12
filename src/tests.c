#include <stdio.h>

#include "debug.h"
#include "ship.h"
#include "tests.h"
#include "gameobj.h"
#include "gameobjnode.h"
#include "gameobjlist.h"


void
tests__run(void)
{

    /* GAME OBJ STRUCT TESTS */
    struct gameobj_params param_obj1 = {
        .size = 1,
        .acceleration = 0.2,
        .angle = 3,
        .ang_velocity = 0.8,
        .active = true,
        .life_timer = 5000,
        .type = 0
    };
    struct gameobj * obj1 = gameobj__init(param_obj1);
    obj1->position->x = 1.1;
    obj1->position->y = 1.2;
    obj1->position->z = 0.0;

    struct gameobj_params param_obj2 = {
        .size = 2,
        .acceleration = 0.2,
        .angle = 3,
        .ang_velocity = 0.8,
        .active = true,
        .life_timer = 5000,
        .type = 0
    };
    struct gameobj * obj2 = gameobj__init(param_obj2);
    obj2->position->x = 2.1;
    obj2->position->y = 2.2;
    obj2->position->z = 0.0;



    struct gameobj_params param_obj3 = {
        .size = 3,
        .acceleration = 0.2,
        .angle = 3,
        .ang_velocity = 0.8,
        .active = true,
        .life_timer = 5000,
        .type = 0
    };
    struct gameobj * obj3 = gameobj__init(param_obj3);
    obj3->position->x = 3.1;
    obj3->position->y = 3.2;
    obj3->position->z = 0.0;

    struct ship_params param_ship = {
        .base.size = 3,
        .base.acceleration = 2.2,
        .base.angle = 3,
        .base.ang_velocity = 0.8,
        .base.active = true,
        .base.life_timer = 5000,
        .base.type = 0,
	.active_bullet_count = 0
    };
    struct ship * ship1 = ship__init(param_ship);
    ship1->base.position->x = 4.1;
    ship1->base.position->y = 4.2;
    ship1->base.position->z = 0.0;

    
    /* Creates a list to hold the obj */
    struct gameobjlist * mylist = gameobjlist__init();
    
    gameobjlist__add(mylist, obj1);
    // debug_print("List size %zu\n", mylist->size);
    gameobjlist__add(mylist, obj2);
    // debug_print("List size %zu\n", mylist->size);
    gameobjlist__add(mylist, obj3);
    // debug_print("List size %zu\n", mylist->size);
    gameobjlist__add(mylist, (struct gameobj *) ship1);
    // debug_print("List size %zu\n", mylist->size);


    // gameobjlist__print(mylist);

    float dt = 0.5;
    ship__update(ship1, dt);
    // gameobj__print((struct gameobj *) ship1);
    // gameobjlist__print(mylist);

    gameobjlist__free(mylist);
    gameobj__free(obj1);
    gameobj__free(obj2);
    gameobj__free(obj3);
    ship__free(ship1);

}

