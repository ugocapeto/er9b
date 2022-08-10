#include "header.h"
#include "proto.h"

void feature_dog_hessian(
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 int octave,
 int interval,
 int i,
 int j,
 double hessian[3*3]
)

{

 int width;
 int height;
 double v;
 double dxx;
 double dyy;
 double dss;
 double dxy;
 double dxs;
 double dys;

 width= gauss_pyr_width[octave];
 height= gauss_pyr_height[octave];

 v= dog_pyr_image[octave][interval][i*width+j];

 /*
 Compute derivative w/r to xx
 */

 dxx= dog_pyr_image[octave][interval][i*width+(j+1)]+
      dog_pyr_image[octave][interval][i*width+(j-1)]-2*v;

 /*
 Compute derivative w/r to yy
 */

 dyy= dog_pyr_image[octave][interval][(i+1)*width+j]+
      dog_pyr_image[octave][interval][(i-1)*width+j]-2*v;

 /*
 Compute derivative w/r to ss
 */

 dss= dog_pyr_image[octave][interval+1][i*width+j]+
      dog_pyr_image[octave][interval-1][i*width+j]-2*v;

 /*
 Compute derivative w/r to xy
 */

 dxy= (dog_pyr_image[octave][interval][(i+1)*width+(j+1)]-
       dog_pyr_image[octave][interval][(i+1)*width+(j-1)]-
       dog_pyr_image[octave][interval][(i-1)*width+(j+1)]+
       dog_pyr_image[octave][interval][(i-1)*width+(j-1)])/4;

 /*
 Compute derivative w/r to xs
 */

 dxs= (dog_pyr_image[octave][interval+1][i*width+(j+1)]-
       dog_pyr_image[octave][interval+1][i*width+(j-1)]-
       dog_pyr_image[octave][interval-1][i*width+(j+1)]+
       dog_pyr_image[octave][interval-1][i*width+(j-1)])/4;

 /*
 Compute derivative w/r to ys
 */

 dys= (dog_pyr_image[octave][interval+1][(i+1)*width+j]-
       dog_pyr_image[octave][interval+1][(i-1)*width+j]-
       dog_pyr_image[octave][interval-1][(i+1)*width+j]+
       dog_pyr_image[octave][interval-1][(i-1)*width+j])/4;

 hessian[0*3+0]= dxx;
 hessian[0*3+1]= dxy;
 hessian[0*3+2]= dxs;
 hessian[1*3+0]= dxy;
 hessian[1*3+1]= dyy;
 hessian[1*3+2]= dys;
 hessian[2*3+0]= dxs;
 hessian[2*3+1]= dys;
 hessian[2*3+2]= dss;

}
