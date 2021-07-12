#include "helpers.h"
#include "atantables.h"
#include "print/print.h"
#include "vectrex.h"
#include "enemy.h"

int abs(int i)
{
    return i < 0 ? -i : i;
}

// Function to embedd an arctan lookup table with additional logic to reduce its size
unsigned int atan2_lookup(int y, int x)
{
    unsigned int angle = 0;
    unsigned int flags = 0x00;

    if (x == 0 && y > 0)
        return 64;
    if (x == 0 && y < 0)
        return 192;
    if (y == 0 && x > 0)
        return 0;
    if (y == 0 && x < 0)
        return 128;
    if (x == 0 && y == 0)
        return 0;

    if (x < 0)
    {
        flags |= 0b00000010;
        x = abs(x);
    }
    if (y < 0)
    {
        flags |= 0b00000100;
        y = abs(y);
    }

    if (y < x)
    {
        //swap
        int tmp = y;
        y = x;
        x = tmp;
        flags |= 0b00000001;
    }

    angle = atantable[log2table[y] - log2table[x]];
    if ((flags & 0b00000110) == 0b00000010)
    {
        // y+ x- -> q2
        if (!(flags & 0x01))
            angle = 64 - angle;
        angle += 64;
    }
    else if ((flags & 0b00000110) == 0b00000110)
    {
        // x and y were negative -> q3
        if (flags & 0x01)
            angle = 64 - angle;
        angle += (unsigned int)128;
    }
    else if ((flags & 0b00000110) == 0b00000100)
    {
        // y-, x+ -> q4
        if (!(flags & 0x01))
            angle = 64 - angle;
        angle += (unsigned int)192;
    }
    else
    {
        // y+, x+ -> q1
        if (flags & 0x01)
            angle = 64 - angle;
    }
    return angle;
}

// Calculate the angle between source and target while preventing over- and underflow
unsigned int getAngle(const struct vector_t *const target, const struct vector_t *const source)
{
    // set to default first and then correct if necessary
    int newx = target->x - source->x;
    int newy = target->y - source->y;

    // prevent underflow and overflow for x
    if (target->x > 0 && source->x < 0)
    {
        if (source->x < -127 + target->x)
        {
            newx = 127; // set to max, because it has exceed it
        }
    }
    else if (target->x < 0 && source->x > 0)
    {
        if (source->x > target->x + 128)
        {
            newx = -128; // set to min, because it has underflown
        }
    }
    // prevent underflow and overflow for y
    if (target->y > 0 && source->y < 0)
    {
        if (source->y < -127 + target->y)
        {
            newy = 127; // set to max, because it has exceed it
        }
    }
    else if (target->y < 0 && source->y > 0)
    {
        if (source->y > target->y + 128)
        {
            newy = -128; // set to min, because it has underflown
        }
    }

    // calculate angle
    return ((atan2_lookup(newy, newx) - 64) >> 2);
}

// Calculate a slightly optimized Manhattan distance and check against a threshold
int isInRange(const struct vector_t *const a, const struct vector_t *const b)
{
    unsigned int ax = (unsigned int)((unsigned int)a->x + 120U);
    unsigned int bx = (unsigned int)((unsigned int)b->x + 120U);

    unsigned int ay = (unsigned int)((unsigned int)a->y + 120U);
    unsigned int by = (unsigned int)((unsigned int)b->y + 120U);

    unsigned int xdiff;
    unsigned int ydiff;

    if (ax > bx)
        xdiff = ax - bx;
    else
        xdiff = bx - ax;

    if (xdiff > 30)
        return 0;

    if (ay > by)
        ydiff = ay - by;
    else
        ydiff = by - ay;

    if (ydiff > 30)
        return 0;

    return ((xdiff + ydiff) < 43) ? 1 : 0;
}

// Check if a position is in the field of view of the given enemy
int isInFOV(const struct vector_t *const target, const struct enemy *const self)
{
    if (isInRange(target, &self->pos))
    {
        int angle_target = (int)getAngle(target, &self->pos);

        int angle_tmp = (int)self->angle - 8;
        if (angle_tmp < 0)
            angle_tmp = 64 + angle_tmp;

        angle_tmp = angle_target - angle_tmp;
        if (angle_tmp < 0)
            angle_tmp += 64;

        if (angle_tmp < 17)
            return 1;

        return 0;
    }
    return 0;
}
