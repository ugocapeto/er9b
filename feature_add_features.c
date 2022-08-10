#include "header.h"
#include "proto.h"

void feature_add_features(
 feat_struct feat,
 double *hist_arr,
 int hist_nbr,
 double mag_thresh,
 feat_struct **pfeat_arr,
 int *pfeat_nbr
)

{

 double pi=acos(-1);
 double pi2= pi*2;
 int octave;
 int interval;
 int i;
 int j;
 double xinterval;
 double xi;
 double xj;
 double sigma;
 double sigma_octave;
 feat_struct *feat_arr;
 int feat_nbr;
 int hist_ind;
 int hist_ind_l;
 int hist_ind_r;
 double l;
 double c;
 double r;
 double val_dbl;
 double ori;
 double hist_ind_peak_dbl;

 octave= feat.octave;
 interval= feat.interval;
 i= feat.i;
 j= feat.j;
 xinterval= feat.xinterval;
 xi= feat.xi;
 xj= feat.xj;
 sigma= feat.sigma;
 sigma_octave= feat.sigma_octave;

 feat_arr= (*pfeat_arr);
 feat_nbr= (*pfeat_nbr);

 for ( hist_ind= 0 ; hist_ind< hist_nbr ; hist_ind++ ) {

    /*
    Get left histogram index
    */

    hist_ind_l= hist_ind-1;
    if ( hist_ind_l == -1 )
     hist_ind_l= hist_nbr-1;

    /*
    Get right histogram index
    */

    hist_ind_r= hist_ind+1;
    if ( hist_ind_r == hist_nbr )
     hist_ind_r= 0;

    /*
    Check if we have a peak
    */

    if ( hist_arr[hist_ind] > hist_arr[hist_ind_l] &&
         hist_arr[hist_ind] > hist_arr[hist_ind_r] &&
         hist_arr[hist_ind] >= mag_thresh ) {

       /*
       Fit a parabola to the left, center, and right magnitudes
       to get exact orientation for the peak
       */

       l= hist_arr[hist_ind_l];
       c= hist_arr[hist_ind];
       r= hist_arr[hist_ind_r];

       val_dbl= 0.5*(l-r)/(l-2*c+r);

       hist_ind_peak_dbl= (double)hist_ind+val_dbl;

       if ( hist_ind_peak_dbl < (double)0 )
        hist_ind_peak_dbl+= (double)hist_nbr;
       if ( hist_ind_peak_dbl >= (double)hist_nbr )
        hist_ind_peak_dbl-= (double)hist_nbr;

       /*
       Compute corresponding orientation
       which goes from 0 to 2pi
       */

       ori= pi2*hist_ind_peak_dbl/(double)hist_nbr;

       /*
       Add the input feature
       */

       feature_add_feature(
        octave,
        interval,
        i,
        j,
        xinterval,
        xi,
        xj,
        sigma,
        sigma_octave,
        ori,
        (double *)0,
        (int )0,
        &feat_arr,
        &feat_nbr
       );
    }
 }

 (*pfeat_arr)= feat_arr;
 (*pfeat_nbr)= feat_nbr;

}
