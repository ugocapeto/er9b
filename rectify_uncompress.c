#include "header.h"
#include "proto.h"

void rectify_uncompress(
 double X2[6],
 int row_to_row2[6],
 double X[6]
)

/*
Given row i in original vector,
i2= row_to_row2[i] gives the row in compressed vector
if i2 == -1, the row has been eliminated in the new vector
*/

{

 int i;
 int i2;

 /*
 Initialize X to 0
 */

 for ( i= 0 ; i< 6 ; i++ )
  X[i]= 0;

 for ( i= 0 ; i< 6 ; i++ ) {

    /*
    Get corresponding row i2 in compressed vector X2
    */

    i2= row_to_row2[i];

    /*
    See if that row has been eliminated
    */

    if ( i2 == -1 ) {

       /*
       This row is gone
       0 is the proper solution in uncompressed vector X
       */

       continue;
    }

    /*
    Update X
    */

    X[i]= X2[i2];
 }

}
