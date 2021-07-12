#include "level.h"
#include "player.h"
#include "enemy.h"
#include "helpers.h"
#include "assert/assert.h"
#include "print/print.h"
#include "random.h"
#include <vectrex.h>

extern const struct packet_t (*const numbers[])[];

extern struct rng_t rng;

const unsigned int enemy_count_per_level[] = {1, 2, 3, 4, 4, 5};

// The player object
struct player hero = {
    .id = 0,
    .pos = {50, 0},
    .shape = &player_shape[0]};

// Array to store all enemies in the game
struct enemy enemies[8] = {};

// Field to store which enemies are alive, one bit each
unsigned int enemies_alive = 0x00;
unsigned int enemies_left = 0;

enum levelState current_level_state = LEVEL_ACTIVE;
unsigned int level_timer_seconds = 30;
unsigned int level_timer_frames = 0;

struct GameStats stats =
    {
        .lifes = 5,
        .level = 0,
        .score = 0};

void insertNewEnemy(const struct enemy *const en, const unsigned int pos)
{
    assert(pos < 8);
    enemies[pos] = *en;
    enemies_alive |= 1 << pos;
    enemies_left++;
}

void level_init(void)
{
    unsigned int delay = 100;
    // Draw Level Greeting

    do
    {
        Wait_Recal();
        Intensity_5F();
        print_string(60, -100, "LEVEL\x80");
        print_unsigned_int(60, 40, stats.level);
        print_string(30, -100, "SCORE\x80");
        print_long_unsigned_int(30, 17, stats.score);
    } while (--delay > 0);

    // Reset the player position
    hero.pos = (struct vector_t){0, 0};

    enemies_left = 0;

    unsigned int encnt;
    if (stats.level > 5)
        encnt = 5;
    else
        encnt = enemy_count_per_level[stats.level];

    for (unsigned int i = 0; i < encnt; i++)
    {
        // Roll random positions until it is far enough from player
        struct vector_t pos;
        do
        {
            pos.x = (int)rnd(&rng);
            pos.y = (int)rnd(&rng);
        } while (isInRange(&pos, &((struct vector_t){0, 0})));

        struct enemy newen =
            {
                .id = i,
                .pos = pos,
                .shape = &enemy_shape[0],
                .target = {(int)rnd(&rng), (int)rnd(&rng)},
                .angle = 0,
                .fov = {{-21, -1}, {-21, 1}},
                .state = enemy_state_idle,
                .idle_timer = 100,
                .hunt_timer = 150,
                .weapon_charge = 0,
                .explosion_timer = 5};

        insertNewEnemy(&newen, i);
    }

    // Set current level to active
    current_level_state = LEVEL_ACTIVE;
    level_timer_seconds = 32;
}

void level_play(void)
{
    unsigned int delay = 50;
    while (current_level_state == LEVEL_ACTIVE) // while level is neither won nor los
    {
        Wait_Recal();

        // ------  PROCESS INPUT AND HANDLE ENTITIES ------
        // Handle player
        player_update(&hero);

        // Handle enemies
        for (unsigned int i = 0; i < 8; i++)
        {
            if (enemies_alive & (1 << i))
                enemy_update(&(enemies[i]));
        }

        if (stats.lifes <= 0)
        {
            current_level_state = LEVEL_LOST;
        }

        if (enemies_alive == 0x00) // All enemies are dead
        {

            if (--delay == 0)
            {
                current_level_state = LEVEL_WON;
                stats.score += level_timer_seconds;
            }
        }
        else
        {
            if (++level_timer_frames > 49)
            {
                level_timer_frames = 0;
                level_timer_seconds--;
                if (level_timer_seconds == 0)
                {
                    current_level_state = LEVEL_LOST;
                }
            }
        }

        // ------  DRAW ------
        // Draw player
        player_draw(&hero);

        // Draw enemies
        for (unsigned int i = 0; i < 8; i++)
        {
            if (enemies_alive & (1 << i))
                enemy_draw(&(enemies[i]));
        }

        // Draw life total
        Reset0Ref();
        dp_VIA_t1_cnt_lo = 125;
        Moveto_d(-123, 100);
        dp_VIA_t1_cnt_lo = 8;
        Intensity_5F();
        Draw_VLp((void *)numbers[stats.lifes - 1]);

        // Draw timer
        Reset0Ref();
        dp_VIA_t1_cnt_lo = 125;
        Moveto_d(-123, -89);
        dp_VIA_t1_cnt_lo = 37;
        Intensity_5F();
        Draw_Line_d(fov_circle[level_timer_seconds].y, fov_circle[level_timer_seconds].x);
    }
}