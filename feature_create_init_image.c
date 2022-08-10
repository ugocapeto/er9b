#include "header.h"
#include "proto.h"

void feature_create_init_image(
 int width,
 int height,
 int *image_rgb,
 double init_sigma,
 int image_doubling_flag,
 int *pinit_width,
 int *pinit_height,
 double **pinit_image
)

/*
Input is a rgb image
where the intensity for each channel
is an integer between 0 and 255 
The output (init_image) is a grayscale image
where the intensity is a double precision number between 0 and 1
*/

/*
If image_doubling_flag is 1,
the input image is enlarged by a factor of 2
*/

{

 double *init_image;
 double sig_diff;
 int precision;
 int i;
 int j;
 int pixel;
 int init_width;
 int init_height;
 double *grayscale_image;
 double cur_sigma;

 /*
 Convert the rgb image into a grayscale image
 with a double precision intensity that varies from 0 to 255
 */

 grayscale_image= (double *)calloc(width*height,sizeof(double));

 rgb_to_grayscale(
  width,
  height,
  image_rgb,
  grayscale_image
 );

 /*
 Normalize the intensities to be between 0 and 1
 */

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       pixel= i*width+j;
       grayscale_image[pixel]/= 255;
       if ( grayscale_image[pixel] < 0 )
        grayscale_image[pixel]= 0;
       if ( grayscale_image[pixel] > 1 )
        grayscale_image[pixel]= 1;
    }
 }

 if ( image_doubling_flag == 1 ) {

    /*
    Image doubling is on
    */

    /*
    Enlarge the grayscale image by a factor of 2 
    */

    init_width= width*2;
    init_height= height*2;

    init_image= (double *)calloc(init_width*init_height,sizeof(double));

    /*
    upsample_image(
     grayscale_image,
     width,
     height,
     init_image,
     init_width,
     init_height,
    );
    */
 }
 else {

    /*
    Image doubling is off
    */

    /*
    Copy the grayscale image
    */

    init_width= width;
    init_height= height;

    init_image= (double *)calloc(init_width*init_height,sizeof(double));

    for ( i= 0 ; i< init_height ; i++ ) {
       for ( j= 0 ; j< init_width ; j++ ) {
          pixel= i*init_width+j; 
          init_image[pixel]= grayscale_image[pixel];
       }
    }
 }

 /*
 It is assumed the input image has already been smoothed
 with a sigma equal to cur_sigma
 */

 cur_sigma= 0.5;

 if ( image_doubling_flag == 1 ) {

    /*
    Multiply the current sigma by 2
    */

    cur_sigma*= 2;

 }

 /*
 Apply Gaussian filter to init image
 so that the total sigma is equal to sigma
 */

 sig_diff= sqrt(init_sigma*init_sigma-cur_sigma*cur_sigma);
 precision= 5;
 gaussian_blur_image(
  init_image,
  init_width,
  init_height,
  sig_diff,
  precision,
  init_image
 );

 /*
 Free grayscale_image
 */

 free(grayscale_image);

 (*pinit_width)= init_width;
 (*pinit_height)= init_height;
 (*pinit_image)= init_image;

}
