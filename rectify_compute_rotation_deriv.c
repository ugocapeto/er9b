#include "header.h"
#include "proto.h"

void rectify_compute_rotation_deriv(
 double theta,
 char axis,
 double rot_mat_deriv[9]
)

/*
Compute rotation around given axis
*/

{

 double pi=acos(-1);

 if ( axis == 'x' ) {
    rot_mat_deriv[0*3+0] =  0;
    rot_mat_deriv[0*3+1] =  0;
    rot_mat_deriv[0*3+2] =  0;

    rot_mat_deriv[1*3+0] =  0;
    rot_mat_deriv[1*3+1] =  cos(theta+pi/2);
    rot_mat_deriv[1*3+2] = -sin(theta+pi/2);

    rot_mat_deriv[2*3+0] =  0;
    rot_mat_deriv[2*3+1] =  sin(theta+pi/2);
    rot_mat_deriv[2*3+2] =  cos(theta+pi/2);
 }
 else if ( axis == 'y' ) {
    rot_mat_deriv[0*3+0] =  cos(theta+pi/2);
    rot_mat_deriv[0*3+1] =  0;
    rot_mat_deriv[0*3+2] = -sin(theta+pi/2);

    rot_mat_deriv[1*3+0] =  0;
    rot_mat_deriv[1*3+1] =  0;
    rot_mat_deriv[1*3+2] =  0;

    rot_mat_deriv[2*3+0] =  sin(theta+pi/2);
    rot_mat_deriv[2*3+1] =  0;
    rot_mat_deriv[2*3+2] =  cos(theta+pi/2);
 }
 else if ( axis == 'z' ) {
    rot_mat_deriv[0*3+0] =  cos(theta+pi/2);
    rot_mat_deriv[0*3+1] = -sin(theta+pi/2);
    rot_mat_deriv[0*3+2] =  0;

    rot_mat_deriv[1*3+0] =  sin(theta+pi/2);
    rot_mat_deriv[1*3+1] =  cos(theta+pi/2);
    rot_mat_deriv[1*3+2] =  0;

    rot_mat_deriv[2*3+0] =  0;
    rot_mat_deriv[2*3+1] =  0;
    rot_mat_deriv[2*3+2] =  0;
 }
 else {
    er9b_error_handler("rectify_compute_rotation_deriv");
 }

}
