#include "header.h"
#include "proto.h"

void feature_compute_features_orientation_histogram(
 int octave_nbr,
 int interval_nbr,
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 feat_struct **pfeat_arr,
 int *pfeat_nbr
)

{

 int hist_nbr;
 double sigma_factor;
 int smooth_iter_nbr;
 double peak_ratio;
 feat_struct *feat_arr;
 int feat_nbr;
 int octave;
 int interval;
 int i;
 int j;
 double xinterval;
 double xi;
 double xj;
 double sigma;
 double sigma_octave;
 int width;
 int height;
 double *image;
 double radius_dbl;
 double *hist_arr;
 int iter;
 double max_mag;
 int max_hist_ind;
 double mag_thresh;
 double feature_radius_dbl;
 int feature_radius;
 double feature_sigma;
 feat_struct *inp_feat_arr;
 int inp_feat_nbr;
 feat_struct inp_feat;
 int inp_feat_ind;

 /*
 Set number of bins in orientation histogram
 */

 hist_nbr= 36;

 /*
 Set Gaussian sigma factor for orientation histogram
 */

 sigma_factor= 1.5;

 /* 
 Set the radius of the window used for orientation histogram
 */

 radius_dbl= 3.0*sigma_factor;

 /*
 Set the number of smoothing passes for orientation histogram
 */

 smooth_iter_nbr= 2;

 /*
 Set peak ratio that results in new feature
 */

 peak_ratio= 0.8;

 inp_feat_arr= (*pfeat_arr);
 inp_feat_nbr= (*pfeat_nbr);

 /*
 We are gonna create a brand new array of features
 */

 feat_arr= 0;
 feat_nbr= 0;

 for ( inp_feat_ind= 0 ; inp_feat_ind< inp_feat_nbr ; inp_feat_ind++ ) {
    inp_feat= inp_feat_arr[inp_feat_ind];
    octave= inp_feat.octave;
    interval= inp_feat.interval;
    i= inp_feat.i;
    j= inp_feat.j;
    xinterval= inp_feat.xinterval;
    xi= inp_feat.xi;
    xj= inp_feat.xj;
    sigma= inp_feat.sigma;
    sigma_octave= inp_feat.sigma_octave;

    /*
    Get the image for that octave
    */

    width= gauss_pyr_width[octave];
    height= gauss_pyr_height[octave];
    image= gauss_pyr_image[octave][interval];

    /*
    Get window radius for that feature
    */

    feature_radius_dbl= radius_dbl*sigma_octave;
    feature_radius= (int)(feature_radius_dbl+0.5);

    /*
    Get sigma for that feature
    */

    feature_sigma= sigma_factor*sigma_octave;

    /*
    Compute orientation histogram
    */

    hist_arr= feature_orientation_histogram(
     width,
     height,
     image,
     i,
     j,
     hist_nbr,
     feature_radius,
     feature_sigma
    );

    /*
    Smooth the orientation histogram
    */

    for ( iter= 0 ; iter< smooth_iter_nbr ; iter++ ) {
       feature_smooth_orientation_histogram(
        hist_arr,
        hist_nbr
       );
    }

    /*
    Get the dominant orientation
    */

    feature_get_dominant_orientation(
     hist_arr,
     hist_nbr,
     &max_mag,
     &max_hist_ind
    );

    /*
    Add features for any peak that's high enough
    */

    mag_thresh= max_mag*peak_ratio;
    feature_add_features(
     inp_feat,
     hist_arr,
     hist_nbr,
     mag_thresh,
     &feat_arr,
     &feat_nbr
    );

    /*
    Free hist_arr
    */

    if ( hist_nbr > 0 )
     free(hist_arr);
 }

 /*
 Free inp_feat_arr
 */

 if ( inp_feat_nbr > 0 )
  free(inp_feat_arr);

 (*pfeat_arr)= feat_arr;
 (*pfeat_nbr)= feat_nbr;

}
