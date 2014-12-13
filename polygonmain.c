/*
 * Pierre Brunet
 * pierre.brunet-de-monthelie@utbm.fr
 *
 * Guillaume Prost
 * guillaume.prost@utbm.fr
 *
 * Subject : Interface for the 2D polygon library
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <polygon.h>
#include <string.h>

int main(int argc, char* argv[]){
    int choice, i, j;
    float f;
    double x, y;
    Point pt,pt1,pt2;
    Polygon p;
    Bool err=FALSE;
    do{
        err = FALSE;
        i = 0;
        f = 0;
        printf("0.exit\n1. createPoint\n2. createPolygon\n3. addPoint\n4. removePoint\n5.scalePolygon\n6.rotatePolygon\n7.translatePolygon\n8.printPoint\n9.printPolygon\n");
        /*polygon=createPolygon();*/
        scanf("%d", &choice);
        switch(choice){
            case 0:
                break;
            case 1:
                printf("Enter x");
                scanf("%lf",&x);
                printf("Enter y");
                scanf("%lf",&y);
                pt = createPoint(x,y);
                err=TRUE;
                break;
            case 2:
                p = createPolygon();
                err=TRUE;
                break;
            case 3:
                 p = addPoint(p,pt);
                 err = TRUE;
                 break;
            case 4:
                 printf("point No ? \t");
                 scanf("%d", &i);
                 p = removePoint(p, i);
                 err = TRUE;
                 break;
            case 5:
                 printf("please specify the scaling factor : \t");
                 scanf("%f", &f);
                 p = scalePolygon(p, f);
                 err = TRUE;
                 break;
            case 6:
                 printf("rotation of ?(rad)\t");
                 scanf("%f", &f);
                 printf("Around which point ?\n x?\t");
                 scanf("%lf", &x);
                 printf("y?\t");
                 scanf("%lf", &y);

                 pt = createPoint(x, y);

                 p = rotatePolygon(p, pt, f);

                 err = TRUE;
                 break;
            case 7:
                 printf("first point :\n");
                 printf("Enter x");
                 scanf("%lf",&x);
                 printf("Enter y");
                 scanf("%lf",&y);
                 pt1 = createPoint(x,y);

                 printf("second point :\n");
                 printf("Enter x");
                 scanf("%lf",&x);
                 printf("Enter y");
                 scanf("%lf",&y);
                 pt2 = createPoint(x,y);
                 p = translatePolygon(p, pt1, pt2);
                 err = TRUE;
                 break;
            case 8:
                 printf("point No ?\t");
                 scanf("%d", &i);

                 for( j=0 ; j<i-1 ; j++){

                     p.head = p.head->next;
                 }

                 printPoint(p.head->point);

                 err = TRUE;
                 break;
            case 9:
                 printPolygon(p);
                 err = TRUE;
                 break;




            default:
                printf("Would you mind to reformulate please ?");
                err = TRUE;
                break;
        }

    }while(err==TRUE);

    pt.x++;

    return EXIT_SUCCESS;
}

