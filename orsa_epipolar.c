#include "header.h"
#include "proto.h"

int orsa_epipolar(
 match_struct *match_arr,
 int match_nbr,
 int match7_ind[7],
 double *F_arr
)

/*
F_arr is of size 3*9
since there can bee either 1 fundamental matrix found or 3
*/

{

 double A[7*9];
 double F1[3*3];
 double F2[3*3];
 double a[4];
 double z[3];
 int match_ind;
 double x1;
 double y1;
 double x2;
 double y2;
 double *U;
 double *w;
 double *V;
 int i;
 int F_nbr;
 int ind;

 /*
 Build the 7x9 matrix from the 7 matches
 */

 for ( match_ind= 0 ; match_ind< 7 ; match_ind++ ) {
    x1= match_arr[match7_ind[match_ind]].x1;
    y1= match_arr[match7_ind[match_ind]].y1;
    x2= match_arr[match7_ind[match_ind]].x2;
    y2= match_arr[match7_ind[match_ind]].y2;

    A[match_ind*9+0]= x1 * x2;
    A[match_ind*9+1]= y1 * x2;
    A[match_ind*9+2]=      x2;
    A[match_ind*9+3]= x1 * y2;
    A[match_ind*9+4]= y1 * y2;
    A[match_ind*9+5]=      y2;
    A[match_ind*9+6]= x1;
    A[match_ind*9+7]= y1;
    A[match_ind*9+8]= 1.;
 }

 /*
 fprintf(stdout,"A=");
 for ( ind= 0 ; ind< 7*9 ; ind++ )
  fprintf(stdout," %g",A[ind]);
 fprintf(stdout,"\n");
 */

 /*
 Perform singular value decomposition
 */

 /*
 Allocate memory for U
 */

 U= (double *)calloc(7*9,sizeof(double));

 /*
 Allocate memory for w
 */

 w= (double *)calloc(9,sizeof(double));

 /*
 Allocate memory for V
 */

 V= (double *)calloc(9*9,sizeof(double));

 math_singular_value_decomposition(
  7,
  9,
  A,
  U,
  w,
  V
 );

 /*
 Solution space is of dimension 2
 The basis vectors are F1 and F2 
 Any linear combination of F1 and F2 is a proper solution
 but we are looking for the solution that is singular
 */

 for ( i= 0 ; i< 9 ; i++ )
  F1[i]= V[i*9+7];

 /*
 fprintf(stdout,"F1=");
 for ( ind= 0 ; ind< 9 ; ind++ )
  fprintf(stdout," %g",F1[ind]);
 fprintf(stdout,"\n");
 */

 for ( i= 0 ; i< 9 ; i++ )
  F2[i]= V[i*9+8];

 /*
 fprintf(stdout,"F2=");
 for ( ind= 0 ; ind< 9 ; ind++ )
  fprintf(stdout," %g",F2[ind]);
 fprintf(stdout,"\n");
 */

 for ( i= 0 ; i< 9 ; i++ )
  F2[i]-= F1[i];

 /*
 fprintf(stdout,"F2=");
 for ( ind= 0 ; ind< 9 ; ind++ )
  fprintf(stdout," %g",F2[ind]);
 fprintf(stdout,"\n");
 */

 /*
 Build the cubic polynomial
 P(x)=det(F1+xF2)
 We are gonna solve for P(x)=0
 that is get the fundamental matrix that is singular (detF=0)
 */

 orsa_characteristic_polynomial(
  F1,
  F2,
  a
 );

 /*
 fprintf(stdout,"a=");
 for ( ind= 0 ; ind< 4 ; ind++ )
  fprintf(stdout," %g",a[ind]);
 fprintf(stdout,"\n");
 */

 /*
 Find the roots of the cubic polynomial
 (either 1 real solution or 3)
 */

 F_nbr= orsa_find_cubic_roots(
  a,
  z
 );

 /*
 fprintf(stdout,"z=");
 for ( ind= 0 ; ind< 3 ; ind++ )
  fprintf(stdout," %g",z[ind]);
 fprintf(stdout,"\n");
 */

 for ( ind= 0 ; ind< F_nbr ; ind++ ) {
    for ( i= 0 ; i< 9 ; i++ )
     F_arr[ind*9+i]= F1[i] + z[ind]*F2[i];
 }

 /*
 Free U
 */

 free(U);

 /*
 Free w
 */

 free(w);

 /*
 Free V
 */

 free(V);

 return F_nbr;

}
