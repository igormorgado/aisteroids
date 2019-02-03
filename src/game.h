#ifndef __GAME_H__
#define __GAME_H__

#include <stdbool.h>

#include "phys.h"

enum CONTROL
{
    CONTROL_THRUST_ON,
    CONTROL_THRUST_REVERSE,
    CONTROL_THRUST_OFF,
    CONTROL_RIGHT_ON,
    CONTROL_LEFT_ON,
    CONTROL_STOP,
    CONTROL_SHOOT,
    CONTROL_HYPERSPACE,
    CONTROL_PAUSE,
    CONTROL_AION,
    CONTROL_AIOFF
};

enum GAMESTATE
{
    STATE_PLAY,
    STATE_PAUSE,
    STATE_NEXTWAVE,
    STATE_GAMEOVER
};

struct game {
    // Rendering options
    int screen_width;
    int screen_height;
    int space_size;

    bool bonus_used;
    float respawn_timer;
    float powerup_timer;
    int state;
    int score;
    int num_lives;
    int wave_number;
    int num_asteroids;
    bool ai_on;

    struct ship * ship;
    struct human_control * humanControl;
    struct ai_control * aiControl;
};



void    game__update(struct game * self, float dt);
void    game__draw(struct game * self);
void    game__draw_lives(struct game * self);
void    game__clip(struct game * self, point3f * p);
void    game__use_control(struct game *self, int control);

void    game__increment_score(struct game * self, int value); 
void    game__reset_score(struct game * self);

void    game__start(struct game * self);
void    game__start_next_wave(struct game * self);
void    game__launch_asteroid_wave(struct game * self);
void    game__wave_over(struct game * self);
void    game__over(struct game * self);
void    game__kill_ship(struct game * self, struct ship * ship);



#endif
