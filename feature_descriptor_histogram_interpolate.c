#include "header.h"
#include "proto.h"

void feature_descriptor_histogram_interpolate(
 double ***hist_arr,
 double descr_i_sub,
 double descr_j_sub,
 double hist_ind_sub,
 double mag,
 int descr_width,
 int hist_nbr
)

/*
Distribute mag in a trilinear fashion
*/

{

 int descr_i_sub_floor;
 int descr_j_sub_floor;
 int hist_ind_sub_floor;
 int i_offset;
 int j_offset;
 int h_offset;
 int descr_i;
 int descr_j;
 int hist_ind;
 double val_i;
 double val_j;
 double val_h;
 double diff_i;
 double diff_j;
 double diff_h;

 /*
 Get the floor of descr_i_sub
 */

 if ( descr_i_sub >= 0 )
  descr_i_sub_floor= (int)descr_i_sub;
 else
  descr_i_sub_floor= (int)descr_i_sub-1;

 /*
 Get the floor of descr_j_sub
 */

 if ( descr_j_sub >= 0 )
  descr_j_sub_floor= (int)descr_j_sub;
 else
  descr_j_sub_floor= (int)descr_j_sub-1;

 /*
 Get the floor of hist_ind_sub
 */

 if ( hist_ind_sub >= 0 )
  hist_ind_sub_floor= (int)hist_ind_sub;
 else
  hist_ind_sub_floor= (int)hist_ind_sub-1;

 /*
 Compute the differences
 (between sub value and floor)
 */

 diff_i= descr_i_sub-(double)descr_i_sub_floor;
 diff_j= descr_j_sub-(double)descr_j_sub_floor;
 diff_h= hist_ind_sub-(double)hist_ind_sub_floor;

 for ( i_offset= 0 ; i_offset<= 1 ; i_offset++ ) {

    descr_i= descr_i_sub_floor+i_offset;

    if ( !( descr_i >= 0 &&
            descr_i < descr_width ) )
     continue;

    if ( i_offset == 0 ) {
       val_i= 1-diff_i;
    } 
    if ( i_offset == 1 ) {
       val_i=   diff_i;
    }

    for ( j_offset= 0 ; j_offset<= 1 ; j_offset++ ) {

       descr_j= descr_j_sub_floor+j_offset; 

       if ( !( descr_j >= 0 &&
               descr_j < descr_width ) )
         continue;

       if ( j_offset == 0 ) {
          val_j= 1-diff_j;
       }
       if ( j_offset == 1 ) {
          val_j=   diff_j;
       }

       for ( h_offset= 0 ; h_offset<= 1 ; h_offset++ ) {

          hist_ind= (hist_ind_sub_floor+h_offset)%hist_nbr;

          if ( h_offset == 0 ) {
             val_h= 1-diff_h;
          }
          if ( h_offset == 1 ) {
             val_h=   diff_h;
          }

          hist_arr[descr_i][descr_j][hist_ind]+= val_i*val_j*val_h*mag;

       }
    }
 }

}
