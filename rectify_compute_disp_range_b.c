#include "header.h"
#include "proto.h"

typedef struct rectify_print_disparity_b_struct {
 double d_dbl;
 int match_ind;
} rectify_print_disparity_b_struct;

static int rectify_print_disparity_b_compare(
 const void *p1,
 const void *p2
)

{

 if ( ((rectify_print_disparity_b_struct *)p1)->d_dbl < ((rectify_print_disparity_b_struct *)p2)->d_dbl )
  return -1;
 if ( ((rectify_print_disparity_b_struct *)p1)->d_dbl > ((rectify_print_disparity_b_struct *)p2)->d_dbl )
  return +1;

 return 0;

}

void rectify_compute_disp_range_b(
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
 rectify_print_disparity_b_struct *arr;
 double nbr_dbl;
 int nbr;
 int min_d_ind;
 int max_d_ind;
 double disp_range;

 /*
 Store the disparities
 */

 if ( match_nbr > 0 )
  arr= (rectify_print_disparity_b_struct *)calloc(match_nbr,sizeof(rectify_print_disparity_b_struct));

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

    /*
    Store the disparity
    */

    arr[match_ind].d_dbl= d_dbl;
    arr[match_ind].match_ind= match_ind;
 }

 /*
 Sort the disparities w/r to increasing disparity
 */

 qsort(
  arr,
  match_nbr,
  sizeof(rectify_print_disparity_b_struct),
  rectify_print_disparity_b_compare
 );

 /*
 Trim 1% of disparities on either side
 to get rid of possible outliers
 */

 nbr_dbl= (double)match_nbr*0.01;
 nbr= (int)(nbr_dbl+0.5);
 min_d_ind= nbr;
 max_d_ind= match_nbr-nbr-1;

 min_d_dbl= arr[min_d_ind].d_dbl;
 max_d_dbl= arr[max_d_ind].d_dbl;

 /*
 Add 10% of the range to the current range
 to extend the range on either side
 */

 disp_range= max_d_dbl-min_d_dbl;

 min_d_dbl-= disp_range*0.10;
 max_d_dbl+= disp_range*0.10;

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

 /*
 Free the disparities
 */

 if ( match_nbr > 0 )
  free(arr);

 (*pmin_d)= min_d;
 (*pmax_d)= max_d;

}
