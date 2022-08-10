#include "header.h"
#include "proto.h"

void feature_dog_deriv(
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 int octave,
 int interval,
 int i,
 int j,
 double deriv[3]
)

{

 int width;
 int height;
 double dx;
 double dy;
 double ds;

 width= gauss_pyr_width[octave];
 height= gauss_pyr_height[octave];

 /*
 Compute derivative w/r to x
 */

 dx= (dog_pyr_image[octave][interval][i*width+j+1]-
      dog_pyr_image[octave][interval][i*width+j-1])/2;

 /*
 Compute derivative w/r to y
 */

 dy= (dog_pyr_image[octave][interval][(i+1)*width+j]-
      dog_pyr_image[octave][interval][(i-1)*width+j])/2;

 /*
 Compute derivative w/r to s
 */

 ds= (dog_pyr_image[octave][interval+1][i*width+j]-
      dog_pyr_image[octave][interval-1][i*width+j])/2;

 deriv[0]= dx;
 deriv[1]= dy;
 deriv[2]= ds;

}
