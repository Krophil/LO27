/*
 * Pierre Brunet
 * pierre.brunet-de-monthelie@utbm.fr
 *
 *
 */

#ifndef DEF_
#define DEF_

typedef struct{
    double x;
    double y;
}point;

typedef struct *Element{
    *Element prev;
    point point;
    *Element next;
    int index;
}elem;

typedef struct{
    *Element head;
    int N;
}PolygonList;

#endif

