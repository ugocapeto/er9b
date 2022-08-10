#include "header.h"
#include "proto.h"

int match_feature(
 feat_struct inp_feat,
 feat_struct *feat_arr,
 int feat_nbr
)

{

 int inp_octave;
 int inp_interval;
 int inp_i;
 int inp_j;
 double inp_xinterval;
 double inp_xi;
 double inp_xj;
 double inp_pos_x;
 double inp_pos_y;
 double inp_sigma;
 double inp_sigma_octave;
 double inp_ori;
 double *inp_descr;
 int inp_descr_nbr;
 double min_dist_squared1;
 double min_dist_squared2;
 int min_feat_ind1;
 int min_feat_ind2;
 int feat_ind;
 feat_struct feat;
 int octave;
 int interval;
 int i;
 int j;
 double xinterval;
 double xi;
 double xj;
 double pos_x;
 double pos_y;
 double sigma;
 double sigma_octave;
 double ori;
 double *descr;
 int descr_nbr;
 double dist_squared;
 double dist_squared1;
 double dist_squared2;
 int feat_ind1;
 int feat_ind2;
 double ratio;
 double sq_dist_ratio_thresh;
 double min_dist_squared2_bis;
 int min_feat_ind2_bis;

 inp_octave= inp_feat.octave;
 inp_interval= inp_feat.interval;
 inp_i= inp_feat.i;
 inp_j= inp_feat.j;
 inp_xinterval= inp_feat.xinterval;
 inp_xi= inp_feat.xi;
 inp_xj= inp_feat.xj;
 inp_pos_x= inp_feat.pos_x;
 inp_pos_y= inp_feat.pos_y;
 inp_sigma= inp_feat.sigma;
 inp_sigma_octave= inp_feat.sigma_octave;
 inp_ori= inp_feat.ori;
 inp_descr= inp_feat.descr;
 inp_descr_nbr= inp_feat.descr_nbr;

 /*
 Go through the features in feat_arr
 to find the 2 closest features to the input feature
 1 is the closest
 2 is the next closest
 */

 min_dist_squared1= 1.0e32;
 min_dist_squared2= 1.0e32;
 min_feat_ind1=-1;
 min_feat_ind2=-1;

 for ( feat_ind= 0; feat_ind< feat_nbr ; feat_ind++ ) {
    feat= feat_arr[feat_ind];

    octave= feat.octave;
    interval= feat.interval;
    i= feat.i;
    j= feat.j;
    xinterval= feat.xinterval;
    xi= feat.xi;
    xj= feat.xj;
    pos_x= feat.pos_x;
    pos_y= feat.pos_y;
    sigma= feat.sigma;
    sigma_octave= feat.sigma_octave;
    ori= feat.ori;
    descr= feat.descr;
    descr_nbr= feat.descr_nbr;

    /*
    Compute distance squared between the 2 features
    */

    dist_squared= match_distance_squared(
     inp_feat,
     feat
    );

    if ( dist_squared < min_dist_squared1 ) { 
       min_dist_squared2= min_dist_squared1;
       min_feat_ind2= min_feat_ind1;
       min_dist_squared1= dist_squared;
       min_feat_ind1= feat_ind;
    }
    else if ( dist_squared < min_dist_squared2 ) {
       min_dist_squared2= dist_squared;
       min_feat_ind2= feat_ind;
    }
 }

 /*
 Compute the second closest feature in a different way
 Comment out when not needed!
 */

 /*
 min_dist_squared2_bis= 1.0e32;
 min_feat_ind2_bis=-1;

 for ( feat_ind= 0; feat_ind< feat_nbr ; feat_ind++ ) {
    if ( feat_ind == min_feat_ind1 )
     continue;
    feat= feat_arr[feat_ind];

    octave= feat.octave;
    interval= feat.interval;
    i= feat.i;
    j= feat.j;
    xinterval= feat.xinterval;
    xi= feat.xi;
    xj= feat.xj;
    pos_x= feat.pos_x;
    pos_y= feat.pos_y;
    sigma= feat.sigma;
    sigma_octave= feat.sigma_octave;
    ori= feat.ori;
    descr= feat.descr;
    descr_nbr= feat.descr_nbr;

    dist_squared= match_distance_squared(
     inp_feat,
     feat
    );

    if ( dist_squared < min_dist_squared2_bis ) {
       min_dist_squared2_bis= dist_squared;
       min_feat_ind2_bis= feat_ind;
    }
 }

 if ( min_feat_ind2_bis != min_feat_ind2 ) {
    er9b_error_handler("match_feature");
 }
 */

 dist_squared1= min_dist_squared1;
 dist_squared2= min_dist_squared2;
 feat_ind1= min_feat_ind1;
 feat_ind2= min_feat_ind2;

 /*
 Compute the ratio of the distance squared
 */

 ratio= dist_squared1/dist_squared2;

 sq_dist_ratio_thresh= 0.49;

 if ( ratio < sq_dist_ratio_thresh )
  feat_ind= feat_ind1;
 else
  feat_ind=-1;

 return feat_ind;

}
