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
    Point p;
    Polygon newPol;
    do{
        printf("1. createPoint\n2. createPolygon\n3. addPoint\n4. removePoint\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Enter x");
                scanf("x");
                printf("Enter y");
                scanf("y");
                createPoint(x,y);
            case 2:
                newPol=createPolygon();
            case 3:
                if (p!=NULL){
                    while(p!=NULL){
                        printpoint(p);
                        p->next;
                    }
                }
            default:
                printf("Would you mind to reformulate please ?");
                break;
        }

    }while(default);
    return EXIT_SUCCESS;
}

