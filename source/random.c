#include "random.h"
//8 bit pseudo random generator

struct rng_t rng;

// ---------------------------------------------------------------------------

void init_rng(struct rng_t *const p, const unsigned int seed_1, const unsigned int seed_2, const unsigned int seed_3)
{
	p->a = seed_1;
	p->b = seed_2;
	p->c = seed_3;

	p->x = 1;
	p->a = (p->a ^ p->c ^ p->x);
	p->b = (p->b + p->a);
	p->c = ((p->c + (p->b >> 1)) ^ p->a);
}

// ---------------------------------------------------------------------------

unsigned int rnd(struct rng_t *const p)
{
	p->x++;								  //x is incremented every round and is not affected by any other variable
	p->a = (p->a ^ p->c ^ p->x);		  //note the mix of addition and XOR
	p->b = (p->b + p->a);				  //and the use of very few instructions
	p->c = ((p->c + (p->b >> 1)) ^ p->a); //the right shift is to ensure that high-order bits from b can affect
	return p->c;						  //low order bits of other variables
}
