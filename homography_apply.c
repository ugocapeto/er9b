#include "header.h"
#include "proto.h"

void homography_apply( 
 double H_mat[9],
 double x,
 double y,
 double *px2,
 double *py2
)

{

 double m[3];
 double m2[3];
 double x2;
 double y2;

 m[0]= x;
 m[1]= y;
 m[2]= 1;

 math_matrix_vector_product(
  H_mat,
  3,
  3,
  m,
  3,
  m2
 );

 x2= m2[0]/m2[2];
 y2= m2[1]/m2[2];

 (*px2)= x2;
 (*py2)= y2;

}
