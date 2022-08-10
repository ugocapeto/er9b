#include "header.h"
#include "proto.h"

void rectify_compute_disp_range(
 int w,
 int h,
 int match_nbr,
 match_struct *match_arr,
 double H_l_mat[9],
 double H_r_mat[9],
 int *pmin_d,
 int *pmax_d
)

/*
Get min and max disparity
for the left and right rectified images
Disparity d is defined as I_l(x_l)=I_r(x_r=x_l-d)
*/

{

 double min_d_dbl;
 double max_d_dbl;
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
 double d_dbl;
 int d;
 int min_d;
 int max_d;

 /*
 Initialize
 */

 min_d_dbl= 1.0e32;
 max_d_dbl=-1.0e32;

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
    Compute disparity
    */

    d_dbl= x2_l-x2_r;

    if ( d_dbl < min_d_dbl )
     min_d_dbl= d_dbl;
    if ( d_dbl > max_d_dbl )
     max_d_dbl= d_dbl;
 }

 /*
 Get min_d_dbl's floor
 */

 d_dbl= min_d_dbl;
 if ( d_dbl >= 0.0 )
  d= (int)d_dbl;
 else
  d= (int)d_dbl-1;
 min_d= d;

 /*
 Get max_d_dbl's ceiling
 */

 d_dbl= max_d_dbl;
 if ( d_dbl >= 0.0 )
  d= (int)d_dbl+1;
 else
  d= (int)d_dbl;
 max_d= d;

 (*pmin_d)= min_d;
 (*pmax_d)= max_d;

}
