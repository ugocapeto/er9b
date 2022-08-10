#include "header.h"
#include "proto.h"

void feature_build_dog_space(
 int octave_nbr,
 int interval_nbr,
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ****pdog_pyr_image
)

/*
Perform the DoG (Difference of Gaussians)
and store the resulting image
*/

{

 double ***dog_pyr_image;
 int octave;
 int width;
 int height;
 int interval;
 int i;
 int j;
 int pixel;

 dog_pyr_image= (double ***)calloc(octave_nbr,sizeof(double **));

 for ( octave= 0 ; octave< octave_nbr ; octave++ ) {
    dog_pyr_image[octave]= (double **)calloc(interval_nbr+2,sizeof(double *));
 }

 for ( octave= 0 ; octave< octave_nbr ; octave++ ) {
    width= gauss_pyr_width[octave];
    height= gauss_pyr_height[octave];
    for ( interval= 0 ; interval< interval_nbr+2 ; interval++ ) {
       dog_pyr_image[octave][interval]= (double *)calloc(width*height,sizeof(double));
       for ( i= 0 ; i< height ; i++ ) {
          for ( j= 0 ; j< width ; j++ ) {
             pixel= i*width+j;
             dog_pyr_image[octave][interval][pixel]=
              gauss_pyr_image[octave][interval+1][pixel]-
              gauss_pyr_image[octave][interval][pixel];
          }
       }
    }
 }

 (*pdog_pyr_image)= dog_pyr_image;

}
