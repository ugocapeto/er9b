#include "header.h"
#include "proto.h"

int feature_check_extremum_edge_like(
 int octave_nbr,
 int interval_nbr,
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 int img_border,
 int octave,
 int inp_interval,
 int inp_i,
 int inp_j
)

{

 double curv_thresh;
 int width;
 int height;
 double d;
 double dxx;
 double dyy;
 double dxy;
 double tr;
 double det;

 /*
 Set the curvature ratio threshold
 */

 curv_thresh= 10.0;

 /*
 Get the width and height for this octave
 */

 width= gauss_pyr_width[octave];
 height= gauss_pyr_height[octave];

 /*
 Compute the principal curvatures
 using the trace and determinant of the Hessian
 */

 d= dog_pyr_image[octave][inp_interval][inp_i*width+inp_j];

 /*
 Compute derivative w/r to xx
 */

 dxx= dog_pyr_image[octave][inp_interval][inp_i*width+inp_j+1]+
      dog_pyr_image[octave][inp_interval][inp_i*width+inp_j-1]-2*d;

 /*
 Compute derivative w/r to yy
 */

 dyy= dog_pyr_image[octave][inp_interval][(inp_i+1)*width+inp_j]+
      dog_pyr_image[octave][inp_interval][(inp_i-1)*width+inp_j]-2*d;

 /*
 Compute derivative w/r to xy
 */

 dxy= (dog_pyr_image[octave][inp_interval][(inp_i+1)*width+inp_j+1]-
       dog_pyr_image[octave][inp_interval][(inp_i+1)*width+inp_j-1]-
       dog_pyr_image[octave][inp_interval][(inp_i-1)*width+inp_j+1]+
       dog_pyr_image[octave][inp_interval][(inp_i-1)*width+inp_j-1])/4;

 tr= dxx+dyy;
 det= dxx*dyy-dxy*dxy;

 if ( det <= 0 ) {

    /*
    Curvatures have different signs
    */

    /*
    We are gonna have to reject this feature
    */

    return 1;
 }

 if ( (tr*tr/det) < (curv_thresh+1.)*(curv_thresh+1.)/curv_thresh ) {

    /*
    The ratio of principal curvatures is below threshold
    */

    /*
    We are gonna have to accept this feature
    */

    return 0;
 }

 /*
 If here,
 the ratio of principal curvature is above threshold
 */

 /*
 We are gonna have to reject this feature
 */

 return 1; 

}
