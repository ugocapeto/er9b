#include "header.h"
#include "proto.h"

void feature_adjust_features_image_doubling(
 int interval_nbr,
 double inp_sigma,
 feat_struct *feat_arr,
 int feat_nbr
)

{

 feat_struct feat;
 int feat_ind;

 for ( feat_ind= 0 ; feat_ind< feat_nbr ; feat_ind++ ) {
    feat= feat_arr[feat_ind];
    feat.pos_x/= 2;
    feat.pos_y/= 2;
    feat.sigma/= 2;
    feat_arr[feat_ind]= feat;
 }

}
