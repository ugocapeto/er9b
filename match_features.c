#include "header.h"
#include "proto.h"

void match_features(
 feat_struct *feat1_arr,
 int feat1_nbr,
 feat_struct *feat2_arr,
 int feat2_nbr,
 match_struct **pmatch_arr,
 int *pmatch_nbr
)

{

 int octave1;
 int interval1;
 int i1;
 int j1;
 double xinterval1;
 double xi1;
 double xj1;
 double pos_x1;
 double pos_y1;
 double sigma1;
 double sigma_octave1;
 double ori1;
 double *descr1;
 int descr_nbr1;
 int octave2;
 int interval2;
 int i2;
 int j2;
 double xinterval2;
 double xi2;
 double xj2;
 double pos_x2;
 double pos_y2;
 double sigma2;
 double sigma_octave2;
 double ori2;
 double *descr2;
 int descr_nbr2;
 int feat1_ind;
 int feat2_ind;
 feat_struct feat1;
 feat_struct feat2;
 int match_nbr;
 match_struct *match_arr;

 match_arr= 0;
 match_nbr= 0;

 for ( feat1_ind= 0; feat1_ind< feat1_nbr ; feat1_ind++ ) {
    feat1= feat1_arr[feat1_ind];

    octave1= feat1.octave;
    interval1= feat1.interval;
    i1= feat1.i;
    j1= feat1.j;
    xinterval1= feat1.xinterval;
    xi1= feat1.xi;
    xj1= feat1.xj;
    pos_x1= feat1.pos_x;
    pos_y1= feat1.pos_y;
    sigma1= feat1.sigma;
    sigma_octave1= feat1.sigma_octave;
    ori1= feat1.ori;
    descr1= feat1.descr;
    descr_nbr1= feat1.descr_nbr;

    /*
    Find matching feature in feat2_arr
    */

    feat2_ind= match_feature(
     feat1,
     feat2_arr,
     feat2_nbr
    );

    if ( feat2_ind == -1 )
     continue;

    feat2= feat2_arr[feat2_ind];

    octave2= feat2.octave;
    interval2= feat2.interval;
    i2= feat2.i;
    j2= feat2.j;
    xinterval2= feat2.xinterval;
    xi2= feat2.xi;
    xj2= feat2.xj;
    pos_x2= feat2.pos_x;
    pos_y2= feat2.pos_y;
    sigma2= feat2.sigma;
    sigma_octave2= feat2.sigma_octave;
    ori2= feat2.ori;
    descr2= feat2.descr;
    descr_nbr2= feat2.descr_nbr;

    if ( match_nbr == 0 ) {
       match_arr= (match_struct *)calloc(match_nbr+1,sizeof(match_struct));
    }
    else {
       match_arr= (match_struct *)realloc(match_arr,(match_nbr+1)*4*sizeof(match_struct));
    }
    match_arr[match_nbr].feat1_ind= feat1_ind;
    match_arr[match_nbr].x1= pos_x1;
    match_arr[match_nbr].y1= pos_y1;
    match_arr[match_nbr].feat2_ind= feat2_ind;
    match_arr[match_nbr].x2= pos_x2;
    match_arr[match_nbr].y2= pos_y2;
    match_nbr++;
 }

 (*pmatch_arr)= match_arr;
 (*pmatch_nbr)= match_nbr;

}
