#ifndef __MOCKS_H__
#define __MOCKS_H__

#define TEST_SAMPLE_GAMEOBJECT {				\
        .size = 1,                                      	\
        .acceleration = 0.2,                            	\
        .angle = 3,                                     	\
        .ang_velocity = 0.8,                            	\
        .active = true,                                 	\
        .life_timer = 5000,                             	\
        .type = 0,                                       	\
	.position = (struct point3f) { .x = 1.1, .y = 2.1, .z = 3.1 }	\
    }							

#endif /* __MOCKS_H__ */









