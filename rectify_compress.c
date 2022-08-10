#include "header.h"
#include "proto.h"

int rectify_compress(
 double JtJ[6*6],
 double B[6],
 double JtJ2[6*6],
 double B2[6],
 int row_to_row2[6]
)

/*
Gets rid of rows/cols where you only have zeros
Returns the new number of rows/cols
*/

{

 double max;
 double epsilon_kernel=1.0e-9;
 int i;
 int i2;
 int j;
 int j2;
 int n2;

 /*
 Initialize JtJ2
 */

 for ( i= 0 ; i< 6 ; i++ ) {
    for ( j= 0 ; j< 6 ; j++ ) {
       JtJ2[i*6+j]= 0;
    }
 }

 /*
 Initialize B2
 */

 for ( i= 0 ; i< 6 ; i++ ) {
    B2[i]= 0;
 }

 /*
 Initialize row_to_row2
 */

 for ( i= 0 ; i< 6 ; i++ ) {
    row_to_row2[i]= i;
 }

 max= 0;
 for ( i= 0 ; i< 6 ; i++ ) {
    if ( JtJ[i*6+i] > max )
     max= JtJ[i*6+i];
 }
 max*= epsilon_kernel;

 /*
 Initialize the new number of rows/cols
 */

 n2= 0;

 /*
 See if rows are gonna stay
 Update n2 and row_to_row2
 */

 for ( i= 0 ; i< 6 ; i++ ) {

   /*
   Let's see if that row is gonna stay
   */

   if ( JtJ[i*6+i] > max ) {

      /*
      This row is gonna stay
      */

      n2++; 
      continue;
   }

   /*
   This row is gonna be removed
   */

   /*
   Update row_to_row2
   */

   row_to_row2[i]= -1;
   for ( i2= i+1 ; i2< 6 ; i2++ )
    row_to_row2[i2]--;
 }

 /*
 Now that we know the new number of rows/cols,
 we can fill JtJ2 and B2
 */

 for ( i= 0 ; i< 6 ; i++ ) {

    /*
    Get the new row index
    */

    i2= row_to_row2[i];

    /*
    See if that row has been eliminated
    */

    if ( i2 == -1 ) {

       /*
       This row is gone
       */

       continue;
    }

    /*
    This row stays
    Basically, row/col i becomes row/col i2
    */

    for ( j= 0 ; j< 6 ; j++ ) {

       /*
       Get the new col index
       using row_to_row2
       */

       j2= row_to_row2[j]; 

       /*
       See if that col has been eliminated
       */

       if ( j2 == -1 ) {

          /*
          This col is gone
          */

          continue;
       }

       /*
       This column stays
       Basically, (i,j) becomes (i2,j2)
       */

       JtJ2[i2*n2+j2]= JtJ[i*6+j];
       B2[i2]= B[i];
    }
 }

 return n2;

}
