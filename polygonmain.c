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
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]){
    char c1,c2;/*, i, j*/;
    //float f;
    double x,y;
    Point pt/*, pt1, pt2*/;
    Polygon p1;
    //Polygon p2;
    Bool err1=FALSE;
    Bool err2=FALSE;
    p1=createPolygon();
    do{
        err1=FALSE;
        //i=0;
        //f=0;
        printf("0. Exit\n1. Create a point\n2. Remove a point\nYour choice :\t");
        scanf("%s", &c1);
        switch(atoi(&c1)){
            case 0:
                break;
            case 1:
                printf("Enter x : ");
                scanf("%lf",&x);
                printf("Enter y : ");
                scanf("%lf",&y);
                pt = createPoint(x,y);
                printPoint(pt);
                do{
                    err1=FALSE;
                    printf("\nWhat do you want to do with this point ?\n0. Return to menu\n1. Add this point on the current polygon\n2. Test if the point is in the current polygon\nYour choice :\t");
                    scanf("%s", &c2);
                    switch(atoi(&c2)){
                        case 0:
                            err2=FALSE;
                            break;
                        case 1:
                            p1=addPoint(p1,pt);
                            printPolygon(p1);
                            err2=FALSE;
                            break;
                        case 2:
                            if(containsPoint(p1,pt)){
                                printf("The current polygon contains the point.\n");
                                }else{
                                printf("The current polygon does not contain the point.\n");
                                }
                            err2=FALSE;
                            break;
                        default:
                            printf("Would you mind to reformulate ?\n");
                            err2=TRUE;
                            break;
                            }
                    err1=TRUE;
                }while(err2==TRUE);
                break;
            default:
                printf("Would you mind to reformulate ?");
                err1=TRUE;
        }
    }while(err1==TRUE);
    return EXIT_SUCCESS;
}

