#include "header.h"
#include "proto.h"

void rectify_compute_rotation(
 double theta,
 char axis,
 double rot_mat[9]
)

/*
Compute rotation around given axis
*/

{

 if ( axis == 'x' ) {
    rot_mat[0*3+0] =  1;
    rot_mat[0*3+1] =  0;
    rot_mat[0*3+2] =  0;

    rot_mat[1*3+0] =  0;
    rot_mat[1*3+1] =  cos(theta);
    rot_mat[1*3+2] = -sin(theta);

    rot_mat[2*3+0] =  0;
    rot_mat[2*3+1] =  sin(theta);
    rot_mat[2*3+2] =  cos(theta);
 }
 else if ( axis == 'y' ) {
    rot_mat[0*3+0] =  cos(theta);
    rot_mat[0*3+1] =  0;
    rot_mat[0*3+2] = -sin(theta);

    rot_mat[1*3+0] =  0;
    rot_mat[1*3+1] =  1;
    rot_mat[1*3+2] =  0;

    rot_mat[2*3+0] =  sin(theta);
    rot_mat[2*3+1] =  0;
    rot_mat[2*3+2] =  cos(theta);
 }
 else if ( axis == 'z' ) {
    rot_mat[0*3+0] =  cos(theta);
    rot_mat[0*3+1] = -sin(theta);
    rot_mat[0*3+2] =  0;

    rot_mat[1*3+0] =  sin(theta);
    rot_mat[1*3+1] =  cos(theta);
    rot_mat[1*3+2] =  0;

    rot_mat[2*3+0] =  0;
    rot_mat[2*3+1] =  0;
    rot_mat[2*3+2] =  1;
 }
 else {
    er9b_error_handler("rectify_compute_rotation");
 }

}
