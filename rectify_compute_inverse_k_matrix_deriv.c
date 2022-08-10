#include "header.h"
#include "proto.h"

void rectify_compute_inverse_k_matrix_deriv(
 int w,
 int h,
 double f,
 double inv_k_mat_deriv[9]
)

{

 int i;
 int j;

 inv_k_mat_deriv[0*3+0]= 1/f;
 inv_k_mat_deriv[0*3+1]= 0;
 inv_k_mat_deriv[0*3+2]=-(double)w/(2*f);

 inv_k_mat_deriv[1*3+0]= 0;
 inv_k_mat_deriv[1*3+1]= 1/f;
 inv_k_mat_deriv[1*3+2]=-(double)h/(2*f);

 inv_k_mat_deriv[2*3+0]= 0;
 inv_k_mat_deriv[2*3+1]= 0;
 inv_k_mat_deriv[2*3+2]= 0;

 for ( i= 0 ; i< 3 ; i++ ) {
    for ( j= 0 ; j< 3 ; j++ ) {
       inv_k_mat_deriv[i*3+j]*= (-log(3));
    }
 }

}
