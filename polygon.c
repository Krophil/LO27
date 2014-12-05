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
    Element B;
    B.point = b;

    if(a.N==0){
        a.head->point = b;
        a.head->prev = a.head;
        a.head->next = a.head;
    }
    else{
        B.prev=a.head->prev;
        B.next=a.head;
        a.head->prev=&B;
    }
    a.N++;
    return a;
}

Polygon removePoint(Polygon p, int i){
    int j;
    Element* supp;
    supp=p.head;
    if (i==1)
    {
        p.head->next=p.head;
        p.head->prev->prev->next=p.head;
    }


    if(p.N!=0){
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
return r;
}

void printPoint(int i){
    printf("test");
}

/*Bool containsPoint(Polygon p, Point point){
    Bool oddNodes=0;
    int i;
    Element* testa=p.head;
    Element* testb=p.head->prev;
    if (p.N<3){
        return FALSE;
    }else{
        for(i=0;i<p.N;i++){
            if(testa->point.y<point.y && testb->point.y>=point.y || testb->point.y<point.y && testa->point.y>=point.y){
                if(testa->point.x+(point.y-testa->point.y)/(testb->point.y-testa->point.y)*(testb->point.x-testa->point.x)<point.x){
                    oddNodes= !oddNodes;
                }
            }
        testb=testa;
        testa=testa->next;
        }
}
return oddNodes;
}*/

Bool containsPoint(Polygon p, Point point){
    int intersect=0, i;
    /*intersect represents the number of intersections between the ray of the testing point
     * and the different sides of the polygon
     */
    Element* testa=p.head;
    Element* testb=p.head->prev;
    Bool line, isIn;
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
    a=p1.head;
    b=p2.head;
    int i=0;
    Bool same;
    do{
        if(a->point.x=b->point.x && a->point.y==b->point.y){
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
            if(a->point.x=b->point.x && a->point.y==b->point.y){
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
    vectA.x=p.x-a.x;
    vectA.y=p.y-a.y;
    vectB.x=b.x-a.x;
    vectB.y=b.y-a.y;
    Bool line=FALSE;
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


