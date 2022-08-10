#include "header.h"
#include "proto.h"

int feature_interpolate_extremum_location_main(
 int octave_nbr,
 int interval_nbr,
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 int img_border,
 int octave,
 int inp_interval,
 int inp_i,
 int inp_j,
 int *pinterval,
 int *pi,
 int *pj,
 double *pxinterval,
 double *pxi,
 double *pxj,
 double *pxdog
)

{

 double max_iter;
 int err_flag;
 int interval;
 int i;
 int j;
 int iter;
 double xinterval;
 double xi;
 double xj;
 double xdog;
 double interval_dbl;
 double i_dbl;
 double j_dbl;

 /*
 Initialize to couldn't compute exact location of extremum
 */

 err_flag= 1;

 /*
 Set max number of iterations
 */

 max_iter= 5;

 /*
 Initialize integer location of extremum
 */

 interval= inp_interval;
 i= inp_i;
 j= inp_j;

 /*
 Initialize extremum location increments
 */

 xinterval= 0;
 xi= 0;
 xj= 0;

 /*
 Initialize extremum value
 */

 xdog= 0;

 for ( iter= 0 ; iter< max_iter ; iter++ ) {

    /*
    Interpolate location of actual extremum
    Returns the offset to apply to integer location
    to correct proper location of extremum
    */

    feature_interpolate_extremum_location(
     gauss_pyr_image,
     gauss_pyr_width,
     gauss_pyr_height,
     dog_pyr_image,
     octave,
     interval,
     i,
     j,
     &xinterval,
     &xi,
     &xj,
     &xdog
    );

    /*
    Check if location is ok
    */

    if ( fabs(xinterval) < 0.5 &&
         fabs(xi) < 0.5 &&
         fabs(xj) < 0.5 ) {

       /*
       Success!
       */

       err_flag= 0;
       break;
    }

    /*
    Update the integer location of the extremum
    */

    interval_dbl= (double)interval+xinterval;
    if ( interval_dbl >= 0 )
     interval= (int)(interval_dbl+0.5);
    else
     interval= (int)(interval_dbl-0.5);

    i_dbl= (double)i+xi;
    if ( i_dbl >= 0 )
     i= (int)(i_dbl+0.5);
    else
     i= (int)(i_dbl-0.5);

    j_dbl= (double)j+xj;
    if ( j_dbl >= 0 )
     j= (int)(j_dbl+0.5);
    else
     j= (int)(j_dbl-0.5);

    /*
    Check that integer location of the extremum is still in bounds
    */

    if ( interval < 1 ||
         interval > interval_nbr ||
         i < img_border ||
         j < img_border ||
         i >= gauss_pyr_height[octave]-img_border ||
         j >= gauss_pyr_width[octave]-img_border ) {
       break;
    }
 }

 (*pinterval)= interval;
 (*pi)= i;
 (*pj)= j;
 (*pxinterval)= xinterval;
 (*pxi)= xi;
 (*pxj)= xj;
 (*pxdog)= xdog;

 return err_flag;

}
