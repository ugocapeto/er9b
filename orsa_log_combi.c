#include "header.h"
#include "proto.h"

double orsa_log_combi(
 int k,
 int n
)

{

 double r;
 int i;

 if ( k >= n || k <= 0 ) {
    return 0;
 }

 if ( n-k < k ) {
    k= n-k;
 }

 r= 0;
 for ( i= 1 ; i<= k ; i++ ) {
    r+= log10( (double)(n-i+1) )-
        log10( (double)i );
 }

 return r;

}
