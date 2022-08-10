#include "header.h"
#include "proto.h"

void rectify_fix_center(
 int w,
 int h,
 double theta_l_y,
 double theta_l_z,
 double theta_r_x,
 double theta_r_y,
 double theta_r_z,
 double f,
 double H_l_mat[9],
 double H_r_mat[9]
)

/*
Modify the left and right homographies
to fix the center point of each image
through application of rectifying homography
*/

{

 double k_mat[9];
 double inv_k_mat[9];
 double rot_l_mat[9];
 double rot_r_mat[9];
 double x;
 double y;
 double x2;
 double y2;
 double alpha;
 double rot_x_mat[9];
 double temp_mat[9];
 double temp2_mat[9];

 /*
 Compute K matrix
 */

 rectify_compute_k_matrix(
  w,
  h,
  f,
  k_mat
 );

 /*
 Compute inverse K matrix
 */

 rectify_compute_inverse_k_matrix(
  w,
  h,
  f,
  inv_k_mat
 );

 /*
 Compute left rotation matrix
 */

 rectify_compute_rotation_left(
  theta_l_y,
  theta_l_z,
  rot_l_mat
 );

 /*
 Compute right rotation matrix
 */

 rectify_compute_rotation_right(
  theta_r_x,
  theta_r_y,
  theta_r_z,
  rot_r_mat
 );

 /*
 Rotate around x axis to keep center point at same ordinate
 */

 /*
 Apply left homography to the image center
 */

 x= (double)w/2;
 y= (double)h/2;

 homography_apply(
  H_l_mat,
  x,
  y,
  &x2,
  &y2
 );

 /*
 Compute rotation angle alpha
 */

 /*
 alpha= atan((y2-y)/f);
 */
 alpha= atan2(y2-y,f);

 /*
 Compute rotation matrix around x
 */

 rectify_compute_rotation(
  alpha,
  'x',
  rot_x_mat
 );

 /*
 Compute left homography
 */

 /*
 Compute Rl*inv_k_mat
 */

 math_matrix_matrix_product(
  rot_l_mat,
  3,
  3,
  inv_k_mat,
  3,
  3,
  temp_mat
 );

 /*
 Compute rot_x_mat*Rl*inv_k_mat
 */

 math_matrix_matrix_product(
  rot_x_mat,
  3,
  3,
  temp_mat,
  3,
  3,
  temp2_mat
 );

 /*
 Compute k_mat*rot_x_mat*Rl*inv_k_mat
 */

 math_matrix_matrix_product(
  k_mat,
  3,
  3,
  temp2_mat,
  3,
  3,
  H_l_mat
 );

 /*
 Compute right homography
 */

 /*
 Compute Rr*inv_k_mat
 */

 math_matrix_matrix_product(
  rot_r_mat,
  3,
  3,
  inv_k_mat,
  3,
  3,
  temp_mat
 );

 /*
 Compute rot_x_mat*Rr*inv_k_mat
 */

 math_matrix_matrix_product(
  rot_x_mat,
  3,
  3,
  temp_mat,
  3,
  3,
  temp2_mat
 );

 /*
 Compute k_mat*rot_x_mat*Rr*inv_k_mat
 */

 math_matrix_matrix_product(
  k_mat,
  3,
  3,
  temp2_mat,
  3,
  3,
  H_r_mat
 );

 /*
 Move principal point to keep center point at same abscissa
 */

 /*
 Apply left homography to the image center
 */

 x= (double)w/2;
 y= (double)h/2;

 homography_apply(
  H_l_mat,
  x,
  y,
  &x2,
  &y2
 );

 /*
 Update k_mat
 */

 k_mat[0*3+2]= (double)w-x2;

 /*
 Compute left homography
 */

 /*
 Compute Rl*inv_k_mat
 */

 math_matrix_matrix_product(
  rot_l_mat,
  3,
  3,
  inv_k_mat,
  3,
  3,
  temp_mat
 );

 /*
 Compute rot_x_mat*Rl*inv_k_mat
 */

 math_matrix_matrix_product(
  rot_x_mat,
  3,
  3,
  temp_mat,
  3,
  3,
  temp2_mat
 );

 /*
 Compute k_mat*rot_x_mat*Rl*inv_k_mat
 */

 math_matrix_matrix_product(
  k_mat,
  3,
  3,
  temp2_mat,
  3,
  3,
  H_l_mat
 );

 /*
 Apply right homography to the image center
 */

 x= (double)w/2;
 y= (double)h/2;

 homography_apply(
  H_r_mat,
  x,
  y,
  &x2,
  &y2
 );

 /*
 Update k_mat
 */

 k_mat[0*3+2]= (double)w-x2;

 /*
 Compute right homography
 */

 /*
 Compute Rr*inv_k_mat
 */

 math_matrix_matrix_product(
  rot_r_mat,
  3,
  3,
  inv_k_mat,
  3,
  3,
  temp_mat
 );

 /*
 Compute rot_x_mat*Rr*inv_k_mat
 */

 math_matrix_matrix_product(
  rot_x_mat,
  3,
  3,
  temp_mat,
  3,
  3,
  temp2_mat
 );

 /*
 Compute k_mat*rot_x_mat*Rr*inv_k_mat
 */

 math_matrix_matrix_product(
  k_mat,
  3,
  3,
  temp2_mat,
  3,
  3,
  H_r_mat
 );

}
