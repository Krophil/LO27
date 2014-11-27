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
    int choice;
    double x, y;
    /*Point p;
    Polygon polygon;*/
    Bool err=FALSE;
    do{
        printf("1. createPoint\n2. createPolygon\n3. addPoint\n4. removePoint\n");
        /*polygon=createPolygon();*/
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Enter x");
                scanf("%lf",&x);
                printf("Enter y");
                scanf("%lf",&y);
                createPoint(x,y);
                err=TRUE;
                break;
            case 2:
                err=TRUE;
                break;
            /*case 3:
             *   if (p!=NULL){
             *       while(p!=NULL){
             *           printpoint(p);
             *           p->next;
             *       }
             *   }*/
            default:
                printf("Would you mind to reformulate please ?");
                break;
        }

    }while(err==FALSE);
    return EXIT_SUCCESS;
}

