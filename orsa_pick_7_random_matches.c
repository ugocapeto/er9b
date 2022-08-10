#include "header.h"
#include "proto.h"

void orsa_pick_7_random_matches(
 int k[7],
 int n
)

{

 int kind;
 double rand_dbl;
 int rand_int;
 int temp_int;
 int kind2;

 for ( kind= 0 ; kind< 7 ; kind++ ) {

    /*
    Generate a pseudo-random double number between 0.0 and 1.0
    */

    rand_dbl= (double)rand()/(double)RAND_MAX;

    /*
    Convert into a pseudo-random integer number between 0 and n-1
    */

    rand_int= (int)( rand_dbl*(double)n + 0.5);

    if ( rand_int == n )
     rand_int= n-1;

    k[kind]= rand_int;
 }

 /*
 Sort w/r to index
 */

 for ( kind= 0 ; kind< 7 ; kind++ ) {
    for ( kind2= kind+1 ; kind2< 7 ; kind2++ ) {
       if ( k[kind2] < k[kind] ) {
          temp_int= k[kind];
          k[kind]= k[kind2];
          k[kind2]= temp_int;
       }
    }
 }

}
