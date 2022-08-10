#include "header.h"
#include "proto.h"

void rectify_compute_fundamental_matrix(
 int w,
 int h,
 double theta_l_y,
 double theta_l_z,
 double theta_r_x,
 double theta_r_y,
 double theta_r_z,
 double f,
 double fund_mat[9]
)

/*
Compute the fundamental matrix
F = (Rl*K^-1)t * [e1]x * Rr*K^-1
*/

{
 
 double inv_k_mat[9];
 double rot_mat_r[9];
 double RrK1_mat[9];
 double e1_cross_mat[9];
 double e1RrK1_mat[9];
 double rot_mat_l[9];
 double RlK1_mat[9];
 double RlK1t_mat[9];

 /*
 Compute K^-1
 */

 rectify_compute_inverse_k_matrix(
  w,
  h,
  f,
  inv_k_mat
 );

 /*
 Compute Rr
 */

 rectify_compute_rotation_right(
  theta_r_x,
  theta_r_y,
  theta_r_z,
  rot_mat_r
 );

 /*
 Compute Rr*K^-1
 */

 math_matrix_matrix_product(
  rot_mat_r,
  3,
  3,
  inv_k_mat,
  3,
  3,
  RrK1_mat
 );

 /*
 Compute [e1]x
 */

 e1_cross_mat[0*3+0]= 0;
 e1_cross_mat[0*3+1]= 0;
 e1_cross_mat[0*3+2]= 0;

 e1_cross_mat[1*3+0]= 0;
 e1_cross_mat[1*3+1]= 0;
 e1_cross_mat[1*3+2]=-1;

 e1_cross_mat[2*3+0]= 0;
 e1_cross_mat[2*3+1]= 1;
 e1_cross_mat[2*3+2]= 0;

 /*
 Compute [e1]x * Rr*K^-1
 */

 math_matrix_matrix_product(
  e1_cross_mat,
  3,
  3,
  RrK1_mat,
  3,
  3,
  e1RrK1_mat
 );

 /*
 Compute Rl
 */

 rectify_compute_rotation_left(
  theta_l_y,
  theta_l_z,
  rot_mat_l
 );

 /*
 Compute Rl*K^-1
 */

 math_matrix_matrix_product(
  rot_mat_l,
  3,
  3,
  inv_k_mat,
  3,
  3,
  RlK1_mat
 );

 /*
 Compute (Rl*K^-1)t
 */

 math_matrix_transpose(
  RlK1_mat,
  3,
  3,
  RlK1t_mat
 );

 /*
 Compute (Rl*K^-1)t * [e1]x * Rr*K^-1
 */

 math_matrix_matrix_product(
  RlK1t_mat,
  3,
  3,
  e1RrK1_mat,
  3,
  3,
  fund_mat
 );

}
