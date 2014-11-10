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
 *Add a point b in the polygon a at the end
 */

#endif

