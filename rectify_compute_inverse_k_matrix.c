#include "header.h"
#include "proto.h"

void rectify_compute_inverse_k_matrix(
 int w,
 int h,
 double f,
 double inv_k_mat[9]
)

{

 inv_k_mat[0*3+0]= 1/f;
 inv_k_mat[0*3+1]= 0;
 inv_k_mat[0*3+2]=-(double)w/(2*f);

 inv_k_mat[1*3+0]= 0;
 inv_k_mat[1*3+1]= 1/f;
 inv_k_mat[1*3+2]=-(double)h/(2*f);

 inv_k_mat[2*3+0]= 0;
 inv_k_mat[2*3+1]= 0;
 inv_k_mat[2*3+2]= 1;

}
