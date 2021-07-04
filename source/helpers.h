#pragma once
#include "utils/vector.h"
#include "enemy.h"

extern int abs(int i);
extern int isInRange(const struct vector_t *const a, const struct vector_t *const b);
extern unsigned int getAngle(const struct vector_t *const target, const struct vector_t *const source);
extern int isInFOV(const struct vector_t *const target, const struct enemy *const self);
/*
extern int getSideOfLine(struct vector_t *A, struct vector_t *B, struct vector_t *C);

extern int isPointInTriangle(struct vector_t *A, struct vector_t *B, struct vector_t *C, struct vector_t *PT);

extern int intpoint_inside_trigon(struct vector_t *s, struct vector_t *a, struct vector_t *b, struct vector_t *c);
*/
