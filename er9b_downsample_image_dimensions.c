#include "header.h"
#include "proto.h"

void er9b_downsample_image_dimensions(
 int inp_xdim,
 int inp_ydim,
 int *pout_xdim,
 int *pout_ydim,
 double factor
)

{

 int out_xdim;
 int out_ydim;

 out_xdim= (int)( (double)inp_xdim/factor );
 out_ydim= (int)( (double)inp_ydim/factor );

 (*pout_xdim)= out_xdim;
 (*pout_ydim)= out_ydim;

}
