#include "header.h"
#include "proto.h"

void rectify_compute_rotation_right(
 double theta_r_x,
 double theta_r_y,
 double theta_r_z,
 double rot_mat_r[9]
)

/*
Compute rotation for right image
*/

{

 double rot_mat_r_x[9];
 double rot_mat_r_y[9];
 double rot_mat_r_z[9];
 double temp_mat[9];

 /*
 Compute rotation around x axis
 */

 rectify_compute_rotation(
  theta_r_x,
  'x',
  rot_mat_r_x
 );

 /*
 Compute rotation around y axis
 */

 rectify_compute_rotation(
  theta_r_y,
  'y',
  rot_mat_r_y
 );

 /*
 Compute rotation around z axis
 */

 rectify_compute_rotation(
  theta_r_z,
  'z',
  rot_mat_r_z
 );

 /*
 Compute R_r_y * R_r_x
 */

 math_matrix_matrix_product(
  rot_mat_r_y,
  3,
  3,
  rot_mat_r_x,
  3,
  3,
  temp_mat
 );

 /*
 Compute R_r_z * R_r_y * R_r_x
 */

 math_matrix_matrix_product(
  rot_mat_r_z,
  3,
  3,
  temp_mat,
  3,
  3,
  rot_mat_r
 );

}
