#include "header.h"
#include "proto.h"

int rectify_main(
 char *filename_match,
 int w,
 int h,
 char *filename_H_l,
 char *filename_H_r,
 char *filename_disp_range,
 double max_mean_error
)

/*
max_mean_error is the maximum mean vertical disparity error
that is allowed
*/

{

 FILE *fp;
 int match_nbr;
 match_struct *match_arr;
 double theta_l_y;
 double theta_l_z;
 double theta_r_x;
 double theta_r_y;
 double theta_r_z;
 double f;
 double k_mat[9];
 double inv_k_mat[9];
 double rot_l_mat[9];
 double rot_r_mat[9];
 double temp_mat[9];
 double H_l_mat[9];
 double H_r_mat[9];
 int i;
 int j;
 int feat1_ind;
 int feat2_ind;
 double x1;
 double y1;
 double x2;
 double y2;
 int err_flag;
 double mean_error;
 int min_d;
 int max_d;

 /*
 Initialize to no error
 */

 err_flag= 0;
 
 /*
 Read the file containing the matches and
 put the matches in match_arr
 */

 fp= fopen(filename_match,"r");

 match_nbr= 0;
 match_arr= 0;

 while ( fscanf(fp,"%d %lg %lg %d %lg %lg",
          &feat1_ind,&x1,&y1,&feat2_ind,&x2,&y2) == 6 ) {
    if ( match_nbr == 0 ) {
       match_arr= (match_struct *)calloc(match_nbr+1,sizeof(match_struct));
    }
    else {
       match_arr= (match_struct *)realloc(match_arr,(match_nbr+1)*sizeof(match_struct));
    }
    match_arr[match_nbr].feat1_ind= feat1_ind;
    match_arr[match_nbr].x1= x1;
    match_arr[match_nbr].y1= y1;
    match_arr[match_nbr].feat2_ind= feat2_ind;
    match_arr[match_nbr].x2= x2;
    match_arr[match_nbr].y2= y2;
    match_nbr++;
 }

 fclose(fp);

 /*
 Minimize the Sampson error
 */

 rectify_minimize_sampson_error(
  w,
  h,
  match_nbr,
  match_arr,
  &theta_l_y,
  &theta_l_z,
  &theta_r_x,
  &theta_r_y,
  &theta_r_z,
  &f
 );

 fprintf(stdout,"theta_l_y = %g\n",theta_l_y);
 fprintf(stdout,"theta_l_z = %g\n",theta_l_z);
 fprintf(stdout,"theta_r_x = %g\n",theta_r_x);
 fprintf(stdout,"theta_r_y = %g\n",theta_r_y);
 fprintf(stdout,"theta_r_z = %g\n",theta_r_z);
 fprintf(stdout,"f = %g\n",f);

 /*
 Compute the left and right homographies
 */

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
 fprintf(stdout,"k_mat=");
 for ( i= 0 ; i< 3*3 ; i++ )
  fprintf(stdout," %g",k_mat[i]);
 fprintf(stdout,"\n");
 */

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
 fprintf(stdout,"inv_k_mat=");
 for ( i= 0 ; i< 3*3 ; i++ )
  fprintf(stdout," %g",inv_k_mat[i]);
 fprintf(stdout,"\n");
 */

 /*
 Compute left homography
 */

 /*
 Compute left rotation matrix
 */

 rectify_compute_rotation_left(
  theta_l_y,
  theta_l_z,
  rot_l_mat
 );

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
 Compute H_l = k_mat*Rl*inv_k_mat
 That's the left homography
 */

 math_matrix_matrix_product(
  k_mat,
  3,
  3,
  temp_mat,
  3,
  3,
  H_l_mat
 );

 /*
 fprintf(stdout,"H_l_mat=");
 for ( i= 0 ; i< 3*3 ; i++ )
  fprintf(stdout," %g",H_l_mat[i]);
 fprintf(stdout,"\n");
 */

 /*
 Compute right homography
 */

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
 Compute H_r = k_mat*Rr*inv_k_mat
 That's the right homography
 */

 math_matrix_matrix_product(
  k_mat,
  3,
  3,
  temp_mat,
  3,
  3,
  H_r_mat
 );

 /*
 fprintf(stdout,"H_r_mat=");
 for ( i= 0 ; i< 3*3 ; i++ )
  fprintf(stdout," %g",H_r_mat[i]);
 fprintf(stdout,"\n");
 */

 /*
 Modify the rectifying homographies so that
 the image center for each image is fixed
 through application of rectifying homography
 */

 rectify_fix_center(
  w,
  h,
  theta_l_y,
  theta_l_z,
  theta_r_x,
  theta_r_y,
  theta_r_z,
  f,
  H_l_mat,
  H_r_mat
 );

 /*
 fprintf(stdout,"H_l_mat=");
 for ( i= 0 ; i< 3*3 ; i++ )
  fprintf(stdout," %g",H_l_mat[i]);
 fprintf(stdout,"\n");
 */

 /*
 fprintf(stdout,"H_r_mat=");
 for ( i= 0 ; i< 3*3 ; i++ )
  fprintf(stdout," %g",H_r_mat[i]);
 fprintf(stdout,"\n");
 */

 /*
 Compute the mean vertical disparity error
 */

 mean_error= rectify_compute_vertical_disparity_error(
  w,
  h,
  match_nbr,
  match_arr,
  H_l_mat,
  H_r_mat
 );

 fprintf(stdout,"Mean vertical disparity error = %g\n",
  mean_error);

 if ( mean_error > max_mean_error ) {
    err_flag= 1;
    goto END;
 }

 /*
 Compute the min and max disparity
 for the rectified images
 */

 rectify_compute_disp_range(
  w,
  h,
  match_nbr,
  match_arr,
  H_l_mat,
  H_r_mat,
  &min_d,
  &max_d
 );

 fprintf(stdout," Min disp = %d Max disp = %d\n",min_d,max_d);

 /*
 Compute the min and max disparity
 for the rectified images
 after having trimmed the disparity distribution
 to get a better disparity range
 */

 rectify_compute_disp_range_b(
  w,
  h,
  match_nbr,
  match_arr,
  H_l_mat,
  H_r_mat,
  &min_d,
  &max_d
 );

 fprintf(stdout," Min disp = %d Max disp = %d\n",min_d,max_d);

 /*
 Check the disparity range
 If too large, the rectification is likely not to be good
 */

 if ( max_d-min_d > w/2 ) {
    err_flag= 1;
    goto END;
 }

 /*
 Write the disp range on file
 */

 fp= fopen(filename_disp_range,"w");

 fprintf(fp,"%d %d\n",min_d,max_d);

 fclose(fp);

 /*
 Write the left homography to given file
 */

 fp= fopen(filename_H_l,"w");
 for ( i= 0 ; i< 3 ; i++ ) {
    for ( j= 0 ; j< 3 ; j++ ) {
       fprintf(fp,"%g ",H_l_mat[i*3+j]);
    }
 }
 fclose(fp);

 /*
 Write the right homography to given file
 */

 fp= fopen(filename_H_r,"w");
 for ( i= 0 ; i< 3 ; i++ ) {
    for ( j= 0 ; j< 3 ; j++ ) {
       fprintf(fp,"%g ",H_r_mat[i*3+j]);
    }
 }
 fclose(fp);

 END:

 /*
 Free match_arr
 */

 if ( match_nbr > 0 )
  free(match_arr);

 return err_flag;

}
