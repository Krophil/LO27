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
  }

void printPoint(int i){
    printf("test");
}

Bool containsPolygon(Polygon p, Point point){
    Bool oddNodes=0;
    int i;
    Element* testa=p.head;
    Element* testb=p.head->prev;
    if (p.N<3){
        return FALSE;
    }else{
        for(i=0;i<p.N;i++){
            if(testa->point.y<point.y && testb->point.y>=point.y || testb->point.y<point.y && testa->point.y>=point.y){
                if(testa->point.x+(point.y+testa->point.y)/(testb->point.y-testa->point.y)*(testb->point.x-testa->point.x)<point.x){
                    oddNodes= !oddNodes;
                }
            }
        testb=testa;
        testa=testa->next;
        }
}
return oddNodes;
}
