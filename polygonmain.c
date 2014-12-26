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
    Polygon p2;
    Bool err1=FALSE;
    Bool err2=FALSE;
    Bool polComplete=FALSE;
    Bool testPoint;
    int test;
    p1=createPolygon();
    do{
        err1=FALSE;
        //i=0;
        //f=0;
        printf("\n0. Exit\n1. Create a polygon\nYour choice :\t");
        scanf("%s", &c1);
        switch(atoi(&c1)){
            case 0:
                break;
            case 1:
                do{
                    printf("Enter x : ");
                    scanf("%lf",&x);
                    printf("Enter y : ");
                    scanf("%lf",&y);
                    pt = createPoint(x,y);
                    printPoint(pt);
                    do{
                        err1=FALSE;
                        printf("\nWhat do you want to do with this point ?\n0. Return to menu\n1. Add this point on the current polygon\n2. Rewrite this point\nYour choice :\t");
                        scanf("%s", &c2);
                        switch(atoi(&c2)){
                            case 0:
                                err2=FALSE;
                                break;
                            case 1:
                                p1=addPoint(p1,pt);
                                printPolygon(p1);
                                err2=FALSE;
                                printf("Is your polygon complete ? Y or N\n");
                                scanf("%s",&c2);
                                if(c2=='Y'||c2=='y'){
                                    if(p1.N>=3){
                                        polComplete=TRUE;
                                    }
                                }
                                break;
                            case 2:
                                printf("Enter x : ");
                                scanf("%lf",&x);
                                printf("Enter y : ");
                                scanf("%lf",&y);
                                pt= createPoint(x, y);
                                err2=TRUE;
                                break;
                            default:
                                printf("Would you mind to reformulate ?\n");
                                err2=TRUE;
                                break;
                            }
                        err1=TRUE;
                    }while(err2==TRUE);
                }while(polComplete==FALSE);
                if (polComplete){
                    printf("What do you want to do ?\n1. Create a second polygon and manipulate both\n2. Just create a point and check if it is in or out of the polygon\nYour choice :\t");
                    scanf("%s",&c1);
                    switch(atoi(&c1)){
                        case 0:
                            break;
                        case 1:
                            err2=TRUE;
                            p2=createPolygon();
                            do{
                                printf("\nEnter x : ");
                                scanf("%lf",&x);
                                printf("Enter y : ");
                                scanf("%lf",&y);
                                pt=createPoint(x,y);
                                p2=addPoint(p2,pt);
                                printPolygon(p2);
                                printf("Is your polygon complete ? Y or N\t");
                                scanf("%s",&c1);
                                if(c1=='Y'||c1=='y'){
                                    printf("%d\n",containsPolygon(p1,p2));
                                    err2=FALSE;
                                }
                            }while(err2==TRUE);
                            break;
                        case 2:
                            do{
                            printf("Enter x : ");
                            scanf("%lf",&x);
                            printf("Enter y : ");
                            scanf("%lf",&y);
                            pt=createPoint(x,y);
                            testPoint=containsPoint(p1,pt);
                            if(testPoint){
                                printf("in\n");
                            }else{
                                printf("out\n");
                            }
                            scanf("%d",&test);
                            }while(test);
                            break;

                    }
                }
                break;
            default:
                printf("Would you mind to reformulate ?");
                err1=TRUE;
        }
    }while(err1==TRUE);
    return EXIT_SUCCESS;
}

