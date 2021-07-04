#include "enemy.h"
#include "utils/vector.h"
#include "vectrex.h"
#include "helpers.h"
#include "math/sin.h"
#include "math/cos.h"
#include "player.h"
#include "assert/assert.h"
#include "print/print.h"
#include "level.h"

#define SIN(angle) sin_##angle
#define COS(angle) cos_##angle

#define TURN(angle, y, x)                                                                         \
	{                                                                                             \
		((long int)(((double)y) * ((double)COS(angle)) + ((double)x) * ((double)SIN(angle)))),    \
			((long int)(((double)x) * ((double)COS(angle)) - ((double)y) * ((double)SIN(angle)))) \
	}

#define DIST 30

const struct vector_t fov_circle[] =
	{
		TURN(0, DIST, 0),
		TURN(4, DIST, 0),
		TURN(8, DIST, 0),
		TURN(12, DIST, 0),
		TURN(16, DIST, 0),
		TURN(20, DIST, 0),
		TURN(24, DIST, 0),
		TURN(28, DIST, 0),
		TURN(32, DIST, 0),
		TURN(36, DIST, 0),
		TURN(40, DIST, 0),
		TURN(44, DIST, 0),
		TURN(48, DIST, 0),
		TURN(52, DIST, 0),
		TURN(56, DIST, 0),
		TURN(60, DIST, 0),
		TURN(64, DIST, 0),
		TURN(68, DIST, 0),
		TURN(72, DIST, 0),
		TURN(76, DIST, 0),
		TURN(80, DIST, 0),
		TURN(84, DIST, 0),
		TURN(88, DIST, 0),
		TURN(92, DIST, 0),
		TURN(96, DIST, 0),
		TURN(100, DIST, 0),
		TURN(104, DIST, 0),
		TURN(108, DIST, 0),
		TURN(112, DIST, 0),
		TURN(116, DIST, 0),
		TURN(120, DIST, 0),
		TURN(124, DIST, 0),
		TURN(128, DIST, 0),
		TURN(132, DIST, 0),
		TURN(136, DIST, 0),
		TURN(140, DIST, 0),
		TURN(144, DIST, 0),
		TURN(148, DIST, 0),
		TURN(152, DIST, 0),
		TURN(156, DIST, 0),
		TURN(160, DIST, 0),
		TURN(164, DIST, 0),
		TURN(168, DIST, 0),
		TURN(172, DIST, 0),
		TURN(176, DIST, 0),
		TURN(180, DIST, 0),
		TURN(184, DIST, 0),
		TURN(188, DIST, 0),
		TURN(192, DIST, 0),
		TURN(196, DIST, 0),
		TURN(200, DIST, 0),
		TURN(204, DIST, 0),
		TURN(208, DIST, 0),
		TURN(212, DIST, 0),
		TURN(216, DIST, 0),
		TURN(220, DIST, 0),
		TURN(224, DIST, 0),
		TURN(228, DIST, 0),
		TURN(232, DIST, 0),
		TURN(236, DIST, 0),
		TURN(240, DIST, 0),
		TURN(244, DIST, 0),
		TURN(248, DIST, 0),
		TURN(252, DIST, 0),
};

// ---------------- DEFINE ENEMY SHAPE IN 64 ROTATION VARIANTS -----------------
#define SCALE 60
#if (1)
#define ANGLE 0
const struct packet_t enemy_shape_0[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 4
const struct packet_t enemy_shape_1[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 8
const struct packet_t enemy_shape_2[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 12
const struct packet_t enemy_shape_3[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 16
const struct packet_t enemy_shape_4[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 20
const struct packet_t enemy_shape_5[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 24
const struct packet_t enemy_shape_6[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 28
const struct packet_t enemy_shape_7[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 32
const struct packet_t enemy_shape_8[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 36
const struct packet_t enemy_shape_9[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 40
const struct packet_t enemy_shape_10[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 44
const struct packet_t enemy_shape_11[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 48
const struct packet_t enemy_shape_12[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 52
const struct packet_t enemy_shape_13[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 56
const struct packet_t enemy_shape_14[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 60
const struct packet_t enemy_shape_15[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 64
const struct packet_t enemy_shape_16[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 68
const struct packet_t enemy_shape_17[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 72
const struct packet_t enemy_shape_18[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 76
const struct packet_t enemy_shape_19[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 80
const struct packet_t enemy_shape_20[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 84
const struct packet_t enemy_shape_21[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 88
const struct packet_t enemy_shape_22[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 92
const struct packet_t enemy_shape_23[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 96
const struct packet_t enemy_shape_24[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 100
const struct packet_t enemy_shape_25[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 104
const struct packet_t enemy_shape_26[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 108
const struct packet_t enemy_shape_27[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 112
const struct packet_t enemy_shape_28[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 116
const struct packet_t enemy_shape_29[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 120
const struct packet_t enemy_shape_30[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 124
const struct packet_t enemy_shape_31[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 128
const struct packet_t enemy_shape_32[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 132
const struct packet_t enemy_shape_33[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 136
const struct packet_t enemy_shape_34[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 140
const struct packet_t enemy_shape_35[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 144
const struct packet_t enemy_shape_36[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 148
const struct packet_t enemy_shape_37[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 152
const struct packet_t enemy_shape_38[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 156
const struct packet_t enemy_shape_39[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 160
const struct packet_t enemy_shape_40[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 164
const struct packet_t enemy_shape_41[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 168
const struct packet_t enemy_shape_42[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 172
const struct packet_t enemy_shape_43[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 176
const struct packet_t enemy_shape_44[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 180
const struct packet_t enemy_shape_45[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 184
const struct packet_t enemy_shape_46[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 188
const struct packet_t enemy_shape_47[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 192
const struct packet_t enemy_shape_48[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 196
const struct packet_t enemy_shape_49[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 200
const struct packet_t enemy_shape_50[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 204
const struct packet_t enemy_shape_51[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 208
const struct packet_t enemy_shape_52[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 212
const struct packet_t enemy_shape_53[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 216
const struct packet_t enemy_shape_54[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 220
const struct packet_t enemy_shape_55[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 224
const struct packet_t enemy_shape_56[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 228
const struct packet_t enemy_shape_57[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 232
const struct packet_t enemy_shape_58[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 236
const struct packet_t enemy_shape_59[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 240
const struct packet_t enemy_shape_60[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 244
const struct packet_t enemy_shape_61[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 248
const struct packet_t enemy_shape_62[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#define ANGLE 252
const struct packet_t enemy_shape_63[] =
	{
#include "enemysprite.i"
};
#undef ANGLE
#endif

#if (1)
const struct packet_t (*const enemy_shapes[])[] =
	{
		&enemy_shape_0,
		&enemy_shape_1,
		&enemy_shape_2,
		&enemy_shape_3,
		&enemy_shape_4,
		&enemy_shape_5,
		&enemy_shape_6,
		&enemy_shape_7,
		&enemy_shape_8,
		&enemy_shape_9,
		&enemy_shape_10,
		&enemy_shape_11,
		&enemy_shape_12,
		&enemy_shape_13,
		&enemy_shape_14,
		&enemy_shape_15,
		&enemy_shape_16,
		&enemy_shape_17,
		&enemy_shape_18,
		&enemy_shape_19,
		&enemy_shape_20,
		&enemy_shape_21,
		&enemy_shape_22,
		&enemy_shape_23,
		&enemy_shape_24,
		&enemy_shape_25,
		&enemy_shape_26,
		&enemy_shape_27,
		&enemy_shape_28,
		&enemy_shape_29,
		&enemy_shape_30,
		&enemy_shape_31,
		&enemy_shape_32,
		&enemy_shape_33,
		&enemy_shape_34,
		&enemy_shape_35,
		&enemy_shape_36,
		&enemy_shape_37,
		&enemy_shape_38,
		&enemy_shape_39,
		&enemy_shape_40,
		&enemy_shape_41,
		&enemy_shape_42,
		&enemy_shape_43,
		&enemy_shape_44,
		&enemy_shape_45,
		&enemy_shape_46,
		&enemy_shape_47,
		&enemy_shape_48,
		&enemy_shape_49,
		&enemy_shape_50,
		&enemy_shape_51,
		&enemy_shape_52,
		&enemy_shape_53,
		&enemy_shape_54,
		&enemy_shape_55,
		&enemy_shape_56,
		&enemy_shape_57,
		&enemy_shape_58,
		&enemy_shape_59,
		&enemy_shape_60,
		&enemy_shape_61,
		&enemy_shape_62,
		&enemy_shape_63};
#endif

const struct packet_t enemy_shape[] =
	{
		{MOVE, {1 * SCALE, -1.5 * SCALE}},
		{DRAW, {-2 * SCALE, 0 * SCALE}},
		{DRAW, {0 * SCALE, 1.5 * SCALE}},
		{DRAW, {0 * SCALE, 1.5 * SCALE}},
		{DRAW, {2 * SCALE, 0 * SCALE}},
		{DRAW, {-1 * SCALE, -1 * SCALE}},
		{DRAW, {0 * SCALE, -1 * SCALE}},
		{DRAW, {1 * SCALE, -1 * SCALE}},
		{STOP, {-1 * SCALE, 1.5 * SCALE}}};

#undef SCALE
#define SCALE 18
const struct packet_t explosion_shape[] =
	{
		{MOVE, {1 * SCALE, -1 * SCALE}},
		{DRAW, {-3 * SCALE, 3 * SCALE}},
		{MOVE, {1.5 * SCALE, -4 * SCALE}},
		{DRAW, {1 * SCALE, 5 * SCALE}},
		{MOVE, {3 * SCALE, -1 * SCALE}},
		{DRAW, {-6.5 * SCALE, -4 * SCALE}},
		{MOVE, {5.5 * SCALE, 1 * SCALE}},
		{DRAW, {-6 * SCALE, 3 * SCALE}},
		{MOVE, {2.5 * SCALE, -2 * SCALE}},
		{DRAW, {4 * SCALE, 0 * SCALE}},
		{STOP, {0 * SCALE, 0 * SCALE}}};

struct packet_t rotated[9] = {};
extern struct enemy enemies[8];
extern unsigned int enemies_left;
extern struct player hero;
extern unsigned int enemies_alive;
extern struct GameStats stats;

void enemy_draw(const struct enemy *const en)
{
	if (en->state == enemy_state_dead)
	{
		return;
	}
	else if (en->state == enemy_state_exploding)
	{
		Reset0Ref();
		dp_VIA_t1_cnt_lo = 110;
		Moveto_d(en->pos.y, en->pos.x);
		dp_VIA_t1_cnt_lo = en->explosion_timer;
		Intensity_5F();
		Draw_VLp(&explosion_shape);
	}
	else
	{
		// Draw enemy shape
		/*Rot_VL_Mode(en->angle, (void *)en->shape, &rotated[0]);*/
		Reset0Ref();
		dp_VIA_t1_cnt_lo = 110;
		Moveto_d(en->pos.y, en->pos.x);
		dp_VIA_t1_cnt_lo = 8;
		Intensity_5F();
		/*Draw_VLp(&rotated[0]);*/
		Draw_VLp((void *)en->shape);

		// Draw enemy field of view
		Reset0Ref();
		Intensity_3F();
		dp_VIA_t1_cnt_lo = 110;
		Moveto_d(en->pos.y, en->pos.x);
		Draw_Line_d(en->fov[0].y - en->pos.y, en->fov[0].x - en->pos.x);
		Draw_Line_d(en->fov[1].y - en->fov[0].y, en->fov[1].x - en->fov[0].x);
		Draw_Line_d(en->pos.y - en->fov[1].y, en->pos.x - en->fov[1].x);

		if (en->state == enemy_state_hunt)
		{
			if (en->weapon_charge > 10)
			{
				struct vector_t dots[3];
				unsigned int alpha = ((en->angle << 2) + 16) >> 2;
				dots[0].y = fov_circle[alpha].y + en->pos.y;
				dots[0].x = fov_circle[alpha].x + en->pos.x;
				alpha = ((en->angle << 2) - 16) >> 2;
				dots[1].y = fov_circle[alpha].y + en->pos.y;
				dots[1].x = fov_circle[alpha].x + en->pos.x;
				alpha = ((en->angle << 2) - 0) >> 2;
				dots[2].y = fov_circle[alpha].y + en->pos.y;
				dots[2].x = fov_circle[alpha].x + en->pos.x;

				Reset0Ref();

				if (en->weapon_charge < 25)
					Intensity_1F();
				else if (en->weapon_charge > 24 && en->weapon_charge < 39)
					Intensity_3F();
				else
					Intensity_5F();

				dp_VIA_t1_cnt_lo = 110;
				Moveto_d(en->pos.y, en->pos.x);
				Draw_Line_d(dots[0].y - en->pos.y, dots[0].x - en->pos.x);
				Reset0Ref();
				Moveto_d(en->pos.y, en->pos.x);
				Draw_Line_d(dots[1].y - en->pos.y, dots[1].x - en->pos.x);
				Reset0Ref();
				Moveto_d(en->pos.y, en->pos.x);
				Draw_Line_d(dots[2].y - en->pos.y, dots[2].x - en->pos.x);
			}
		}
	}
}

#define ENEMYDOMOVE

void enemy_update(struct enemy *en)
{
	// Handle enemy state
	(*(en->state))(en);

	//enemy_handle_state(en);
	if (!(en->state == enemy_state_exploding || en->state == enemy_state_dead))
	{
		if (isInFOV(&hero.pos, en))
		{
			en->state = enemy_state_hunt;
			en->hunt_timer = 150;
		}

		en->angle = getAngle(&en->target, &en->pos);
		en->shape = &(*enemy_shapes[en->angle])[0];

		//en->fov[0] = (struct vector_t) {en1.pos.y, en1.pos.x};
		//unsigned int fov_angle_neg = (en->angle >= 8) ? en->angle - 8 : 56 + en->angle;
		//unsigned int fov_angle_pos = (en->angle < 54) ? en->angle + 8 : en->angle - 54;
		unsigned int fov_angle_neg = ((en->angle << 2) - 32) >> 2;
		unsigned int fov_angle_pos = ((en->angle << 2) + 32) >> 2;
		en->fov[0] = (struct vector_t){fov_circle[fov_angle_neg].y + en->pos.y, fov_circle[fov_angle_neg].x + en->pos.x};
		en->fov[1] = (struct vector_t){fov_circle[fov_angle_pos].y + en->pos.y, fov_circle[fov_angle_pos].x + en->pos.x};

		if (en->state == enemy_state_hunt)
		{
			enemy_load_weapon(en);
		}
	}
}

void enemy_state_idle(struct enemy *const en)
{
	if (en->idle_timer > 0)
	{
		en->idle_timer--;
	}
	else
	{
		en->idle_timer = Random() >> 1;
		en->state = enemy_state_wander;
	}
}

void enemy_state_wander(struct enemy *const en)
{
	if (en->pos.x == en->target.x && en->pos.y == en->target.y) // target reached
	{
		// Get a new random point to walk towards
		en->target = (struct vector_t){(int)Random(), (int)Random()};
		// Idle for a random amount of time before walking to the new target
		en->state = enemy_state_idle;
	}
	if (en->pos.x < en->target.x)
		en->pos.x++;
	if (en->pos.x > en->target.x)
		en->pos.x--;
	if (en->pos.y > en->target.y)
		en->pos.y--;
	if (en->pos.y < en->target.y)
		en->pos.y++;
}

void enemy_state_hunt(struct enemy *const en)
{
	en->target = hero.pos;
	if (en->pos.x < en->target.x)
		en->pos.x++;
	if (en->pos.x > en->target.x)
		en->pos.x--;
	if (en->pos.y > en->target.y)
		en->pos.y--;
	if (en->pos.y < en->target.y)
		en->pos.y++;

	if (en->hunt_timer > 0)
	{
		en->hunt_timer--;
	}
	else
	{
		en->hunt_timer = 150;
		en->weapon_charge = 0;
		en->state = enemy_state_idle;
	}
}

void enemy_state_exploding(struct enemy *const en)
{
	en->explosion_timer += 8;
	if (en->explosion_timer > 100)
	{
		enemies_left--;
		en->state = enemy_state_dead;
	}
}

void enemy_state_dead(struct enemy *const en)
{
	enemies_alive &= ~(1 << en->id); // Mark self as dead
}

void enemy_load_weapon(struct enemy *const en)
{
	en->weapon_charge++;
	if (en->weapon_charge > 49)
	{
		enemy_attack(en);
		en->weapon_charge = 0;
	}
}

void enemy_attack(struct enemy *const en)
{
	if (isInFOV(&hero.pos, en))
	{
		// do damage to player
		stats.lifes--;
	}
	for (unsigned int i = 0; i < 8; i++)
	{
		if (i == en->id)
			continue;

		if (enemies[i].state != enemy_state_dead && enemies[i].state != enemy_state_exploding)
		{
			if (isInFOV(&(enemies[i].pos), en))
			{
				enemies[i].state = enemy_state_exploding;
				//en->state = EXPLODING_S;
			}
		}
		/*if (enemies_alive & (1 << i))
		{
			if (isInFOV(&(enemies[i].pos), en))
			{

				enemies_alive &= ~(1 << (en->id)); // kill self
				enemies_alive &= ~(1 << i);		   // kill the other one
			}
		}*/
	}
}
