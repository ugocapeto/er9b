#include "header.h"
#include "proto.h"

void rectify_compute_sampson_error_jacobian(
 int w,
 int h,
 double theta_l_y,
 double theta_l_z,
 double theta_r_x,
 double theta_r_y,
 double theta_r_z,
 double f,
 int match_nbr,
 match_struct *match_arr,
 double *sampson_error_jacobian_mat
)

/*
Compute the Sampson error jacobian for each match
and put it in sampson_error_jacobian_arr[match_ind][var_ind]
*/

{

 double inv_k_mat[9];
 double inv_k_mat_deriv[9];
 double rot_l_y_mat[9];
 double rot_l_z_mat[9];
 double rot_r_x_mat[9];
 double rot_r_y_mat[9];
 double rot_r_z_mat[9];
 double fund_mat[9];
 double rot_l_mat[9];
 double rot_r_mat[9];
 double RrK1_mat[9];
 double F_r_mat[9];
 double RlK1_mat[9];
 double RlK1t_mat[9];
 double F_l_mat[9];
 double rot_l_y_mat_deriv[9];
 double rot_l_z_mat_deriv[9];
 double rot_r_x_mat_deriv[9];
 double rot_r_y_mat_deriv[9];
 double rot_r_z_mat_deriv[9];
 double temp_mat[9];
 double temp2_mat[9];
 double temp3_mat[9];
 double dF0_mat[9];
 double dF1_mat[9];
 double dF2_mat[9];
 double dF3_mat[9];
 double dF4_mat[9];
 double dF5_mat[9];
 int i;
 int j;
 double dF_mat[6*9];
 double fund_mat_trans[9];
 double dF0_mat_trans[9];
 double dF1_mat_trans[9];
 double dF2_mat_trans[9];
 double dF3_mat_trans[9];
 double dF4_mat_trans[9];
 double dF5_mat_trans[9];
 double dF_mat_trans[6*9];
 int match_ind;
 double match3_l[3];
 double match3_r[3];
 int var_ind;
 double FtXl[3];
 double FdtXl[3];
 double FXr[3];
 double FdXr[3];
 double den;
 double val;
 double num1;
 double num2;
 double num3;
 double e1_cross_mat[9];

 /*
 Get K^-1
 */

 rectify_compute_inverse_k_matrix(
  w,
  h,
  f,
  inv_k_mat
 );

 /*
 Get K^-1' (derivative of K^-1)
 */

 rectify_compute_inverse_k_matrix_deriv(
  w,
  h,
  f,
  inv_k_mat_deriv
 );

 /*
 Get rotation around y for left camera
 */

 rectify_compute_rotation(
  theta_l_y,
  'y',
  rot_l_y_mat
 );

 /*
 Get rotation around z for left camera
 */

 rectify_compute_rotation(
  theta_l_z,
  'z',
  rot_l_z_mat
 );

 /*
 Get rotation around x for right camera
 */

 rectify_compute_rotation(
  theta_r_x,
  'x',
  rot_r_x_mat
 );

 /*
 Get rotation around y for right camera
 */
 
 rectify_compute_rotation(
  theta_r_y,
  'y',
  rot_r_y_mat
 );

 /*
 Get rotation around z for right camera
 */
 
 rectify_compute_rotation(
  theta_r_z,
  'z',
  rot_r_z_mat
 );

 /*
 Compute fundamental matrix
 */

 rectify_compute_fundamental_matrix(
  w,
  h,
  theta_l_y,
  theta_l_z,
  theta_r_x,
  theta_r_y,
  theta_r_z,
  f,
  fund_mat
 );

 /*
 fprintf(stdout,"F=");
 for ( i= 0 ; i< 9 ; i++ )
  fprintf(stdout," %g",fund_mat[i]);
 fprintf(stdout,"\n");
 */

 /*
 Compute left rotation Rl
 */

 rectify_compute_rotation_left(
  theta_l_y,
  theta_l_z,
  rot_l_mat
 );

 /*
 Compute right rotation Rr
 */

 rectify_compute_rotation_right(
  theta_r_x,
  theta_r_y,
  theta_r_z,
  rot_r_mat
 );

 /*
 Compute F_r_mat = [e1]x * RrK^-1
 */

 /*
 Compute Rr*K^-1
 */

 math_matrix_matrix_product(
  rot_r_mat,
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
  F_r_mat
 );

 /*
 Compute F_l_mat = (Rl*K^-1)t * [e1]x
 */

 /*
 Compute Rl*K^-1
 */

 math_matrix_matrix_product(
  rot_l_mat,
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
 Compute (Rl*K^-1)t * [e1]x
 */

 math_matrix_matrix_product(
  RlK1t_mat,
  3,
  3,
  e1_cross_mat,
  3,
  3,
  F_l_mat
 );

 /*
 Compute derivative of the fundamental matrix
 w/r to the unknowns
 */

 /*
 Compute derivative of rotation around y axis
 for the left camera
 */

 rectify_compute_rotation_deriv(
  theta_l_y,
  'y',
  rot_l_y_mat_deriv
 );

 /*
 Compute derivative of rotation around z axis
 for the left camera
 */

 rectify_compute_rotation_deriv(
  theta_l_z,
  'z',
  rot_l_z_mat_deriv
 );

 /*
 Compute derivative of rotation around x axis
 for the right camera
 */

 rectify_compute_rotation_deriv(
  theta_r_x,
  'x',
  rot_r_x_mat_deriv
 );

 /*
 Compute derivative of rotation around y axis
 for the right camera
 */

 rectify_compute_rotation_deriv(
  theta_r_y,
  'y',
  rot_r_y_mat_deriv
 );

 /*
 Compute derivative of rotation around z axis
 for the right camera
 */

 rectify_compute_rotation_deriv(
  theta_r_z,
  'z',
  rot_r_z_mat_deriv
 );

 /*
 Compute dF0_mat
 Derivative of fundamental matrix w/r to theta_l_y
 */

 /*
 Compute rot_l_z_mat * rot_l_y_mat_deriv
 */

 math_matrix_matrix_product(
  rot_l_z_mat,
  3,
  3,
  rot_l_y_mat_deriv,
  3,
  3,
  temp_mat
 );

 /*
 Compute rot_l_z_mat * rot_l_y_mat_deriv * K^-1
 */

 math_matrix_matrix_product(
  temp_mat,
  3,
  3,
  inv_k_mat,
  3,
  3,
  temp2_mat
 );

 /*
 Compute (rot_l_z_mat * rot_l_y_mat_deriv * K^-1)t
 */

 math_matrix_transpose(
  temp2_mat,
  3,
  3,
  temp3_mat
 );

 /*
 Compute (rot_l_z_mat * rot_l_y_mat_deriv * K^-1)t * F_r_mat
 */

 math_matrix_matrix_product(
  temp3_mat,
  3,
  3,
  F_r_mat,
  3,
  3,
  dF0_mat
 );

 /*
 Compute dF1_mat
 Derivative of fundamental matrix w/r to theta_l_z
 */

 /*
 Compute rot_l_z_mat_deriv * rot_l_y_mat
 */

 math_matrix_matrix_product(
  rot_l_z_mat_deriv,
  3,
  3,
  rot_l_y_mat,
  3,
  3,
  temp_mat
 );

 /*
 Compute rot_l_z_mat_deriv * rot_l_y_mat * K^-1
 */

 math_matrix_matrix_product(
  temp_mat,
  3,
  3,
  inv_k_mat,
  3,
  3,
  temp2_mat
 );

 /*
 Compute (rot_l_z_mat_deriv * rot_l_y_mat * K^-1)t
 */

 math_matrix_transpose(
  temp2_mat,
  3,
  3,
  temp3_mat
 );

 /*
 Compute (rot_l_z_mat_deriv * rot_l_y_mat * K^-1)t * F_r_mat
 */

 math_matrix_matrix_product(
  temp3_mat,
  3,
  3,
  F_r_mat,
  3,
  3,
  dF1_mat
 );

 /*
 Compute dF2_mat
 Derivative of fundamental matrix w/r to theta_r_x
 */

 /*
 Compute rot_r_z_mat * rot_r_y_mat
 */

 math_matrix_matrix_product(
  rot_r_z_mat,
  3,
  3,
  rot_r_y_mat,
  3,
  3,
  temp_mat
 );

 /*
 Compute rot_r_z_mat * rot_r_y_mat * rot_r_x_mat_deriv
 */

 math_matrix_matrix_product(
  temp_mat,
  3,
  3,
  rot_r_x_mat_deriv,
  3,
  3,
  temp2_mat
 );

 /*
 Compute rot_r_z_mat * rot_r_y_mat * rot_r_x_mat_deriv * K^-1
 */

 math_matrix_matrix_product(
  temp2_mat,
  3,
  3,
  inv_k_mat,
  3,
  3,
  temp3_mat
 );

 /*
 Compute F_l_mat * rot_r_z_mat * rot_r_y_mat * rot_r_x_mat_deriv * K^-1
 */

 math_matrix_matrix_product(
  F_l_mat,
  3,
  3,
  temp3_mat,
  3,
  3,
  dF2_mat
 );

 /*
 Compute dF3_mat
 Derivative of fundamental matrix w/r to theta_r_y
 */

 /*
 Compute rot_r_z_mat * rot_r_y_mat_deriv
 */

 math_matrix_matrix_product(
  rot_r_z_mat,
  3,
  3,
  rot_r_y_mat_deriv,
  3,
  3,
  temp_mat
 );

 /*
 Compute rot_r_z_mat * rot_r_y_mat_deriv * rot_r_x_mat
 */

 math_matrix_matrix_product(
  temp_mat,
  3,
  3,
  rot_r_x_mat,
  3,
  3,
  temp2_mat
 );

 /*
 Compute rot_r_z_mat * rot_r_y_mat_deriv * rot_r_x_mat * K^-1
 */

 math_matrix_matrix_product(
  temp2_mat,
  3,
  3,
  inv_k_mat,
  3,
  3,
  temp3_mat
 );

 /*
 Compute F_l_mat * rot_r_z_mat * rot_r_y_mat_deriv * rot_r_x_mat * K^-1
 */

 math_matrix_matrix_product(
  F_l_mat,
  3,
  3,
  temp3_mat,
  3,
  3,
  dF3_mat
 );

 /*
 Compute dF4_mat
 Derivative of fundamental matrix w/r to theta_r_z
 */

 /*
 Compute rot_r_z_mat_deriv * rot_r_y_mat
 */

 math_matrix_matrix_product(
  rot_r_z_mat_deriv,
  3,
  3,
  rot_r_y_mat,
  3,
  3,
  temp_mat
 );

 /*
 Compute rot_r_z_mat_deriv * rot_r_y_mat * rot_r_x_mat
 */

 math_matrix_matrix_product(
  temp_mat,
  3,
  3,
  rot_r_x_mat,
  3,
  3,
  temp2_mat
 );

 /*
 Compute rot_r_z_mat_deriv * rot_r_y_mat * rot_r_x_mat * K^-1
 */

 math_matrix_matrix_product(
  temp2_mat,
  3,
  3,
  inv_k_mat,
  3,
  3,
  temp3_mat
 );

 /*
 Compute F_l_mat * rot_r_z_mat_deriv * rot_r_y_mat * rot_r_x_mat * K^-1
 */

 math_matrix_matrix_product(
  F_l_mat,
  3,
  3,
  temp3_mat,
  3,
  3,
  dF4_mat
 );

 /*
 Compute dF5_mat
 Derivative of fundamental matrix w/r to g
 */

 for ( i = 0 ; i< 3 ; i++ ) {
    for ( j = 0 ; j< 3 ; j++ ) {
       dF5_mat[i*3+j]= 0;
    }
 }

 /*
 Compute rot_l_mat * inv_k_mat_deriv
 */

 math_matrix_matrix_product(
  rot_l_mat,
  3,
  3,
  inv_k_mat_deriv,
  3,
  3,
  temp_mat
 );

 /*
 Compute (rot_l_mat * inv_k_mat_deriv)t
 */

 math_matrix_transpose(
  temp_mat,
  3,
  3,
  temp2_mat
 );

 /*
 Compute (rot_l_mat * inv_k_mat_deriv)t * F_r_mat
 */

 math_matrix_matrix_product(
  temp2_mat,
  3,
  3,
  F_r_mat,
  3,
  3,
  temp3_mat
 );

 for ( i = 0 ; i< 3 ; i++ ) {
    for ( j = 0 ; j< 3 ; j++ ) {
       dF5_mat[i*3+j]+= temp3_mat[i*3+j];
    }
 }

 /*
 Compute rot_r_mat * inv_k_mat_deriv
 */

 math_matrix_matrix_product(
  rot_r_mat,
  3,
  3,
  inv_k_mat_deriv,
  3,
  3,
  temp_mat
 );

 /*
 Compute F_l_mat * rot_r_mat * inv_k_mat_deriv
 */

 math_matrix_matrix_product(
  F_l_mat,
  3,
  3,
  temp_mat,
  3,
  3,
  temp2_mat
 );

 for ( i = 0 ; i< 3 ; i++ ) {
    for ( j = 0 ; j< 3 ; j++ ) {
       dF5_mat[i*3+j]+= temp2_mat[i*3+j];
    }
 }

 /*
 fprintf(stdout,"dF0=");
 for ( i= 0 ; i< 9 ; i++ )
  fprintf(stdout," %g",dF0_mat[i]);
 fprintf(stdout,"\n");

 fprintf(stdout,"dF1=");
 for ( i= 0 ; i< 9 ; i++ )
  fprintf(stdout," %g",dF1_mat[i]);
 fprintf(stdout,"\n");

 fprintf(stdout,"dF2=");
 for ( i= 0 ; i< 9 ; i++ )
  fprintf(stdout," %g",dF2_mat[i]);
 fprintf(stdout,"\n");

 fprintf(stdout,"dF3=");
 for ( i= 0 ; i< 9 ; i++ )
  fprintf(stdout," %g",dF3_mat[i]);
 fprintf(stdout,"\n");

 fprintf(stdout,"dF4=");
 for ( i= 0 ; i< 9 ; i++ )
  fprintf(stdout," %g",dF4_mat[i]);
 fprintf(stdout,"\n");

 fprintf(stdout,"dF5=");
 for ( i= 0 ; i< 9 ; i++ )
  fprintf(stdout," %g",dF5_mat[i]);
 fprintf(stdout,"\n");
 */

 /*
 Store the derivatives of the fundamental matrix in dF_mat
 */

 for ( i= 0 ; i< 3 ; i++ ) {
    for ( j= 0 ; j< 3 ; j++ ) {
       dF_mat[0*9+i*3+j]= dF0_mat[i*3+j];
       dF_mat[1*9+i*3+j]= dF1_mat[i*3+j];
       dF_mat[2*9+i*3+j]= dF2_mat[i*3+j];
       dF_mat[3*9+i*3+j]= dF3_mat[i*3+j];
       dF_mat[4*9+i*3+j]= dF4_mat[i*3+j];
       dF_mat[5*9+i*3+j]= dF5_mat[i*3+j];
    }
 }

 /*
 Compute Ft
 */

 math_matrix_transpose(
  fund_mat,
  3,
  3,
  fund_mat_trans
 );

 /*
 Compute dF0t
 */

 math_matrix_transpose(
  dF0_mat,
  3,
  3,
  dF0_mat_trans
 );

 /*
 Compute dF1t
 */

 math_matrix_transpose(
  dF1_mat,
  3,
  3,
  dF1_mat_trans
 );

 /*
 Compute dF2t
 */

 math_matrix_transpose(
  dF2_mat,
  3,
  3,
  dF2_mat_trans
 );

 /*
 Compute dF3t
 */

 math_matrix_transpose(
  dF3_mat,
  3,
  3,
  dF3_mat_trans
 );

 /*
 Compute dF4t
 */
    
 math_matrix_transpose(
  dF4_mat,
  3,
  3,
  dF4_mat_trans
 );

 /* 
 Compute dF5t
 */

 math_matrix_transpose(
  dF5_mat,
  3,
  3,
  dF5_mat_trans
 );

 /*
 Store the transpose of the derivatives of the fundamental matrix in dF_mat_trans
 */

 for ( i= 0 ; i< 3 ; i++ ) {
    for ( j= 0 ; j< 3 ; j++ ) {
       dF_mat_trans[0*9+i*3+j]= dF0_mat_trans[i*3+j];
       dF_mat_trans[1*9+i*3+j]= dF1_mat_trans[i*3+j];
       dF_mat_trans[2*9+i*3+j]= dF2_mat_trans[i*3+j];
       dF_mat_trans[3*9+i*3+j]= dF3_mat_trans[i*3+j];
       dF_mat_trans[4*9+i*3+j]= dF4_mat_trans[i*3+j];
       dF_mat_trans[5*9+i*3+j]= dF5_mat_trans[i*3+j];
    }
 }

 /*
 Loop on all matches
 */

 for ( match_ind= 0 ; match_ind< match_nbr ; match_ind++ ) {
    match3_l[0]= match_arr[match_ind].x1;
    match3_l[1]= match_arr[match_ind].y1;
    match3_l[2]= 1;
    match3_r[0]= match_arr[match_ind].x2;
    match3_r[1]= match_arr[match_ind].y2;
    match3_r[2]= 1;

    /*
    Loop on each variable
    */

    for ( var_ind= 0 ; var_ind< 6 ; var_ind++ ) {

       /*
       Compute Ft*Xl
       */

       math_matrix_vector_product(
        fund_mat_trans,
        3,
        3,
        match3_l,
        3,
        FtXl
       );

       /*
       Compute F't*Xl
       */

       math_matrix_vector_product(
        &dF_mat_trans[var_ind*9],
        3,
        3,
        match3_l,
        3,
        FdtXl
       );

       /*
       Compute F*Xr
       */

       math_matrix_vector_product(
        fund_mat,
        3,
        3,
        match3_r,
        3,
        FXr
       );

       /*
       Compute F'*Xr
       */

       math_matrix_vector_product(
        &dF_mat[var_ind*9],
        3,
        3,
        match3_r,
        3,
        FdXr
       );

       /*
       Compute den = sqrt( ||(Ft*Xl)bar||^2 + ||(F*Xr)bar||^2 )
       */

       den= 0;

       val= math_vector_vector_product(
        FtXl,
        2,
        FtXl,
        2
       );

       den+= val;

       val= math_vector_vector_product(
        FXr,
        2,
        FXr,
        2
       );

       den+= val;

       den= sqrt(den);

       /*
       Compute num1 = Xlt*F'*Xr
       */

       num1= math_vector_vector_product(
        match3_l,
        3,
        FdXr,
        3
       );

       /*
       Compute num2 = Xlt*F*Xr
       */

       num2= math_vector_vector_product(
        match3_l,
        3,
        FXr,
        3
       );

       /*
       Compute num3
       */

       num3= 0;

       val= math_vector_vector_product(
        FtXl,
        2,
        FdtXl,
        2
       );

       num3+= val;

       val= math_vector_vector_product(
        FXr,
        2,
        FdXr,
        2
       );

       num3+= val;

       sampson_error_jacobian_mat[match_ind*6+var_ind]=
        num1/den - num2*num3/(den*den*den);

       /*
       fprintf(stdout,"jacobian[%d][%d]= %g\n",match_ind,var_ind,sampson_error_jacobian_mat[match_ind*6+var_ind]);
       */
    } /* loop on var_ind */
 } /* loop on match_ind */

}
