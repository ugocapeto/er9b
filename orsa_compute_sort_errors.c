#include "header.h"
#include "proto.h"

static int compare_error(
 const void *p1,
 const void *p2
)

{

 if ( ((error_struct *)p1)->error < ((error_struct *)p2)->error )
  return -1;
 if ( ((error_struct *)p1)->error > ((error_struct *)p2)->error )
  return +1;

 return 0;

}

void orsa_compute_sort_errors(
 match_struct *match_arr,
 int match_nbr,
 double F[3*3],
 error_struct *error_arr
)

{

 double a;
 double b;
 double c;
 double d;
 int match_ind;
 double x1;
 double y1;
 double x2;
 double y2;
 double error;
 int match2_ind;

 for ( match_ind= 0 ; match_ind< match_nbr ; match_ind++ ) {
    x1= match_arr[match_ind].x1;
    y1= match_arr[match_ind].y1;
    x2= match_arr[match_ind].x2;
    y2= match_arr[match_ind].y2;

    /*
    Compute the error for this match
    The error is defined as the distance between (x2,y2)
    and the epipolar line induced by (x1,y1)
    */

        a = F[0*3+0]*x1+F[0*3+1]*y1+F[0*3+2];
        b = F[1*3+0]*x1+F[1*3+1]*y1+F[1*3+2];
        c = F[2*3+0]*x1+F[2*3+1]*y1+F[2*3+2];
        d = a*x2 + b*y2 + c;
        error= (d*d)/(a*a+b*b);
        error_arr[match_ind].error= error;
        error_arr[match_ind].match_ind= match_ind;
 }

 /*
 Sort w/r to increasing errors
 */

 qsort(
  error_arr,
  match_nbr,
  sizeof(error_struct),
  compare_error
 );

 /*
 Print the errors after the sort
 to make sure it's correctly sorted
 */

 /*
 for ( match2_ind= 0 ; match2_ind< match_nbr ; match2_ind++ ) {
    error= error_arr[match2_ind].error;
    match_ind= error_arr[match2_ind].match_ind;
    fprintf(stdout,"error= %g match_ind= %d\n",
     error,match_ind);
 }
 */

}
