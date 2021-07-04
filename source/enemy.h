#pragma once
#include "utils/vector.h"
#include "player.h"

extern const struct vector_t fov_circle[];
extern const struct packet_t enemy_shape[];

enum EnemyState
{
	DEAD_S = 0,
	IDLE_S,
	WANDER_S,
	HUNT_S,
	EXPLODING_S
};

struct enemy
{
	unsigned int id;
	struct vector_t pos;
	const struct packet_t *shape;
	struct vector_t target;
	unsigned int angle;
	struct vector_t fov[2];
	enum EnemyState state;
	unsigned int idle_timer;
	unsigned int hunt_timer;
	unsigned int weapon_charge;
	unsigned int explosion_timer;
};

// Main logic for the enemy
extern void enemy_update(struct enemy *en);

// Enemy State Machine
extern void enemy_handle_state(struct enemy *en);

// Drawing Routine for the enemy
extern void enemy_draw(const struct enemy *const en);

extern void enemy_attack(struct enemy *const en);

extern void enemy_load_weapon(struct enemy *const en);