#include "header.h"
#include "proto.h"

double interpolate_bicubic(
 double *I,
 double x,
 double y,
 int xdim,
 int ydim
)

/*
Interpolate the value of the intensity at (x,y)
*/

/*
x is assumed to be between 0 and (xdim-1)
0 <= x <= (xdim-1)
y is assumed to be between 0 and (ydim-1)
0 <= y <= (ydim-1)
*/

{

 int i0;
 int i1;
 int i2;
 int i3;
 int j0;
 int j1;
 int j2;
 int j3;
 double p00;
 double p01;
 double p02;
 double p03;
 double p10;
 double p11;
 double p12;
 double p13;
 double p20;
 double p21;
 double p22;
 double p23;
 double p30;
 double p31;
 double p32;
 double p33;
 double q0;
 double q1;
 double q2;
 double q3;
 double f;

 /*
 Recall that x is the horizontal coordinate
 going from left to right
 Recall that y is the vertical coordinate
 going from top to bottom
 It is assumed that 0 <= x <= (xdim-1)
 It is assumed that 0 <= y <= (ydim-1)
 */

 if ( !(x >= 0) )
  er9b_error_handler("er9b_downsample_image");
 if ( !(x <= (xdim-1)) )
  er9b_error_handler("er9b_downsample_image");
 if ( !(y >= 0) )
  er9b_error_handler("er9b_downsample_image");
 if ( !(y <= (ydim-1)) )
  er9b_error_handler("er9b_downsample_image");

 /*
 i is gonna represent the row
 j is gonna represent the column
 */

 /*
 Let's gather the 4x4 matrix of points
 Recall that (x,y) is supposed to lie somewhere
 in the p11,p12,p21,p22 square
 */

 i1= (int)y;
 if ( i1 == (ydim-1) )
  i1--;
 i0= i1-1;
 i2= i1+1;
 i3= i2+1;

 j1= (int)x;
 if ( j1 == (xdim-1) )
  j1--;
 j0= j1-1;
 j2= j1+1;
 j3= j2+1;

 /*
 Repeat the point if out of bounds
 */

 if ( i0 == -1 )
  i0= i1;
 if ( i3 == ydim )
  i3= i2;
 if ( j0 == -1 )
  j0= j1;
 if ( j3 == xdim )
  j3= j2;

 /*
 Row 0
 */

 p00= I[xdim*i0+j0];
 p01= I[xdim*i0+j1];
 p02= I[xdim*i0+j2];
 p03= I[xdim*i0+j3];

 /*
 Row 1
 */

 p10= I[xdim*i1+j0];
 p11= I[xdim*i1+j1];
 p12= I[xdim*i1+j2];
 p13= I[xdim*i1+j3];

 /*
 Row 2
 */

 p20= I[xdim*i2+j0];
 p21= I[xdim*i2+j1];
 p22= I[xdim*i2+j2];
 p23= I[xdim*i2+j3];

 /*
 Row 3
 */

 p30= I[xdim*i3+j0];
 p31= I[xdim*i3+j1];
 p32= I[xdim*i3+j2];
 p33= I[xdim*i3+j3];

 /*
 Let's first interpolate along the columns
 */

 /*
 Column 0
 */

 q0= interpolate_cubic(
  p00,
  p10,
  p20,
  p30,
  y-i1
 );

 /*
 Column 1
 */

 q1= interpolate_cubic(
  p01,
  p11,
  p21,
  p31,
  y-i1
 );

 /*
 Column 2
 */

 q2= interpolate_cubic(
  p02,
  p12,
  p22,
  p32,
  y-i1
 );

 /*
 Column 3
 */

 q3= interpolate_cubic(
  p03,
  p13,
  p23,
  p33,
  y-i1
 );

 /*
 Finally, interpolate horizontally
 */ 

 f= interpolate_cubic(
  q0,
  q1,
  q2,
  q3,
  x-j1
 );

 return f;

}
