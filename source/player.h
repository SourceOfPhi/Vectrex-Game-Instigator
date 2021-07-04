#pragma once
#include "utils/vector.h"

extern const struct packet_t player_shape[];

struct player
{
	unsigned int id;
	struct vector_t pos;
	const struct packet_t *shape;
};

//extern struct player hero;

extern void player_update(struct player *hero);

extern void player_draw(const struct player *const hero);
