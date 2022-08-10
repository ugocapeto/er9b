#include "header.h"
#include "proto.h"

double interpolate_cubic(
 double p0,
 double p1,
 double p2,
 double p3,
 double x
)

/*
Do a cubic interpolation for x
representing the parameter (between 0 and 1) of a point
placed between p1 and p2
*/

{

 double f;

 if ( !(x >= 0) )
  er9b_error_handler("cubic_interpolation");
 if ( !(x <= 1) )
  er9b_error_handler("cubic_interpolation");

 f= (-0.5*p0+1.5*p1-1.5*p2+0.5*p3)*x*x*x+
    ( 1.0*p0-2.5*p1+2.0*p2-0.5*p3)*x*x+
    (-0.5*p0       +0.5*p2       )*x+
    (        1.0*p1              );

 return f;

}
