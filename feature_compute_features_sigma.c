#include "header.h"
#include "proto.h"

void feature_compute_features_sigma(
 int interval_nbr,
 double inp_sigma,
 feat_struct *feat_arr,
 int feat_nbr
)

{

 feat_struct feat;
 double interval_dbl;
 int feat_ind;
 int octave;
 int interval;
 int i;
 int j;
 double xinterval;
 double xi;
 double xj;
 double sigma;
 double sigma_octave;

 for ( feat_ind= 0 ; feat_ind< feat_nbr ; feat_ind++ ) {
    feat= feat_arr[feat_ind];
    octave= feat.octave;
    interval= feat.interval;
    i= feat.i;
    j= feat.j;
    xinterval= feat.xinterval;
    xi= feat.xi;
    xj= feat.xj;

    interval_dbl= (double)interval+xinterval;

    /*
    Compute sigma from base of pyramid
    */

    sigma= inp_sigma * pow(2,(double)octave+interval_dbl/(double)interval_nbr);
    feat.sigma= sigma;

    /*
    Compute sigma from base of pyramid for the octave
    */

    sigma_octave= inp_sigma * pow(2,interval_dbl/(double)interval_nbr);
    feat.sigma_octave= sigma_octave;

    feat_arr[feat_ind]= feat;
 }

}
