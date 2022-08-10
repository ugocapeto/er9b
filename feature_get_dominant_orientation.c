#include "header.h"
#include "proto.h"

void feature_get_dominant_orientation(
 double *hist_arr,
 int hist_nbr,
 double *pmax_mag,
 int *pmax_hist_ind
)

{

 double max_mag;
 int max_hist_ind;
 int hist_ind;

 max_mag= hist_arr[0];
 max_hist_ind= 0;

 for ( hist_ind= 1 ; hist_ind< hist_nbr ; hist_ind++ ) {
    if ( hist_arr[hist_ind] > max_mag ) {
       max_mag= hist_arr[hist_ind]; 
       max_hist_ind= hist_ind;
    }
 }

 (*pmax_mag)= max_mag;
 (*pmax_hist_ind)= max_hist_ind;

}
