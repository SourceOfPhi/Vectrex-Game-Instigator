#include "player.h"
#include "utils/vector.h"
#include "vectrex.h"
#include "utils/controller.h"
#include "math/sin.h"
#include "math/cos.h"
#include "helpers.h"
#include "assert/assert.h"

#define SIN(angle) sin_##angle
#define COS(angle) cos_##angle

#define TURN(angle, y, x)                                                                         \
	{                                                                                             \
		((long int)(((double)y) * ((double)COS(angle)) + ((double)x) * ((double)SIN(angle)))),    \
			((long int)(((double)x) * ((double)COS(angle)) - ((double)y) * ((double)SIN(angle)))) \
	}

#define SF 32

const struct packet_t player_shape[] =
	{
		{MOVE, {0 * SF, -2 * SF}},
		{DRAW, {-1 * SF, 0 * SF}},
		{DRAW, {2 * SF, 2 * SF}},
		{DRAW, {-2 * SF, 2 * SF}},
		{DRAW, {1 * SF, 0 * SF}},
		{MOVE, {0 * SF, -1 * SF}},
		{DRAW, {-1 * SF, 0 * SF}},
		{DRAW, {0 * SF, -2 * SF}},
		{DRAW, {1 * SF, 0 * SF}},
		{STOP, {0 * SF, 1 * SF}}};

#define ANGLE 0
const struct packet_t player_shape_0[] =
	{
#include "playersprite.i"
};
#undef ANGLE
#define ANGLE 32
const struct packet_t player_shape_32[] =
	{
#include "playersprite.i"
};
#undef ANGLE
#define ANGLE 64
const struct packet_t player_shape_64[] =
	{
#include "playersprite.i"
};
#undef ANGLE
#define ANGLE 96
const struct packet_t player_shape_96[] =
	{
#include "playersprite.i"
};
#undef ANGLE
#define ANGLE 128
const struct packet_t player_shape_128[] =
	{
#include "playersprite.i"
};
#undef ANGLE
#define ANGLE 160
const struct packet_t player_shape_160[] =
	{
#include "playersprite.i"
};
#undef ANGLE
#define ANGLE 192
const struct packet_t player_shape_192[] =
	{
#include "playersprite.i"
};
#undef ANGLE
#define ANGLE 224
const struct packet_t player_shape_224[] =
	{
#include "playersprite.i"
};
#undef ANGLE

const struct packet_t (*const player_shapes[])[] =
	{
		&player_shape_0,
		&player_shape_32,
		&player_shape_64,
		&player_shape_96,
		&player_shape_128,
		&player_shape_160,
		&player_shape_192,
		&player_shape_224};

extern unsigned int enemies_left;
extern unsigned int enemies_alive;
extern struct enemy enemies[8];

unsigned int slash_angle = 64;

void player_update(struct player *hero)
{
	Joy_Digital();

	if (joystick_1_up())
	{
		if (hero->pos.y < 118)
			hero->pos.y = hero->pos.y + 2;
		hero->shape = &(*player_shapes[0])[0];
	}
	if (joystick_1_down())
	{
		if (hero->pos.y > -118)
			hero->pos.y = hero->pos.y - 2;
		hero->shape = &(*player_shapes[4])[0];
	}
	if (joystick_1_left())
	{
		if (hero->pos.x > -120)
			hero->pos.x = hero->pos.x - 2;
		if (joystick_1_up())
		{
			hero->shape = &(*player_shapes[1])[0];
		}
		else if (joystick_1_down())
		{
			hero->shape = &(*player_shapes[3])[0];
		}
		else
		{
			hero->shape = &(*player_shapes[2])[0];
		}
	}
	if (joystick_1_right())
	{
		if (hero->pos.x < 120)
			hero->pos.x = hero->pos.x + 2;
		if (joystick_1_up())
		{
			hero->shape = &(*player_shapes[7])[0];
		}
		else if (joystick_1_down())
		{
			hero->shape = &(*player_shapes[5])[0];
		}
		else
		{
			hero->shape = &(*player_shapes[6])[0];
		}
	}

	// Check if only one enemy is left
	if (enemies_left == 1)
	{

		Read_Btns();

		// If so, check slash button
		if (button_1_4_pressed())
		{
			// Find out which enemy is left
			struct enemy *target = 0;
			for (int i = 0; i < 8; i++)
			{
				if (enemies_alive & (1 << i))
				{
					target = &enemies[i];
					break;
				}
			}

			// Slash in a circle around the player (roundhouse kick!)
			if (isInRange(&hero->pos, &target->pos))
			{
				// Destroy the enemy
				target->state = enemy_state_exploding;
				slash_angle = 0;
			}
		}
	}
}

void player_draw(const struct player *const hero)
{
	Reset0Ref();
	dp_VIA_t1_cnt_lo = 110;
	Moveto_d(hero->pos.y, hero->pos.x);
	dp_VIA_t1_cnt_lo = 16;
	Intensity_5F();
	Draw_VLp((void *)hero->shape);

	if (slash_angle < 64)
	{
		Reset0Ref();
		dp_VIA_t1_cnt_lo = 110;
		Moveto_d(hero->pos.y, hero->pos.x);
		assert(slash_angle < 64);
		Draw_Line_d(fov_circle[slash_angle].y, fov_circle[slash_angle].x);
		slash_angle += 3;
	}
}
