#include "header.h"
#include "proto.h"

double match_distance_squared(
 feat_struct feat1,
 feat_struct feat2
)

{

 double *descr1;
 double *descr2;
 int descr_nbr1;
 int descr_nbr2;
 double dist_squared;
 int descr_ind;
 double diff;

 descr1= feat1.descr;
 descr_nbr1= feat1.descr_nbr;
 descr2= feat2.descr;
 descr_nbr2= feat2.descr_nbr;

 if ( descr_nbr2 != descr_nbr1 ) {
    er9b_error_handler("match_distance_squared");
 }

 dist_squared= 0;
 for ( descr_ind= 0 ; descr_ind< descr_nbr1 ; descr_ind++ ) {
    diff= descr1[descr_ind]-descr2[descr_ind];
    dist_squared+= diff*diff;
 }

 return dist_squared;

}
