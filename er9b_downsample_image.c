#include "header.h"
#include "proto.h"

void er9b_downsample_image(
 double *inp_I,
 int inp_xdim,
 int inp_ydim,
 double *out_I,
 int out_xdim,
 int out_ydim,
 double factor
)

/*
The output image must be allocated outside the function
*/

{

 int out_i;
 int out_j;
 int inp_i;
 int inp_j;

 for ( out_i= 0 ; out_i< out_ydim ; out_i++ ) {
    for ( out_j= 0 ; out_j< out_xdim ; out_j++ ) {

       /*
       Get the coordinates in the input image
       */

       inp_i= (int)( (double)out_i*factor );

       if ( inp_i < 0 )
        inp_i= 0;
       if ( inp_i > inp_ydim-1 )
        inp_i= inp_ydim-1;

       inp_j= (int)( (double)out_j*factor );

       if ( inp_j < 0 )
        inp_j= 0;
       if ( inp_j > inp_xdim-1 )
        inp_j= inp_xdim-1;

       out_I[out_i*out_xdim+out_j]= inp_I[inp_i*inp_xdim+inp_j];
    }
 }

}
