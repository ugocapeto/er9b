#include "header.h"
#include "proto.h"

void feature_detect_features(
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

 int img_border;
 double contrast_thresh;
 int feat_nbr;
 feat_struct *feat_arr;
 int octave;
 int interval;
 int i;
 int j;
 int status;
 int err_flag;
 int extremum_interval;
 int extremum_i;
 int extremum_j;
 double extremum_xinterval;
 double extremum_xi;
 double extremum_xj;
 double extremum_xdog;
 double dog;
 double prelim_contrast_thresh;
 int width;
 int height;
 int pixel;

 /*
 Set the image border in which the feaures are ignored
 */

 img_border= 5;

 /*
 Set the contrast threshold
 */

 contrast_thresh= 0.04;

 prelim_contrast_thresh= 0.5 * contrast_thresh / (double)interval_nbr;

 /*
 Initialize the feature storage array
 */

 feat_nbr= 0;
 feat_arr= 0;

 for ( octave= 0 ; octave< octave_nbr ; octave++ ) {

    width= gauss_pyr_width[octave];
    height= gauss_pyr_height[octave];

    for ( interval= 1 ; interval<= interval_nbr ; interval++ ) {

       for ( i= 0+img_border ;
             i< gauss_pyr_height[octave]-img_border ;
             i++ ) {

          for ( j= 0+img_border ;
                j< gauss_pyr_width[octave]-img_border ;
                j++ ) {

             pixel= i*width+j;

             /*
             Get the Difference of Gaussian at that pixel
             */

             dog= dog_pyr_image[octave][interval][pixel];

             /*
             Check if it has enough contrast
             */

             if ( !( fabs(dog) > prelim_contrast_thresh ) ) {

                /*
                Not enough contrast!
                */

                continue;
             }

             /*
             Looks like pixel has enough contrast
             */

             /*
             See if it's an extremum
             status = 1 means yes
             status = 0 means no
             */

             status= feature_is_extremum(
              gauss_pyr_image,
              gauss_pyr_width,
              gauss_pyr_height,
              dog_pyr_image,
              octave,
              interval,
              i,
              j
             );

             if ( status == 0 ) {

                /*
                Not an extremum!
                */

                continue;
             }

             /*
             Looks like we have an extremum
             */

             /*
             Fine-tune the location of the extremum
             (extremum_xinterval,extremum_xi,extremum_xj) is
             the offset vector to add to (interval,i,j)
             to get the actual location of the extremum
             extremum_xdog is the dog at that actual location
             */

             err_flag= feature_interpolate_extremum_location_main(
              octave_nbr,
              interval_nbr,
              gauss_pyr_image,
              gauss_pyr_width,
              gauss_pyr_height,
              dog_pyr_image,
              img_border,
              octave,
              interval,
              i,
              j,
              &extremum_interval,
              &extremum_i,
              &extremum_j,
              &extremum_xinterval,
              &extremum_xi,
              &extremum_xj,
              &extremum_xdog
             );

             if ( err_flag == 1 ) {

                /*
                Looks like
                we could not compute the exact location of the extremum
                */

                continue;
             }

             /*
             If here,
             looks like we have a bona fide extremum
             */

             /*
             Check the pixel contrast
             */

             if ( fabs(extremum_xdog) < contrast_thresh/(double)interval_nbr ) {

                /*
                Not enough contrast for that feature to be kept
                */

                continue;
             }

             /*
             Check if feature is too edge-like
             */

             err_flag= feature_check_extremum_edge_like(
              octave_nbr,
              interval_nbr,
              gauss_pyr_image,
              gauss_pyr_width,
              gauss_pyr_height,
              dog_pyr_image,
              img_border,
              octave,
              extremum_interval,
              extremum_i,
              extremum_j
             );

             if ( err_flag == 1 ) {

                /*
                Looks like we come up emty-handed
                */

                continue;
             }

             /*
             Store the feature
             */

             feature_add_feature(
              octave,
              extremum_interval,
              extremum_i,
              extremum_j,
              extremum_xinterval,
              extremum_xi,
              extremum_xj,
              (double)0,
              (double)0,
              (double)0,
              (double *)0,
              (int)0,
              &feat_arr,
              &feat_nbr
             );
          }
       } 
    }
 }

 (*pfeat_arr)= feat_arr;
 (*pfeat_nbr)= feat_nbr;

}
