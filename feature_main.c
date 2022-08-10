#include "header.h"
#include "proto.h"

int feature_main(
 char *filename_image,
 double sigma,
 feat_struct **pfeat_arr,
 int *pfeat_nbr
)

{

 char *ext;
 double ***gauss_pyr_image;
 int *gauss_pyr_width;
 int *gauss_pyr_height;
 int width;
 int height;
 int *image_rgb;
 int image_doubling_flag;
 int init_width;
 int init_height;
 double *init_image;
 double val_dbl;
 int octave_nbr;
 int interval_nbr;
 double ***dog_pyr_image;
 feat_struct *feat_arr;
 int feat_nbr;
 int val_int;
 double octave_nbr_dbl;
 int octave;
 int interval;
 int img_border;
 int min_size_int;
 double min_size_dbl;
 int err_flag;

 /*
 Load image
 */

 err_flag= load_rgb_image(
  filename_image,
  &image_rgb,
  &width,
  &height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"Filename extension for %s not recognized!\n",
     filename_image);
    fprintf(stdout,"Supported: tiff, TIFF, tif, TIF, png, PNG, jpeg, JPEG, jpg, JPG\n");
    return 1;
 }

 /*
 Set the image doubling flag
 0 means no doubling
 1 means doubling (expect more features)
 */

 image_doubling_flag= 0;

 /*
 Create init image
 (values between 0.0 and 1.0)
 */

 feature_create_init_image(
  width,
  height,
  image_rgb,
  sigma,
  image_doubling_flag,
  &init_width,
  &init_height,
  &init_image
 );

 /*
 Compute the number of octaves
 */

 /*
 Set the image border in which the feaures are ignored
 */

 img_border= 5;

 /*
 Compute minimum image size
 */

 min_size_int= 2*img_border+2;

 min_size_dbl= (double)min_size_int;

 val_int= init_height;
 if ( init_width < val_int )
  val_int= init_width;

 val_dbl= (double)val_int;

 octave_nbr_dbl= (log(val_dbl)-log(min_size_dbl))/log(2);

 octave_nbr= (int)octave_nbr_dbl;

 /*
 Let's cap the number of octaves (as in Monasse)
 */

 /*
 if ( octave_nbr > 4 )
  octave_nbr= 4;
 */

 /*
 fprintf(stdout," Number of octaves = %d\n",octave_nbr);
 */

 /*
 Set the interval nbr
 (nbr of scales)
 */

 interval_nbr= 3;

 /*
 Build scale space
 */

 feature_build_scale_space(
  init_width,
  init_height,
  init_image,
  octave_nbr,
  interval_nbr,
  sigma,
  &gauss_pyr_image,
  &gauss_pyr_width,
  &gauss_pyr_height
 );

 /*
 Build the Difference of Gaussians (DoG) space
 */

 feature_build_dog_space(
  octave_nbr,
  interval_nbr,
  gauss_pyr_image,
  gauss_pyr_width,
  gauss_pyr_height,
  &dog_pyr_image
 );

 /*
 Get the features
 */

 feature_detect_features(
  octave_nbr,
  interval_nbr,
  gauss_pyr_image,
  gauss_pyr_width,
  gauss_pyr_height,
  dog_pyr_image,
  &feat_arr,
  &feat_nbr
 );

 /*
 Get the scale (sigma) for each feature
 */

 feature_compute_features_sigma(
  interval_nbr,
  sigma,
  feat_arr,
  feat_nbr
 );

 if ( image_doubling_flag == 1 ) {

    /*
    Adjust the features to account for initial image doubling
    */

    feature_adjust_features_image_doubling(
     interval_nbr,
     sigma,
     feat_arr,
     feat_nbr
    );
 }

 /*
 Compute orientation histogram for each feature and
 potentially add features if peak high enough
 */

 feature_compute_features_orientation_histogram(
  octave_nbr,
  interval_nbr,
  gauss_pyr_image,
  gauss_pyr_width,
  gauss_pyr_height,
  dog_pyr_image,
  &feat_arr,
  &feat_nbr
 );

 /*
 Compute the descriptors for each feature
 */

 feature_compute_descriptors(
  octave_nbr,
  interval_nbr,
  gauss_pyr_image,
  gauss_pyr_width,
  gauss_pyr_height,
  dog_pyr_image,
  feat_arr,
  feat_nbr
 );

 /*
 Free gauss_pyr_image
 */

 for ( octave= 0 ; octave< octave_nbr ; octave++ ) {
    for ( interval= 0 ; interval< interval_nbr+3 ; interval++ ) {
       free(gauss_pyr_image[octave][interval]);
    }
    free(gauss_pyr_image[octave]);
 }
 free(gauss_pyr_image);

 /*
 Free gauss_pyr_width
 */

 if ( octave_nbr > 0 )
  free(gauss_pyr_width);

 /*
 Free gauss_pyr_height
 */

 if ( octave_nbr > 0 )
  free(gauss_pyr_height);

 /*
 Free dog_pyr_image
 */

 for ( octave= 0 ; octave< octave_nbr ; octave++ ) {
    for ( interval= 0 ; interval< interval_nbr+2 ; interval++ ) {
       free(dog_pyr_image[octave][interval]);
    }
    free(dog_pyr_image[octave]);
 }
 free(dog_pyr_image);

 /*
 Free image_rgb
 */

 free(image_rgb);

 /*
 Free init_image
 */

 free(init_image);

 (*pfeat_arr)= feat_arr;
 (*pfeat_nbr)= feat_nbr;

 return 0;

}
