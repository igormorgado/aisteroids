#ifndef __GAME_H__
#define __GAME_H__

#include <stdbool.h>

#include "sdl.h"
#include "phys.h"
#include "gameobjlist.h"

#define ASTEROID_SCORE_VAL  150

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

struct game 
{
    int space_size;

    // Global states
    bool bonus_used;
    float respawn_timer;
    float powerup_timer;
    int state;
    int score;
    int highscore;
    int num_lives;
    int wave_number;
    int num_asteroids;
    bool ai_on;

    // Game entities
    struct ship * main_ship;
    struct human_control * human_control;
    struct ai_control * ai_control;

    struct sdl_connector *sdlconn;
    struct gameobjlist * active_obj;
};


struct game * game__init(void);
void *        game__free(struct game * self);

void          game__update(struct game * self, float dt);
void          game__draw(struct game * self);
void          game__draw_lives(struct game * self);
void          game__clip(struct game * self, struct point3f * p);
void          game__use_control(struct game *self, int control);
void          game__blit(struct game *self);
void          game__wait(struct game *self, int wait);

void          game__update_score(struct game *self);
void          game__reset_score(struct game * self);

void          game__start(struct game * self);
void          game__start_next_wave(struct game * self);
void          game__launch_asteroid_wave(struct game * self);
void          game__wave_over(struct game * self);
void          game__over(struct game * self);
void          game__kill_ship(struct game * self, struct ship * ship);



#endif /* __GAME_H__ */
