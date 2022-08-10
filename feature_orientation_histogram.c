#include "header.h"
#include "proto.h"

double *feature_orientation_histogram(
 int width,
 int height,
 double *image,
 int inp_i,
 int inp_j,
 int hist_nbr,
 int radius,
 double sigma
)

{

 double *hist_arr;
 double pi= acos(-1);
 double pi2= pi*2;
 int i_offset;
 int i;
 int j_offset;
 int j;
 double dist2;
 int err_flag;
 double mag;
 double ori;
 double weight;
 double hist_ind_dbl;
 int hist_ind;
 double exp_denom;

 /*
 Allocate memory for the histogram
 */

 hist_arr= (double *)calloc(hist_nbr,sizeof(double));

 exp_denom= 2*sigma*sigma;

 for ( i_offset= -radius ; i_offset<= radius ; i_offset++ ) {
    i= inp_i+i_offset;
    for ( j_offset= -radius ; j_offset<= radius ; j_offset++ ) {
       j= inp_j+j_offset;

       /*
       Compute the gradient magnitude and orientation
       */

       err_flag= feature_gradient_magnitude_orientation(
        width,
        height,
        image,
        i,
        j,
        &mag,
        &ori
       );

       if ( err_flag == 1 ) {

          /*
          Could not compute the magnitude and orientation of the gradient
          */

          continue;
       }

       /*
       ori as returned is between -pi and +pi
       but we want ori to go from 0 to 2pi
       */

       if ( ori < 0 )
        ori+= pi2;

       /*
       Compute the weight
       */

       dist2= (double)i_offset*(double)i_offset+
              (double)j_offset*(double)j_offset;
       weight= exp(-dist2/exp_denom);

       /*
       Get the histogram index (bin) the orientation falls in
       */

       hist_ind_dbl= (double)hist_nbr * ori / pi2;
       hist_ind= (int)(hist_ind_dbl+0.5);
       if ( !(hist_ind < hist_nbr) )
        hist_ind= 0;

       /*
       Add the weighted magnitude to the bin
       */

       hist_arr[hist_ind]+= weight * mag;
    }
 }

 return hist_arr;

}
