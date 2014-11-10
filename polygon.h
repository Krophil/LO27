/*
 * Pierre Brunet
 * pierre.brunet-de-monthelie@utbm.fr
 *
 *
 */

#ifndef POLYGON_H
#define POLYGON_H

typedef struct{
    double x;
    double y;
}point;

typedef struct Element{
    struct Element* prev;
    point point;
    struct Element* next;
    int index;
}elem;

typedef struct{
    elem* head;
    int N;
}Polygon;


point createPoint(double a, double b);
/*
 *Creates a point with coordinates :
 *X-axis=a
 *Y-axis=b
 */

Polygon createPolygon();
/*
 *creates an empty polygon
 */

Polygon addPoint(Polygon a, point b);
/*
 *Adds a point b in the polygon a at the end
 */

Polygon removePoint(Polygon p, int i);
/*
 * Removes the ith point in the polygon p
 */
#endif

