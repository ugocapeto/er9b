#include "header.h"
#include "proto.h"

double rectify_compute_vertical_disparity_error(
 int w,
 int h,
 int match_nbr,
 match_struct *match_arr,
 double H_l_mat[9],
 double H_r_mat[9]
)

{

 int match_ind;
 double match3_l[3];
 double match3_r[3];
 double x_l;
 double y_l;
 double x2_l;
 double y2_l;
 double x_r;
 double y_r;
 double x2_r;
 double y2_r;
 double error;
 double mean_error;

 /*
 Loop on all matches
 */

 mean_error= 0;

 for ( match_ind= 0 ; match_ind< match_nbr ; match_ind++ ) {
    match3_l[0]= match_arr[match_ind].x1;
    match3_l[1]= match_arr[match_ind].y1;
    match3_l[2]= 1;
    match3_r[0]= match_arr[match_ind].x2;
    match3_r[1]= match_arr[match_ind].y2;
    match3_r[2]= 1;

    /*
    Apply left homography to pixel in unrectified left image
    */

    x_l= match3_l[0];
    y_l= match3_l[1];

    homography_apply(
     H_l_mat,
     x_l,
     y_l,
     &x2_l,
     &y2_l
    );

    /*
    Apply right homography to pixel in unrectified right image
    */

    x_r= match3_r[0];
    y_r= match3_r[1];

    homography_apply(
     H_r_mat,
     x_r,
     y_r,
     &x2_r,
     &y2_r
    );

    /*
    Compute error
    */

    error= fabs(y2_r-y2_l);

    mean_error+= error;
 }

 mean_error/= (double)match_nbr;

 return mean_error;

}
