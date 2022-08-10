#include "header.h"
#include "proto.h"

void feature_compute_descriptors(
 int octave_nbr,
 int interval_nbr,
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 feat_struct *feat_arr, 
 int feat_nbr
)

{

 int feat_ind;
 feat_struct feat;
 int octave;
 int interval;
 int i;
 int j;
 double xinterval;
 double xi;
 double xj;
 double sigma;
 double sigma_octave;
 double ori;
 int width;
 int height;
 double *image;
 int descr_width;
 int hist_nbr;
 double ***hist_arr;
 int hist_i;
 int hist_j;

 for ( feat_ind= 0 ; feat_ind< feat_nbr ; feat_ind++ ) {
    feat= feat_arr[feat_ind];

    octave= feat.octave;
    interval= feat.interval;
    i= feat.i;
    j= feat.j;
    xinterval= feat.xinterval;
    xi= feat.xi;
    xj= feat.xj;
    sigma= feat.sigma;
    sigma_octave= feat.sigma_octave;
    ori= feat.ori;

    width= gauss_pyr_width[octave];
    height= gauss_pyr_height[octave];
    image= gauss_pyr_image[octave][interval];

    descr_width= 4;
    hist_nbr= 8;
    hist_arr= feature_descriptor_histogram(
     width,
     height,
     image,
     i,
     j,
     ori,
     sigma_octave,
     descr_width,
     hist_nbr
    );

    /*
    Convert descr_width*descr_width descriptor array of histograms 
    into a vector stored directly inside the feature
    */

    feature_descriptor_convert_histogram(
     hist_arr,
     descr_width,
     hist_nbr,
     &feat_arr[feat_ind]
    );

    /*
    Free hist_arr
    */

    for ( hist_i= 0 ; hist_i< descr_width ; hist_i++ ) {
       for ( hist_j= 0 ; hist_j< descr_width ; hist_j++ ) {
          free(hist_arr[hist_i][hist_j]);
       }
       free(hist_arr[hist_i]);
    }
    free(hist_arr);

 } /* loop on the features */

}
