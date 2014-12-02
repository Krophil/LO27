/*
 * Pierre Brunet
 * pierre.brunet-de-monthelie@utbm.fr
 *
 * Guillaume Prost
 * guillaume.prost@utbm.fr
 *
 */

#ifndef POLYGON_H
#define POLYGON_H
#include <bool.h>
typedef struct{
    double x;
    double y;
}Point;

typedef struct{
    Point point;
    Point* next;
    int index;
}PointList;

typedef struct elem{
    struct elem* prev;
    Point point;
    struct elem* next;
    int index;
}Element;

typedef struct{
    Element* head;
    int N;
}Polygon;

/*typedef struct{
 *  Polygon pol;
 *  int N;
}*/

Point createPoint(double a, double b);
/*
 *Creates a point with coordinates :
 *X-axis=a
 *Y-axis=b
 */

Polygon createPolygon();
/*
 *creates an empty polygon
 */

Polygon addPoint(Polygon a, Point b);
/*
 *Adds a point b in the polygon a at the end
 */

Polygon removePoint(Polygon p, int i);
/*
 * Removes the ith point in the polygon p
 */

Polygon unionPolygons(Polygon p, Polygon q);
/*
 * Computes the union between the two specified polygons
 */

void printPoint(int i);
/*
 * print the ith point in the list of points.
 */

Bool containsPoint(Polygon p, Point b);
/*
 *returns true if the specified polygon contains the specified point, false otherwise
 */
#endif

