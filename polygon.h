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
#include <state.h>
#include <math.h>
#include <string.h>


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

Bool containsPoint(Polygon p, Point b);
/*
 *returns true if the specified polygon contains the specified point, false otherwise
 */

State containsPolygon(Polygon p1, Polygon p2);
/*
 *returns :
 * INSIDE if the second polygon is fully inside the first one ;
 * OUTSIDE if the second polygon is fully outside the first one ;
 * INTERSECT if the second polygon is partially inside/outside the first
 * one, in other words intersecting the second one ;
 * ENCLOSING if the first polygon is fully inside the second one ;
 * EQUAL both polygons are exactly equal.
 */

Bool inside(Polygon p1, Polygon P2);

Bool outside(Polygon p1,Polygon p2);

Bool equal(Polygon p1,Polygon p2);

Polygon centralSymmetry(Polygon p, Point a);

Bool isOnTheLine(Point p, Point a, Point b);

Bool intersectSegments(Point p1, Point p2, Point p3, Point p4, Point* i);

Polygon unionPolygons(Polygon p1, Polygon p2);

Polygon rotatePolygon(Polygon P, Point center, float angle);
/*
 * The function rotatePolygon compute, from a given polygon, center of rotation and angle, the corresponding polygon.
 * To find the new polygon, we rotate the given polygon around the center by the given angle.
 */

Bool pointsEquality(Point A, Point B);
/*
 * the function pointEquals compare the coordinates of the 2 points to find out if it's the same point (TRUE) or not (FALSE).
 * This function check if A's coordinates are between B's one +/- 0.000001 (10 to the power -6).
 */


Polygon scalePolygon(Polygon p, float factor);
/*
 * the function scalePolygon literally scale the polygon given in parameters by the factor specifiedand return the correspondind scaled polygon.
 * the coordinates of the first point stay unchanged because we scale the polygon by taking it as a stationary reference.
 */

Polygon translatePolygon(Polygon p, Point pt1, Point pt2);
/*
 * the function translatePolygon move a given polygon p by a tranlation vector, which is the one which links pt1 to pt2.
 */

void printPoint(Point pt);
/*
 * the function printPoint simply display the coordinates of a given point on the user screen. The values are approximated to 1/100.
 */


void printPolygon(Polygon p);
/*
 * the function printPolygon display a given polygon on the user's screen.
 */


char* toString(Polygon p);
    /*
     * the function toString do the same thing as the function printPolygon, but instead of displaying the polygon on the user's screen, it put it into a string, and return it
     */


Polygon convexhullPolygon( Polygon p);
    /*
     * the function convexhullPolygon compute the convex hull of a given polygon using the graham scan procedure.
     */


Polygon minY(Polygon p);
/*
 * the function minY return the same polygon, with the head pointed on the point with the lowest ordinates.
 * In cases of equality between several points, the first encountered is chosen
 */


Rot rotDir(Element* x, Element* y, Element* z);
/*
 * the function rotDir takes 3 pointers on Elements in parameter to find out if the angle between xy and yz is clockwise or counter-clockwise
 * it returns TRUE is the rotation is clockwise, and return FALSE if the rotation is counter-clockwise or if there's no rotation (3 points on the same line).
 */


Polygon sortPolygon( Polygon P);
/*
 * This function was created to sort in ascending order all the points of a polygon, according to the angle the vector linking the headpoint and them makes with the Ox-axis.
 * Without this function, the convexhullPolygon function will not work properly.
 * sortPolygon takes the polygon we want to be sorted in parameter, and return the sorted version.
 * In our softw<are, the head of the given polygon will always be the point with the lowest Y-coordinates, according to the minY function.
 */


double angleOx( Point a, Point b);
/*
 * This function takes 2 points a and b in parameter and returnthe angle between the vector (ba) and the Ox-axis..
 * angleOx is used in sortPolygon, where the returned angle is use as a sorting criteria.
 * Without, sortPolygon will not work.
 */

Element* minCoordinates(Polygon p);

#endif

