#include "header.h"
#include "proto.h"

void orsa_best_number_false_alarms(
 error_struct *error_arr,
 int match_nbr,
 double logalpha0,
 double loge0,
 double *logcn,
 double *logc7,
 double *pbest_nfa,
 int *pbest_k
)

{

 double best_nfa;
 int best_k;
 int match_ind;
 double error;
 double logalpha;
 double nfa;
 int k;

 /*
 Initialize best nfa
 */

 best_nfa= 1.0e32;
 best_k= 6;

 for ( match_ind= 7 ; match_ind< match_nbr ; match_ind++ ) {
    error= error_arr[match_ind].error;
    logalpha= logalpha0 + 0.5 * log10(error);
    nfa= loge0 +
     logalpha * (double)(match_ind-6) +
     logcn[match_ind+1] +
     logc7[match_ind+1];
    k= match_ind;
    if ( nfa < best_nfa ) {
       best_nfa= nfa;
       best_k= k;
    }
 }

 (*pbest_nfa)= best_nfa;
 (*pbest_k)= best_k;

}
