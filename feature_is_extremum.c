#include "header.h"
#include "proto.h"

int feature_is_extremum(
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 int octave,
 int inp_interval,
 int inp_i,
 int inp_j
)

{

 int width;
 int height;
 int inp_pixel;
 double inp_val;
 int interval_offset;
 int interval;
 int i_offset;
 int i;
 int j_offset;
 int j;
 int pixel;
 double val;

 width= gauss_pyr_width[octave];
 height= gauss_pyr_height[octave];
 inp_pixel= inp_i*width+inp_j;
 inp_val= dog_pyr_image[octave][inp_interval][inp_pixel];

 if ( inp_val > 0 ) {

    /*
    Check for maximum
    */

    for ( interval_offset= -1 ; interval_offset<= +1 ; interval_offset++ ) {
       interval= inp_interval+interval_offset;
       for ( i_offset= -1 ; i_offset<= +1 ; i_offset++ ) {
          i= inp_i+i_offset;
          for ( j_offset= -1 ; j_offset<= +1 ; j_offset++ ) {
             j= inp_j+j_offset;
             pixel= i*width+j;
             val= dog_pyr_image[octave][interval][pixel];
             if ( inp_val < val )
              return 0;
          }
       }
    }
 }
 else {

    /*
    Check for minimum
    */

    for ( interval_offset= -1 ; interval_offset<= +1 ; interval_offset++ ) {
       interval= inp_interval+interval_offset;
       for ( i_offset= -1 ; i_offset<= +1 ; i_offset++ ) {
          i= inp_i+i_offset;
          for ( j_offset= -1 ; j_offset<= +1 ; j_offset++ ) {
             j= inp_j+j_offset;
             pixel= i*width+j;
             val= dog_pyr_image[octave][interval][pixel];
             if ( inp_val > val )
              return 0;
          }
       }
    }
 }

 return 1;

}
