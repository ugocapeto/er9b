#include "header.h"
#include "proto.h"

void rectify_compute_sampson_error(
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
 double *sampson_error_arr
)

/*
Compute the Sampson error for each match
and put it in sampson_error_arr[match_ind]
*/

{

 double fund_mat[9];
 double fund_mat_trans[9];
 double e3_cross_mat[9];
 int match_ind;
 double match3_l[3];
 double match3_r[3];
 double FXr_vec[3];
 double num;
 double den;
 double e3FXr_vec[3];
 double val;
 double FtXl_vec[3];
 double e3FtXl_vec[3];

 /*
 Compute the fundamental matrix
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

 math_matrix_transpose(
  fund_mat,
  3,
  3,
  fund_mat_trans
 );

 e3_cross_mat[0*3+0]= 0;
 e3_cross_mat[0*3+1]=-1; 
 e3_cross_mat[0*3+2]= 0;

 e3_cross_mat[1*3+0]= 1;
 e3_cross_mat[1*3+1]= 0;
 e3_cross_mat[1*3+2]= 0;

 e3_cross_mat[2*3+0]= 0;
 e3_cross_mat[2*3+1]= 0;
 e3_cross_mat[2*3+2]= 0;

 for ( match_ind= 0 ; match_ind< match_nbr ; match_ind++ ) {
    match3_l[0]= match_arr[match_ind].x1;
    match3_l[1]= match_arr[match_ind].y1;
    match3_l[2]= 1;
    match3_r[0]= match_arr[match_ind].x2;
    match3_r[1]= match_arr[match_ind].y2;
    match3_r[2]= 1;

    /*
    Numerator is Xlt*F*Xr
    */

    math_matrix_vector_product(
     fund_mat,
     3,
     3,
     match3_r,
     3,
     FXr_vec
    );

    num= math_vector_vector_product(
     match3_l,
     3,
     FXr_vec,
     3
    );

    /*
    Denominator is ||e3*F*Xr||^2 + ||e3*Ft*Xl||^2
    */

    den= 0;

    math_matrix_vector_product(
     e3_cross_mat,
     3,
     3,
     FXr_vec,
     3,
     e3FXr_vec
    );

    val= math_vector_vector_product(
     e3FXr_vec,
     3,
     e3FXr_vec,
     3
    );

    den+= val;

    math_matrix_vector_product(
     fund_mat_trans,
     3,
     3,
     match3_l,
     3,
     FtXl_vec
    );

    math_matrix_vector_product(
     e3_cross_mat,
     3,
     3,
     FtXl_vec,
     3,
     e3FtXl_vec
    );

    val= math_vector_vector_product(
     e3FtXl_vec,
     3,
     e3FtXl_vec,
     3
    );

    den+= val;

    den= sqrt(den);

    sampson_error_arr[match_ind]= num/den;

    /*
    fprintf(stdout,"sampson_error_arr[%d]= %g\n",match_ind,sampson_error_arr[match_ind]);
    */
 }

}
