/*
 * Pierre Brunet
 * pierre.brunet-de-monthelie@utbm.fr
 *
 *
 */

#ifndef STATE_H
#define STATE_H

typedef enum{
    INSIDE=1,
    OUTSIDE=2,
    INTERSECT=3,
    ENCLOSING=4,
    EQUAL=5,
    SAMESHAPE=6,
    ERROR=7
}State;

#endif

