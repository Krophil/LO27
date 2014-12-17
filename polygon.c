/*
 * Pierre Brunet
 * pierre.brunet-de-monthelie@utbm.fr
 *
 * Guillaume Prost
 * guillaume.prost@utbm.fr
 *
 * Subject : 2D polygon library
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <polygon.h>
#include <math.h>
#include <string.h>


int main(int argc, char* argv[]){

    return EXIT_SUCCESS;
}

Point createPoint(double a, double b){
    Point* p;
    p=(Point *) malloc(sizeof(Point));
    p->x=a;
    p->y=b;
    return *p;
}

Polygon createPolygon(){
    Polygon p;
    p.head=NULL;
    p.N=0;
    return p;
}

Polygon addPoint(Polygon a, Point b){
    Element* B = (Element *)malloc(sizeof(Element));
    B->point = b;
    if(a.N==0){
        B->prev = a.head;
        B->next = a.head;
        a.head = B;
    }else if(a.N==1){
        B->prev = a.head;
        B->next = a.head;
        a.head->next = B;
        a.head->prev = B;
    }else{
        B->prev=a.head->prev;
        B->next=a.head;
        B->prev->next = B;
        B->next->prev = B;
    }
    a.N++;
    return a;
}

Polygon removePoint(Polygon p, int i){
    int j;
    Element* supp;
    supp=p.head;


    if(p.N>=0){
        if (i==1){
            p.head->next=p.head;
            p.head->prev->prev->next=p.head;
        }
        for(j=0;j<i;j++){
            supp=p.head->next;
        }
    supp->prev->next=supp->next;
    supp->next->prev=supp->prev;
    free(supp);
    }
    return p;
}

Polygon unionPolygons(Polygon p, Polygon q){
    Polygon r = createPolygon();
    Element* i=p.head;
    Element* j=q.head;
    Point* intersect;
    State status=containsPolygon(p,q);
    intersect=NULL;
    if(status==INSIDE || status==ENCLOSING){
        do{
            r=addPoint(r,i->point);
            i=i->next;
        } while(i!=NULL);
        i=q.head;
        r=addPoint(r,i->point);
        do{
            r=addPoint(r,i->point);
            i=i->next;
        } while(i!=NULL);
    }else if(status==SAMESHAPE){
        if(p.N>=q.N){
            r=p;
        }else{
            r=q;
        }
    }else if (status==INTERSECT){
        i=minCoordinates(p);
        addPoint(r, i->point);
        if (intersectSegments(i->point,i->next->point,j->point,j->next->point, intersect)){
            addPoint(r, (*intersect));
            if(j->next->point.x>=j->point.x){
                j=i;
                i->point=*intersect;
            }else{

            }
        }
    }
    return r;
}

Bool containsPoint(Polygon p, Point point){
    int intersect, i;
    Element* testa;
    Element* testb;
    Bool line, isIn;
    intersect=0;
    /*intersect represents the number of intersections between the ray of the testing point
     * and the different sides of the polygon
     */
    testa=p.head;
    testb=p.head->prev;
    /*testa and testb are two consecutive points in the polygon
     */
    if (p.N<3){
        return FALSE;
    }else{
        for (i=0;i<p.N;i++){/*p.N is the number of points in the polygon*/
            if((testa->point.y<point.y && testb->point.y>=point.y) || (testb->point.y<point.y && testb->point.y>=point.y)){
                /*tests if the Y-coordinate of the point is between the both Y-coordinates of a and b
                 */
                testb=testa;
                testa=testa->next;
            }else if(testa->point.x+((point.y-testa->point.y)/(testb->point.y-testa->point.y))*(testb->point.x-testa->point.x)<=point.x){
                /*calculates the X-coordinate intersection between the ray of the testing point and the segment between point a and point b
                 * if X>=Xintersec, it means there is an intersection
                 */
                intersect++;
                testb=testa;
                testa=testa->next;
            }
            isIn=intersect%2;
            line=isOnTheLine(point,testa->point,testb->point);
        }
        return isIn||line;
    }
}

State containsPolygon(Polygon p1, Polygon p2){
    if (inside(p1,p2)){
        if(equal(p1,p2)){
            return EQUAL;
        }
        else if(inside(p2,p1)){
            return SAMESHAPE;
                }
        return INSIDE;
    }
    else if(outside(p1,p2)){
            if (inside(p2,p1)){
                return ENCLOSING;
            }else{
                return OUTSIDE;
        }
    }
    return INTERSECT;
}


Bool inside(Polygon p1, Polygon p2){
    if(p1.N==p2.N){
        Element* test=p2.head;
        Bool isInside=TRUE;
        int i=0;
        do{
            isInside=containsPoint(p1,test->point);
            test=test->next;
            i++;
        }while(isInside==TRUE && i<p1.N);
        return isInside;
    }else{
        return FALSE;
    }
}

Bool outside(Polygon p1, Polygon p2){
    Element* test=p2.head;
    Bool isInside=TRUE;
    int i=0;
    do{
        isInside=containsPoint(p2,test->point);
        test=test->next;
        i++;
    }while(isInside==FALSE && i<p1.N);
    return !isInside;
}

Bool equal(Polygon p1, Polygon p2){
    Element* a;
    Element* b;
    Bool same;
    int i=0;
    a=p1.head;
    b=p2.head;
    do{
        if(a->point.x==b->point.x && a->point.y==b->point.y){
            same=TRUE;
        }
        b=b->next;
        i++;
    }while(same==FALSE && i<p2.N);
    if(same==TRUE){
        b=b->prev;
        same=FALSE;
        i=0;
        do{
            if(a->point.x==b->point.x && a->point.y==b->point.y){
                same=TRUE;
                a=a->next;
                b=b->next;
                i++;
            }else{
                same=FALSE;
            }
        }while(same==TRUE && i<p2.N);
    }
    return same;

}

Bool isOnTheLine(Point p, Point a, Point b){
    Point vectA,vectB;
    Bool line=FALSE;
    vectA.x=p.x-a.x;
    vectA.y=p.y-a.y;
    vectB.x=b.x-a.x;
    vectB.y=b.y-a.y;
    if(vectA.x*vectB.y-vectB.x*vectB.y==0){
        if((p.x<=a.x && p.y<=a.y && p.y>=b.y && a.y>=b.y)||(p.x>=a.x && p.y>=a.y && p.y<=b.y && a.y<=b.y)){
            line=TRUE;
                }
            }
    return line;
}

Polygon centralSymmetry(Polygon p, Point a){
    Polygon newPol= createPolygon();
    Element* cr=p.head;
    Point point;
    int i;
    do{
        point.x=2*a.x-cr->point.x;
        point.y=2*a.x-cr->point.y;
        newPol=addPoint(newPol,point);
        i++;
    }while(i<p.N);
    return newPol;
}

Bool intersectSegments(Point p1, Point p2, Point p3, Point p4, Point* i){
    Point s1,s2;
    double s, t;
    s1.x=p2.x-p1.x;
    s1.y=p2.y-p1.y;
    s2.x=p4.x-p3.x;
    s2.y=p4.y-p3.y;
    s = (-s1.y*(p1.x-p3.x)+s1.x*(p1.y-p3.y))/(-s2.x*s1.y+s1.x*s2.y);
    t = ( s2.x*(p1.y-p3.y)-s2.y*(p1.x-p3.x))/(-s2.x*s1.y+s1.x*s2.y);

    if((s>=0)&&(s<=1)&&(t>=0)&&(t<=1)){ /* Collision detected */
        if (i!=NULL){
            i->x=p1.x+(t*s1.x);
            i->y=p1.y+(t*s1.y);
        }
        return TRUE;
    }else{
        return FALSE; /* No collision */
    }
}


Polygon rotatePolygon(Polygon p, Point center, float angle){
    /*
     * tempi : integer, used as the iteration variable of a for-loop
     * xr, yr : doubles, respectivly the coordinates of the new rotated point on the x-axis and the y-axis
     * temp1 : double, store the value of an angle
     * temp2: double, store the value of the norm of a vector
     * protated : Polygon, correspond to the rotated version of the initail polygon
     * temppt : Point, temporarly store the current coordinates of the newly rotated point
     */
    int tempi;
    double xr, yr, temp1, temp2;
    Polygon protated = createPolygon();
    Point temppt;

/* this for-loop is used for taking every single points of the initial polygon */
    for(tempi = 0; tempi < p.N; tempi++){

    /* if the polygon is not empty */
        if( p.N != 0){

      /* we check if the current point and the center of the rotation are equals. If it's the case, applying the rotation algorithm is pointless. */
             if( pointsEquality( p.head->point, center )){

             }
             else{

                /* first of all, we compute the value of the angle between the x-axis and the vector linking the center to the current point of the polygon. */
                  temp1 = atan( ( p.head->point.y - center.y) / (p.head->point.x - center.x) - angle );

                /* Then we compute the norm of this vector */
                  temp2 = sqrt( pow(( p.head->point.x - center.x),2) + pow(( p.head->point.y - center.y ),2) );

                /* we calculate the coordinates of the new rotated point */
                  xr = temp2 + cos(temp1) + center.x;
                  yr = temp2 + sin(temp1) + center.y;

                /* we create this point with the coordinates we've found before */
                  temppt = createPoint(xr, yr);

                /* we add this point to the polygon which will contains the rotated points */
                  protated = addPoint( protated, temppt);



              }



        }

        /* and we place the 'head' pointer of the initial polygon on the next point */
                  p.head = p.head->next;
    }

    return protated;
}


Bool pointsEquality( Point A, Point B){

/* equals : boolean, TRUE is the two points are equals, FALSE otherwise */
    Bool equals = FALSE;

/* i : integer, iteration variable for a fro-loop */
    int i;

/* pt1, pt2 : array of caracters, respecctivly store the strings corresponding to the first and the second points given in parameters */
    char* pt1 = (char*) malloc(25*sizeof(char));
    char* pt2 = (char*) malloc(25*sizeof(char));

/* this for-loop initialize the array of caracters by putting in every place a space */
    for(i=0; i<24; i++){
        pt1[i] = ' ';
        pt2[i] = ' ';
    }

/* store the coordinates of the 2 points given in the 2 arrays. the x and y coordinates are separeted by a coma. */
    sprintf( pt1, "%.5f,%.5f", A.x, A.y);
    sprintf( pt2, "%.5f,%.5f", B.x, B.y);

/* the function strcmp return 0 if the 2 strings are strictly identicals */
    if(strcmp(pt1, pt2)==0){
        equals = TRUE;
    }

    return equals;

}


Polygon scalePolygon(Polygon p, float factor){

/*
 * i : integer, iteration variable for a for-loop
 * temppt : Point, store the coordinates of the current point of the polygon, which change with each iteration of the for-loop
 * ref : Point, store the coordinates of the first point of the polygon, which will act a the stationary reference
 * pscaled : Polygon, store the scaled version of the polygon given in parameter
 */
    int i;
    Point temppt;
    Point ref = p.head->point;
    Polygon pscaled = createPolygon();

/* if the polygon have a least 1 point */
    if(p.N > 0){
        /* we add the first point of the initial polygon (the reference) to the scaled polygon without changing anything */
        addPoint(pscaled, p.head->point);

        /* if there's more than 1 single point in the polygon */
        if(p.N > 1){

            /* from the 2nd point to the last point of the polygon */
            for(i=1;  i<p.N-1; i++){
                /* we take the next point in the initial polygon */
                    p.head = p.head->next;
                /* we scale the vector linking the ref-point to the current point by the given factor and we store the new coordinates in the temporary Point-type variable */
                    temppt = createPoint( (p.head->point.x - ref.x)*factor + ref.x , (p.head->point.y - ref.y)*factor + ref.y );
                /* then we add this point to the scaled version of the polygon */
                    addPoint(pscaled, temppt);

            }
        }
    }

    return pscaled;

}


Polygon translatePolygon(Polygon p, Point pt1, Point pt2){

    int i;
    Point temppt;
    Point tvect = createPoint( pt2.x - pt1.x , pt2.y - pt1.y );
    Polygon ptranslated = createPolygon();

    if( p.N > 0){

        for(i=0; i < p.N; i++){

            temppt = createPoint(p.head->point.x + tvect.x, p.head->point.y + tvect.y);
            ptranslated = addPoint( ptranslated, temppt);
            p.head = p.head->next;

        }
    }

    return ptranslated;
}


void printPoint(Point pt){

    printf("[%.2f,%.2f]", pt.x, pt.y);

}


void printPolygon(Polygon p){

    /*
     * i : integer, iteration value for a for-loop
     */
    int i;
    if(p.N > 0){

        /* we start by prompting an opening bracket and the first point of the polygon */
        printf("[");
        printPoint(p.head->point);

        if(p.N >1){
            /* after that, for each point of the polygon, we display it on the user's screen, separeted from the previous point by a coma */
            for(i = 1; i<= p.N-1; i++){

              printf(",");
              p.head = p.head->next;
              printPoint(p.head->point);

            }
        }

         /* finaly, we put and ending bracket */
         printf("]\n");
    }
}


char* toString(Polygon p){

    /*
     * i : integer, size of the string that we'll return at the end of this function
     * j : integer, iteration value for a for-loop
     * index : integer, total length of all already-stored characters
     */
    int i = 100, j;
    int index;

    /*
     * firstpt : boolean, TRUE if the current point is the first, FALSE otherwise
     * buffer : string, store the differents coordinates of all points of the given polygon. have a size of i characters
     */
    Bool firstpt = TRUE;
    char* buffer = (char*) malloc(i*sizeof(char));

    index = sprintf( buffer, "[");

    /* for every single point of the polygon */
    for( j=0; j < p.N-1; j++){

        /* if it's the first loop, so the first point */
        if(firstpt == TRUE){
            firstpt = FALSE;
        }
        else{
            /* if it's not the first loop, we put a coma before the next point */
            index = sprintf( buffer, "%s,", buffer);
        }

        /* we add the next point to the string */
        index = sprintf( buffer, "%s[%.2f,%.2f]", buffer, p.head->point.x, p.head->point.y);

        /* and we take the next one */
        p.head = p.head->next;


        /* if there's less than 30 empty spaces remaining in the string */
        if( i - index <= 30){

            /* we add 30 more empty spaces to this string. It's only here to avoid any overflow */
            i = i + 30;
            buffer = realloc(buffer, i*sizeof(char));
        }

    }

    index = sprintf( buffer, "%s]", buffer);

    return buffer;
}


Polygon convexhullPolygon( Polygon p){

    Element*  fstpt = p.head;
    Element* x;
    Element* y;
    Element* z;
    Polygon chp = createPolygon();

    if(p.N > 0){

        if(p.N == 1 || p.N == 2){

            p.head = p.head->next;

            while( p.head != fstpt){

                chp = addPoint(chp, p.head->point);
                p.head = p.head->next;

            }
        }
        else{

            p = minY(p);

            fstpt = p.head;

            do{
                x = p.head;
                y = p.head->next;
                z = p.head->next->next;

                if( rotDir(x, y, z) == CLOCKWISE){

                        chp = addPoint( chp, y->point);
                        x = x->next;
                        y = y->next;
                        z = z->next;
                }
                else{

                    y = y->next;
                    z = z->next;
                    }
                 }while(pointsEquality(y->point, fstpt->point)==FALSE);

            }
        }
        return chp;
}


Polygon minY(Polygon p){

    int i;
    Element* minimumy = p.head;

    for(i=0; i<p.N-1; i++){

        p.head = p.head->next;

        if(p.head->point.y < minimumy->point.y  || ( p.head->point.y <= minimumy->point.y && p.head->point.x < minimumy->point.x ) ){

            minimumy = p.head;

        }

    }

    while( p.head != minimumy ){

        p.head = p.head->next;

    }

    return p;

}



Rot rotDir(Element* x, Element* y, Element* z){

    Rot rotation;
    double scalarproduct = (y->point.x - x->point.x)*(z->point.y - x->point.y ) - (y->point.y - x->point.y)*(z->point.x - x->point.x);

    if( scalarproduct > 0){

        rotation = CLOCKWISE;
    }
    else{
        if( scalarproduct < 0){

            rotation = ANTICLOCKWISE;
        }
        else{

            rotation = NONE;
        }
    }

    return rotation;

}

Element* minCoordinates(Polygon p){
    int i;
    Element* mini = p.head;
    Element* test = p.head;

    for(i=0; i<p.N; i++){
        if(test->point.x+test->point.y<mini->point.x+mini->point.y){
            mini = test;
        }
        test = test->next;
    }

    return mini;
}


