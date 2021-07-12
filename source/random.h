#pragma once
//8 bit pseudo random generator
struct rng_t
{
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int x;
};
void init_rng(struct rng_t *const p, const unsigned int seed_1, const unsigned int seed_2, const unsigned int seed_3);
unsigned int rnd(struct rng_t *const p);