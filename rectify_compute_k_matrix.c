#include "header.h"
#include "proto.h"

void rectify_compute_k_matrix(
 int w,
 int h,
 double f,
 double k_mat[9]
)

{

 k_mat[0*3+0]= f;
 k_mat[0*3+1]= 0;
 k_mat[0*3+2]= (double)w/2;

 k_mat[1*3+0]= 0;
 k_mat[1*3+1]= f;
 k_mat[1*3+2]= (double)h/2;

 k_mat[2*3+0]= 0;
 k_mat[2*3+1]= 0;
 k_mat[2*3+2]= 1;

}
