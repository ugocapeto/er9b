#include "header.h"
#include "proto.h"

void feature_interpolate_extremum_location(
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 int octave,
 int inp_interval,
 int inp_i,
 int inp_j,
 double *pxinterval,
 double *pxi,
 double *pxj,
 double *pxdog
)

{

 double deriv[3];
 double hessian[3*3];
 double hessian_inv[3*3];
 double temp_vec[3];
 double xinterval;
 double xi;
 double xj;
 double x[3];
 double temp_val;
 int width;
 int height;
 double xdog;
 double vec9[9];
 int i;
 double dog;

 /*
 Compute derivative of DoG w/r to (x=j,y=i,sigma)
 */

 feature_dog_deriv(
  gauss_pyr_image,
  gauss_pyr_width,
  gauss_pyr_height,
  dog_pyr_image,
  octave,
  inp_interval,
  inp_i,
  inp_j,
  deriv
 );

 /*
 Compute the Hessian ie
 matrix of second derivatives of DoG w/r to (x=j,y=i,sigma)
 */

 feature_dog_hessian(
  gauss_pyr_image,
  gauss_pyr_width,
  gauss_pyr_height,
  dog_pyr_image,
  octave,
  inp_interval,
  inp_i,
  inp_j,
  hessian
 );

 /*
 Invert the Hessian
 */

 math_lu_decomposition_inverse(
  3,
  hessian,
  hessian_inv
 );

 /*
 Check to make sure the inverse was properly computed
 Product should of course be the identity matrix
 */

 math_matrix_matrix_product(
  hessian,
  3,
  3, 
  hessian_inv,
  3,
  3,
  vec9
 );

 /*
 Get the solution
 */

 math_matrix_vector_product(
  hessian_inv,
  3,
  3,
  deriv,
  3,
  temp_vec
 );

 for ( i= 0 ; i< 3 ; i++ )
  x[i]= -temp_vec[i];

 xinterval= x[2];
 xi= x[1];
 xj= x[0];

 /*
 Compute the DoG xdog at the offset (needed to check the contrast later)
 */

 temp_val= math_vector_vector_product(
  deriv,
  3,
  x,
  3
 );

 width= gauss_pyr_width[octave];
 height= gauss_pyr_height[octave];
 dog= dog_pyr_image[octave][inp_interval][inp_i*width+inp_j];

 xdog= dog+0.5*temp_val;

 (*pxinterval)= xinterval;
 (*pxi)= xi;
 (*pxj)= xj;
 (*pxdog)= xdog;

}
