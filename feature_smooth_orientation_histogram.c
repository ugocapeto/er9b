#include "header.h"
#include "proto.h"

void feature_smooth_orientation_histogram(
 double *hist_arr,
 int hist_nbr
)

{

 double *smooth_hist_arr;
 int hist_ind;
 int prev_hist_ind;
 int next_hist_ind;

 smooth_hist_arr= (double *)calloc(hist_nbr,sizeof(double));

 for ( hist_ind= 0 ; hist_ind< hist_nbr ; hist_ind++ ) {
    prev_hist_ind= hist_ind-1;
    if ( prev_hist_ind == -1 )
     prev_hist_ind= hist_nbr-1;

    next_hist_ind= hist_ind+1;
    if ( next_hist_ind == hist_nbr )
     next_hist_ind= 0;

    smooth_hist_arr[hist_ind]=
     0.25*hist_arr[prev_hist_ind]+
     0.50*hist_arr[hist_ind]+
     0.25*hist_arr[next_hist_ind];
 }

 /*
 Replace current values with smoothed values
 */

 for ( hist_ind= 0 ; hist_ind< hist_nbr ; hist_ind++ ) {
    hist_arr[hist_ind]= smooth_hist_arr[hist_ind];
 }

 free(smooth_hist_arr);

}
