#pragma once
#include "utils/vector.h"
#include "player.h"

extern const struct vector_t fov_circle[];
extern const struct packet_t enemy_shape[];

/*enum EnemyState
{
	DEAD_S = 0,
	IDLE_S,
	WANDER_S,
	HUNT_S,
	EXPLODING_S
};*/

struct enemy
{
	unsigned int id;
	struct vector_t pos;
	const struct packet_t *shape;
	struct vector_t target;
	unsigned int angle;
	struct vector_t fov[2];
	//enum EnemyState state;
	void (*state)(struct enemy *const en);
	unsigned int idle_timer;
	unsigned int hunt_timer;
	unsigned int weapon_charge;
	unsigned int explosion_timer;
};

// Main logic for the enemy
extern void enemy_update(struct enemy *en);

// Enemy State Machine
void enemy_state_idle(struct enemy *const en);
void enemy_state_wander(struct enemy *const en);
void enemy_state_hunt(struct enemy *const en);
void enemy_state_exploding(struct enemy *const en);
void enemy_state_dead(struct enemy *const en);

//extern void enemy_handle_state(struct enemy *en);

// Drawing Routine for the enemy
extern void enemy_draw(const struct enemy *const en);

extern void enemy_attack(struct enemy *const en);

extern void enemy_load_weapon(struct enemy *const en);