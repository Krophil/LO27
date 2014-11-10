/*
 * Pierre Brunet
 * pierre.brunet-de-monthelie@utbm.fr
 *
 * Subject :
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <polygon.h>

int main(int argc, char* argv[]){

    return EXIT_SUCCESS;
}

point createPoint(double a, double b){
    point* p;
    p=(point *) malloc(sizeof(point));
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

Polygon addPoint(Polygon a, point b){
    elem B;
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
    elem* supp;
    supp=p.head;
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


