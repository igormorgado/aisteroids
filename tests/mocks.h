#ifndef __MOCKS_H__
#define __MOCKS_H__

#define SETUP_GAMEOBJ1_TEST						\
	struct gameobj * obj1 = gameobj__init();			\
	obj1->size = 1.0f;						\
	obj1->acceleration = .5f;                                       \
	obj1->angle = 3.0f;                                             \
	obj1->ang_velocity = 0.5f;                                      \
	obj1->active = true;                                            \
	obj1->life_timer = 5.0f;                                        \
	obj1->type = 0;                                                 \
	obj1->velocity.x = 0.0f;                                        \
	obj1->velocity.y = 0.0f;                                        \
	obj1->velocity.z = 0.0f;					\
	obj1->position.x = 1.1f;                                        \
	obj1->position.y = 2.1f;                                        \
	obj1->position.z = 3.1f;

#define TEARDOWN_GAMEOBJ1_TEST obj1 = gameobj__free(obj1)


#define SETUP_GAMEOBJ2_TEST						\
	struct gameobj * obj2 = gameobj__init();			\
	obj2->size = 2.0f;						\
	obj2->acceleration = .2f;                                       \
	obj2->angle = 3.1f;                                             \
	obj2->ang_velocity = 0.7f;                                      \
	obj2->active = true;                                            \
	obj2->life_timer = 0.0f;                                        \
	obj2->type = 0;                                                 \
	obj2->velocity.x = 0.0f;                                        \
	obj2->velocity.y = 0.0f;                                        \
	obj2->velocity.z = 0.0f;					\
	obj2->position.x = 2.1f;                                        \
	obj2->position.y = 2.1f;                                        \
	obj2->position.z = 0.0f;

#define TEARDOWN_GAMEOBJ2_TEST obj2 = gameobj__free(obj2)


#define SETUP_GAMEOBJ3_TEST						\
	struct gameobj * obj3 = gameobj__init();			\
	obj3->size = 2.0f;						\
	obj3->acceleration = .2f;                                       \
	obj3->angle = 3.1f;                                             \
	obj3->ang_velocity = 0.7f;                                      \
	obj3->active = false;                                           \
	obj3->life_timer = 0.0f;                                        \
	obj3->type = 0;                                                 \
	obj3->velocity.x = 0.0f;                                        \
	obj3->velocity.y = 0.0f;                                        \
	obj3->velocity.z = 0.0f;					\
	obj3->position.x = 3.1f;                                        \
	obj3->position.y = 3.1f;                                        \
	obj3->position.z = 0.0f;

#define TEARDOWN_GAMEOBJ3_TEST obj3 = gameobj__free(obj3)


#define SETUP_SHIP1_TEST						\
	struct ship * ship1 = ship__init();				\
	ship1->base.size = 2.0f;					\
	ship1->base.acceleration = .2f;                                 \
	ship1->base.angle = 3.1f;                                       \
	ship1->base.ang_velocity = 0.7f;                                \
	ship1->base.active = true;                                      \
	ship1->base.life_timer = 5.0f;                                  \
	ship1->base.type = 0;                                           \
	ship1->base.obj_flags = OBJ_SHIP;                               \
	ship1->base.velocity.x = 0.0f;                                  \
	ship1->base.velocity.y = 0.0f;                                  \
	ship1->base.velocity.z = 0.0f;					\
	ship1->base.position.x = 3.5f;                                  \
	ship1->base.position.y = 3.2f;                                  \
	ship1->base.position.z = 0.0f;					\
	ship1->active_bullet_count = 2;					\
	ship1->invincibility_timer = 0.0f;				\

#define TEARDOWN_SHIP1_TEST ship1 = ship__free(ship1)


#define SETUP_GAMEOBJNODE_TEST						\
	SETUP_GAMEOBJ1_TEST;						\
	SETUP_GAMEOBJ2_TEST;						\
	SETUP_GAMEOBJ3_TEST;						\
	SETUP_SHIP1_TEST;						\


#define TEARDOWN_GAMEOBJNODE_TEST 					\
	TEARDOWN_GAMEOBJ1_TEST;						\
	TEARDOWN_GAMEOBJ2_TEST;						\
	TEARDOWN_GAMEOBJ3_TEST;						\
	TEARDOWN_SHIP1_TEST;						\

#endif /* __MOCKS_H__ */









