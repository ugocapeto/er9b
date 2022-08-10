#include "header.h"
#include "proto.h"

void feature_build_scale_space(
 int inp_width,
 int inp_height,
 double *inp_image,
 int octave_nbr,
 int interval_nbr,
 double inp_sigma,
 double ****pgauss_pyr_image,
 int **pgauss_pyr_width,
 int **pgauss_pyr_height
)

{

 double ***gauss_pyr_image;
 int *gauss_pyr_width;
 int *gauss_pyr_height;
 double k_factor;
 int octave;
 double *sig;
 int interval;
 int i;
 int j;
 int width;
 int height;
 int pixel;
 double factor;
 int new_width;
 int new_height;
 double sigma;
 int precision;

 gauss_pyr_image= (double ***)calloc(octave_nbr,sizeof(double **));
 gauss_pyr_width= (int *)calloc(octave_nbr,sizeof(int));
 gauss_pyr_height= (int *)calloc(octave_nbr,sizeof(int));

 for ( octave= 0 ; octave< octave_nbr ; octave++ ) {
    gauss_pyr_image[octave]= (double **)calloc(interval_nbr+3,sizeof(double *));
 }

 /*
 Compute sigma for each interval using
 sigma_total^2 = sigma[interval]^2 + sigma[interval-1]^2
 */

 sig= (double *)calloc(interval_nbr+3,sizeof(double));

 k_factor = pow(2,1/(double)interval_nbr);

 /*
 Compute the incremental sigma for each interval
 */

 sig[0]= inp_sigma;
 sig[1]= inp_sigma * sqrt(k_factor*k_factor-1);
 for ( interval= 2 ; interval< interval_nbr+3 ; interval++ )
  sig[interval]= sig[interval-1]*k_factor;

 /*
 for ( interval= 0 ; interval< interval_nbr+3 ; interval++ ) {
    fprintf(stdout,"interval= %d sigma (incremental)= %g\n",
     interval,sig[interval]);
 }
 */

 for ( octave= 0 ; octave< octave_nbr ; octave++ ) {
    for ( interval= 0 ; interval< interval_nbr+3 ; interval++ ) {
       if ( octave == 0 && interval == 0 ) {

          /*
          Copy input image
          */

          width= inp_width;
          height= inp_height;

          gauss_pyr_image[octave][interval]= (double *)calloc(width*height,sizeof(double));
          for ( i= 0 ; i< height ; i++ ) {
             for ( j= 0 ; j< width ; j++ ) {
                pixel= i*width+j;
                gauss_pyr_image[octave][interval][pixel]= inp_image[pixel];
             }
          }

          /*
          Store width and height for that octave
          */

          gauss_pyr_width[octave]= width;
          gauss_pyr_height[octave]= height;
       } 
       else if ( interval == 0 ) {

          /*
          Downsample image from previous octave
          */

          width= gauss_pyr_width[octave-1];
          height= gauss_pyr_height[octave-1];

          factor= 2.0;

          er9b_downsample_image_dimensions(
           width,
           height,
           &new_width,
           &new_height,
           factor
          );

          gauss_pyr_image[octave][interval]= (double *)calloc(new_width*new_height,sizeof(double));

          er9b_downsample_image(
           gauss_pyr_image[octave-1][interval_nbr],
           width,
           height,
           gauss_pyr_image[octave][interval],
           new_width,
           new_height,
           factor
          );

          /*
          Store width and height for that octave
          */

          gauss_pyr_width[octave]= new_width;
          gauss_pyr_height[octave]= new_height;
       }
       else {

          /*
          Apply a Gaussian blur to the previous image in the octave
          */

          width= gauss_pyr_width[octave];
          height= gauss_pyr_height[octave];

          gauss_pyr_image[octave][interval]= (double *)calloc(width*height,sizeof(double));

          sigma= sig[interval];
          precision= 5;
          gaussian_blur_image(
           gauss_pyr_image[octave][interval-1],
           width,
           height,
           sigma,
           precision,
           gauss_pyr_image[octave][interval]
          );
       }
    }
 }

 /*
 Free sig
 */

 if ( interval_nbr+3 > 0 )
  free(sig);

 (*pgauss_pyr_image)= gauss_pyr_image;
 (*pgauss_pyr_width)= gauss_pyr_width;
 (*pgauss_pyr_height)= gauss_pyr_height;

}
