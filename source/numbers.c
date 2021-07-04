#include "utils/vector.h"

#define SCALE 60

const struct packet_t number_5[] = {
    {MOVE, {2 * SCALE, 1 * SCALE}},
    {DRAW, {0 * SCALE, -2 * SCALE}},
    {DRAW, {-2 * SCALE, 0 * SCALE}},
    {DRAW, {0 * SCALE, 2 * SCALE}},
    {DRAW, {-2 * SCALE, 0 * SCALE}},
    {DRAW, {0 * SCALE, -2 * SCALE}},
    {STOP, {0 * SCALE, 0 * SCALE}}};

const struct packet_t number_4[] = {
    {MOVE, {2 * SCALE, 1 * SCALE}},
    {DRAW, {-2 * SCALE, 0 * SCALE}},
    {DRAW, {-2 * SCALE, 0 * SCALE}},
    {MOVE, {2 * SCALE, 0 * SCALE}},
    {DRAW, {0 * SCALE, -2 * SCALE}},
    {DRAW, {2 * SCALE, 0 * SCALE}},
    {STOP, {0 * SCALE, 0 * SCALE}}};

const struct packet_t number_3[] = {
    {MOVE, {2 * SCALE, -1 * SCALE}},
    {DRAW, {0 * SCALE, 2 * SCALE}},
    {DRAW, {-2 * SCALE, 0 * SCALE}},
    {DRAW, {-2 * SCALE, 0 * SCALE}},
    {DRAW, {0 * SCALE, -2 * SCALE}},
    {MOVE, {2 * SCALE, 0 * SCALE}},
    {DRAW, {0 * SCALE, 2 * SCALE}},
    {STOP, {0 * SCALE, 0 * SCALE}}};

const struct packet_t number_2[] = {
    {MOVE, {2 * SCALE, -1 * SCALE}},
    {DRAW, {0 * SCALE, 2 * SCALE}},
    {DRAW, {-2 * SCALE, 0 * SCALE}},
    {DRAW, {0 * SCALE, -2 * SCALE}},
    {DRAW, {-2 * SCALE, 0 * SCALE}},
    {DRAW, {0 * SCALE, 2 * SCALE}},
    {STOP, {0 * SCALE, 0 * SCALE}}};

const struct packet_t number_1[] = {
    {MOVE, {2 * SCALE, 0 * SCALE}},
    {DRAW, {-2 * SCALE, 0 * SCALE}},
    {DRAW, {-2 * SCALE, 0 * SCALE}},
    {STOP, {0 * SCALE, 0 * SCALE}}};

const struct packet_t (*const numbers[])[] = {
    &number_1,
    &number_2,
    &number_3,
    &number_4,
    &number_5};
