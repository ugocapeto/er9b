#include "header.h"
#include "proto.h"

void rectify_compute_rotation_left(
 double theta_l_y,
 double theta_l_z,
 double rot_mat_l[9]
)

/*
Compute rotation for left image
*/

{

 double rot_mat_l_y[9];
 double rot_mat_l_z[9];

 /*
 Compute rotation around y axis
 */

 rectify_compute_rotation(
  theta_l_y,
  'y',
  rot_mat_l_y
 );

 /*
 Compute rotation around z axis
 */

 rectify_compute_rotation(
  theta_l_z,
  'z',
  rot_mat_l_z
 );

 /*
 Compute R_l_z * R_l_y
 */

 math_matrix_matrix_product(
  rot_mat_l_z,
  3,
  3,
  rot_mat_l_y,
  3,
  3,
  rot_mat_l
 );

}
