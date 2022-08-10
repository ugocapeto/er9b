#include "header.h"
#include "proto.h"

int feature_gradient_magnitude_orientation(
 int width,
 int height,
 double *image,
 int i,
 int j,
 double *pmag,
 double *pori
)

{

 double mag;
 double ori;
 double dx;
 double dy;
 int err_flag;

 mag= 0;
 ori= 0;

 if ( i > 0 && i < height-1 && j > 0 && j < width-1 ) {

    /*
    x is going in the same direction as j, that is,
    from left to right
    */

    dx= image[i*width+j+1]-image[i*width+j-1];

    /*
    y is going in the opposite direction as i, that is,
    from bottom to top
    */

    dy= image[(i-1)*width+j]-image[(i+1)*width+j];

    mag= sqrt(dx*dx+dy*dy);

    /*
    ori is going counter-clockwise
    range is -pi to pi (thanks to atan2)
    */

    ori= atan2(dy,dx);

    err_flag= 0;
 }
 else {
    err_flag= 1;
 }

 (*pmag)= mag;
 (*pori)= ori;

 return err_flag;

}
