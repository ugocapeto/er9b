#include "header.h"
#include "proto.h"

void feature_descriptor_normalize(
 feat_struct *feat
)

{

 double val;
 double len_inv;
 double len_sq;
 int descr_ind;
 int descr_nbr;

 descr_nbr= feat->descr_nbr;

 len_sq= 0.0;
 for ( descr_ind= 0 ; descr_ind< descr_nbr ; descr_ind++ ) {
    val = feat->descr[descr_ind];
    len_sq += val*val;
 }
 len_inv = 1.0 / sqrt( len_sq );

 for ( descr_ind= 0 ; descr_ind< descr_nbr ; descr_ind++ ) {
    feat->descr[descr_ind] *= len_inv;
 }

}
