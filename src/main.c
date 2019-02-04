#include "main.h"

int
main(void)
{

    float dt = 0.1;
    struct ship* xip = ship__init();

    debug_print("%s\n", "Initial position");
    xip->position->x = 1.1;
    xip->position->y = 2.1;
    xip->position->z = 0.0;
    debug_print("%s\n", "Accelerates");
    xip->acceleration = 2.1; 
    debug_print("%s\n", "Rotates");
    xip->ang_velocity = 3;

    ship__update(xip, dt);
    debug_print("%s\n", "Stop turn thursters");
    ship__turn_stop(xip);
    ship__update(xip, dt);
    debug_print("%s\n", "Stop thursters and acceleration");
    ship__stop(xip);
    ship__update(xip, dt);


    gameobjlist * mylist = gameobjlist__init();
    struct gameobj * o1 = gameobj__init();
    struct gameobj * o2 = gameobj__init();
    struct gameobj * o3 = gameobj__init();

    printf("My list size is: %zu\n", mylist->size);
    gameobjlist__add(mylist, o1);
    printf("My list size is: %zu\n", mylist->size);
    gameobjlist__add(mylist, o2);
    printf("My list size is: %zu\n", mylist->size);
    gameobjlist__add(mylist, o3);
    printf("My list size is: %zu\n", mylist->size);

    gameobjlist__print(mylist);
    
    gameobjlist__add(mylist, (struct gameobj *)xip);

    printf("\n");
    gameobjlist__print(mylist);
    

    return 0;
}
