#include "header.h"
#include "proto.h"

void rgb_to_grayscale(
 int width,
 int height,
 int *image_rgb,
 double *image_grayscale
)

{

 int i;
 int j;
 int ind;
 int r;
 int g;
 int b;
 double I_dbl;

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       ind= i*width+j;
       r= image_rgb[3*ind+0];
       g= image_rgb[3*ind+1];
       b= image_rgb[3*ind+2];

       I_dbl= (6969 * (double)r + 23434 * (double)g + 2365 * (double)b) / 32768;

       image_grayscale[ind]= I_dbl;
    }
 }

}
