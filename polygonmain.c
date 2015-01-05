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
    Point pt, pt1, pt2;
    Polygon p1;
    Polygon p2;
    Polygon p3;
    Bool err1=FALSE;
    Bool err2=FALSE;
    /*Bool err3=FALSE;*/
    Bool err4=TRUE;
    Bool polComplete=FALSE;
    Bool testPoint;
    int test;
    int i;
    Element* elem;

    p1=createPolygon();

    do{
        err1=FALSE;
        //i=0;
        //f=0;
        printf("\n0. Exit\n1. Create a polygon\nYour choice :\t");
        scanf("%s", &c1);
        switch(atoi(&c1)){
            case 0:
                err1=FALSE;
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
                        printf("\nWhat do you want to do with this point ?\n0. Exit\n1. Add this point on the current polygon\n2. Rewrite this point\nYour choice :\t");
                        scanf("%s", &c2);

                        switch(atoi(&c2)){
                            case 0:
                                err2=FALSE;
                                err1=FALSE;
                                err4=FALSE;
                                polComplete=TRUE;
                                break;
                            case 1:
                                p1=addPoint(p1,pt);
                                printPolygon(p1);
                                err2=FALSE;
                                err1=TRUE;
                                err4=TRUE;
                                polComplete=FALSE;
                                if(p1.N>2){
                                    printf("Is your polygon complete ? Y or N\n");
                                    scanf("%s",&c2);
                                    if(c2=='Y'||c2=='y'){
                                        if(p1.N>=3){
                                            polComplete=TRUE;
                                        }
                                    }
                                }
                                break;
                            case 2:
                                polComplete=FALSE;
                                printf("Enter x : ");
                                scanf("%lf",&x);
                                printf("Enter y : ");
                                scanf("%lf",&y);
                                pt= createPoint(x, y);
                                err2=TRUE;
                                err1=TRUE;
                                break;
                            default:
                                printf("Would you mind to reformulate ?\n");
                                err2=TRUE;
                                err1=TRUE;
                                break;
                            }
                    }while(err2==TRUE);
                }while(polComplete==FALSE);
                do{
                if (polComplete && err4==TRUE){
                    printPolygon(p1);
                    printf("What do you want to do ?\n0. Exit\n1. Create a second polygon and manipulate both;\n2. Just create a point and check if it is in or out of the polygon;\n3. Translate this polygon from a point to another;\n4. Rotate this polygon around a point;\n5. Scale this polygon by a given factor;\n6. Compute the corresponding convex hull;\n7. Do a central symmetry\nYour choice :\t");
                    scanf("%s",&c1);
                    switch(atoi(&c1)){
                        case 0:
                            err4=FALSE;
                            err1=FALSE;
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
                                if(p2.N>2){
                                    printf("Is your polygon complete ? Y or N\t");
                                    scanf("%s",&c1);
                                    if(c1=='Y'||c1=='y'){
                                        printf("Here we have the two polygons :\n");
                                        printPolygon(p1);
                                        printPolygon(p2);
                                        printf("What do you want to do with these polygons ?\n1. How are those two polygons ?\n2. Let's assembly them !\nYour choice :\t");
                                        scanf("%s",&c1);
                                        switch(atoi(&c1)){
                                            case 1:
                                                switch(containsPolygon(p1,p2)){
                                                    case 1:
                                                        printf("The first polygon is inside the second one.");
                                                        break;
                                                    case 2:
                                                        printf("The polygons have nothing in common except a dimension.");
                                                        break;
                                                    case 3:
                                                        printf("The polygons cross each other.");
                                                        break;
                                                    case 4:
                                                        printf("The second polygon is inside the first one.");
                                                        break;
                                                    case 5:
                                                        printf("The polygons are exactly the same.");
                                                        break;
                                                    case 6:
                                                        printf("They seems to be the same but there are few differences with the points");
                                                        break;
                                                    case 7:
                                                        printf("There is a problem with the polygons, maybe they are not real polygons.");
                                                        break;
                                                }
                                                err4=FALSE;
                                                break;

                                            case 2:
                                                printf("test");
                                                p3=unionPolygons(p1,p2);
                                                printf("Here is your polygon, union of the two polygons :\n");
                                                printPolygon(p3);
                                                err4=TRUE;
                                                break;

                                            default:
                                                printf("Would you mind to reformulate ?");
                                                err4=TRUE;

                                            }
                                        err2=FALSE;
                                    }
                                }
                            }while(err2==TRUE);
                            err4=TRUE;
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
                            err4=TRUE;
                            break;
                        case 3:

                            printf("starting point :\n\t Enter x : ");
                            scanf("%lf",&x);
                            printf("\n\tEnter y : ");
                            scanf("%lf",&y);
                            pt1 = createPoint(x, y);

                            printf("ending point :\n\t Enter x : ");
                            scanf("%lf",&x);
                            printf("\n\tEnter y : ");
                            scanf("%lf",&y);
                            pt2 = createPoint(x, y);

                            p1 = translatePolygon(p1, pt1, pt2);
                            err4=TRUE;
                        break;

                        case 4:

                            printf("Do you want to rotate the polygon around one of its point, or around another point?\n\t1. One of its point;\n\t2. Another point;\n Your choice : ");
                            scanf("%s",&c1);
                            switch(atoi(&c1)){
                                    case 1:
                                            elem = p1.head;
                                            printf("Please give us its number (the first point's number is 1, the second is 2, and so on....) : ");
                                            scanf("%d", &i);

                                            if(i == 1){
                                                pt1 = p1.head->point;
                                            }else{
                                                for(i = i;i>1; i--){
                                                    elem = elem->next;
                                                }
                                                pt1 = elem->point;
                                            }

                                    break;

                                    case 2:

                                            printf("Please enter the coordinates of this point :\n\t Enter x : ");
                                            scanf("%lf",&x);
                                            printf("\n\tEnter y : ");
                                            scanf("%lf",&y);
                                            pt1 = createPoint(x, y);
                                    break;
                            }

                            printf("Enter the angle of the rotation, in radian : ");
                            scanf("%lf", &x);

                            p1 = rotatePolygon(p1, pt1, x);
                            err4=TRUE;
                        break;

                        case 5:
                            printf("Enter the factor, which can be any real number : ");
                            scanf("%lf", &x);

                            p1 = scalePolygon(p1, x);
                            err4=TRUE;
                        break;

                        case 6:

                            p1 = convexhullPolygon(p1);
                            err4=TRUE;
                        break;

                        case 7:
                            printf("Which point do you want for the central symmetry ?\n");
                            printf("Enter x :\t");
                            scanf("%lf", &x);
                            printf("Enter y :\t");
                            scanf("%lf", &y);
                            pt1=createPoint(x,y);
                            p1=centralSymmetry(p1,pt1);
                            err4=TRUE;
                        break;

                        default:
                            printf("Would you mind to reformulate ?\n");
                            err4=TRUE;


                    }
                }
                }while (err4==TRUE);
                break;
            default:
                printf("Would you mind to reformulate ?\n");
                err1=TRUE;
        }
    }while(err1==TRUE);
    return EXIT_SUCCESS;
}

