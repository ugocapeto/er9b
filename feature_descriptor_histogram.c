#include "header.h"
#include "proto.h"

double ***feature_descriptor_histogram(
 int width,
 int height,
 double *image,
 int inp_i,
 int inp_j,
 double ori,
 double feature_sigma,
 int descr_width,
 int hist_nbr
)

/*
descr_width is the numbr of row/cols of the descriptor array
hist_nbr is the size of the histogram stored
for each cell of the descriptor array
*/

{

 double pi= acos(-1);
 double pi2= pi*2;
 double descriptor_sigma_factor;
 double ***hist_arr;
 int hist_i;
 int hist_j;
 double cos_t;
 double sin_t;
 double bins_per_rad;
 double exp_denom;
 double spacing;
 int radius;
 int i;
 int j;
 double j_rot;
 double i_rot;
 double descr_i_dbl;
 double descr_j_dbl;
 double hist_ind_dbl;
 double grad_mag;
 double grad_ori;
 double weight;
 int err_flag;
 double sigma;
 double radius_dbl;

 hist_arr= (double ***)calloc(descr_width,sizeof(double **));
 for ( hist_i= 0 ; hist_i< descr_width ; hist_i++ ) { 
    hist_arr[hist_i]= (double **)calloc(descr_width,sizeof(double *));
    for ( hist_j= 0 ; hist_j< descr_width ; hist_j++ ) { 
       hist_arr[hist_i][hist_j]= (double *)calloc(hist_nbr,sizeof(double));
    }
 }

 descriptor_sigma_factor= 3.0;

 cos_t= cos(ori);
 sin_t= sin(ori);
 bins_per_rad= (double)hist_nbr/pi2;
 sigma= 0.5*(double)descr_width;
 exp_denom= 2*sigma*sigma;
 spacing= descriptor_sigma_factor*feature_sigma;
 radius_dbl= spacing * sqrt(2) * ((double)descr_width+1) * 0.5;
 radius= (int)(radius_dbl+0.5);

 for ( i= -radius ; i<= radius ; i++ ) {
    for ( j= -radius ; j<= radius ; j++ ) {

       /*
       Rotate the sample location
       so that the sample is in the coordinate system of the feature
       (j_rot,i_rot) is the coordinate of the sample
       in the coordinate system of the feature
       */

       j_rot= j*cos_t - i*sin_t;
       i_rot= j*sin_t + i*cos_t;

       /*
       Divide by the spacing,
       which is the width/height of the cells of the descriptor array,
       to get the index into that array
       */

       j_rot/= spacing;
       i_rot/= spacing;

       /*
       Adjust the index
       so that it's w/r to top left corner of the descriptor array
       */

       descr_i_dbl= i_rot + (double)descr_width/2;
       descr_j_dbl= j_rot + (double)descr_width/2;

       /*
       Subtract 0.5
       */

       descr_i_dbl-= 0.5;
       descr_j_dbl-= 0.5;

       /*
       Check if rotated sample now in descriptor array index coordinates
       is physically in the descriptor window
       */

       if ( descr_i_dbl > -1.0 && descr_i_dbl < descr_width &&
            descr_j_dbl > -1.0 && descr_j_dbl < descr_width ) {

          /*
          Rotated sample is in the descriptor
          */
 
          /*
          Compute the gradient magnitude and orientation
          of the sample using the unrotated coordinates
          */

          err_flag= feature_gradient_magnitude_orientation(
           width,
           height,
           image,
           inp_i+i,
           inp_j+j,
           &grad_mag,
           &grad_ori
          );

          if ( err_flag == 1 ) {

             /*
             Could not compute the magnitude and orientation of the gradient
             */

             /*
             Do nothing!
             */

             continue;
          }

          /*
          Recall that the orientation returned is between -pi and +pi
          */

          /*
          Make it to be between 0 and 2pi
          */

          if ( grad_ori < 0 )
           grad_ori+= pi2;

          /*
          The gradient orientation must be w/r to the feature orientation
          */

          grad_ori-= ori;

          /*
          Make sure the gradient orientation is still between 0 and 2pi
          */

          while (grad_ori < 0.0 )
           grad_ori+= pi2;
          while (grad_ori >= pi2 )
           grad_ori-= pi2;

          /*
          Compute index of gradient orientation into the histogram
          */

          hist_ind_dbl= grad_ori*bins_per_rad;

          /*
          Compute the weight
          to be given to the gradient magnitude
          */

          weight= exp(-(j_rot*j_rot+i_rot*i_rot)/exp_denom);

          /*
          Add the gradient magnitude to the descriptor array
          using trilinear interpolation
          */

          feature_descriptor_histogram_interpolate(
           hist_arr,
           descr_i_dbl,
           descr_j_dbl,
           hist_ind_dbl,
           grad_mag*weight,
           descr_width,
           hist_nbr
          );
       }
    }
 }

 return hist_arr;

}
