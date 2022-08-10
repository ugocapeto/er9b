#include "header.h"
#include "proto.h"

void feature_descriptor_convert_histogram(
 double ***hist_arr,
 int descr_width,
 int hist_nbr,
 feat_struct *feat
)

{

 double mag_thresh;
 double int_factor;
 int int_val;
 int descr_nbr;
 int descr_i;
 int descr_j;
 int hist_ind;
 int descr_ind;

 descr_nbr= descr_width*descr_width*hist_nbr;

 feat->descr_nbr= descr_nbr;
 feat->descr= (double *)calloc(descr_nbr,sizeof(double));

 /*
 Store the histogram in vector form directly in the feature
 */

 descr_ind= 0;
 for ( descr_i= 0 ; descr_i< descr_width ; descr_i++ ) {
    for ( descr_j= 0 ; descr_j< descr_width ; descr_j++ ) {
       for ( hist_ind= 0 ; hist_ind< hist_nbr ; hist_ind++ ) {
          feat->descr[descr_ind] = hist_arr[descr_i][descr_j][hist_ind];
          descr_ind++;
       }
    }
 }

 /*
 Normalize the descriptor
 */

 feature_descriptor_normalize(
  feat
 );

 /*
 Cap the descriptor
 */

 mag_thresh= 0.2;
 for ( descr_ind= 0 ; descr_ind< descr_nbr ; descr_ind++ ) {
    if ( feat->descr[descr_ind] > mag_thresh )
     feat->descr[descr_ind] = mag_thresh;
 }

 /*
 Normalize the descriptor
 */

 feature_descriptor_normalize(
  feat
 );

 /*
 Convert double precision values between 0 and 1
 to integer values between 0 and int_factor
 */

 int_factor= 512.0;
 for ( descr_ind= 0 ; descr_ind< descr_nbr ; descr_ind++ ) {
    int_val = (int)(int_factor * feat->descr[descr_ind]);
    if ( int_val > 255 ) 
     int_val= 255;
    feat->descr[descr_ind]= (double)int_val;
 }

}
