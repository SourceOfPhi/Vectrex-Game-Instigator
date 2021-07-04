#pragma once

struct GameStats
{
    unsigned int level;
    int lifes;
    unsigned long int score;
};

enum levelState
{
    LEVEL_LOST,
    LEVEL_WON,
    LEVEL_ACTIVE
};

void level_init(void);

void level_play(void);
