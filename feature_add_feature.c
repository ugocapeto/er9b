#include "header.h"
#include "proto.h"

void feature_add_feature(
 int octave,
 int interval,
 int i,
 int j,
 double xinterval,
 double xi,
 double xj,
 double sigma,
 double sigma_octave,
 double ori,
 double *descr,
 int descr_nbr,
 feat_struct **pfeat_arr,
 int *pfeat_nbr
)

{

 feat_struct *feat_arr;
 int feat_nbr;

 feat_arr= (*pfeat_arr);
 feat_nbr= (*pfeat_nbr);

 if ( feat_nbr == 0 ) {
    feat_arr= (feat_struct *)calloc(feat_nbr+1,sizeof(feat_struct));
 }
 else {
    feat_arr= (feat_struct *)realloc(feat_arr,(feat_nbr+1)*sizeof(feat_struct));
 }

 feat_arr[feat_nbr].octave= octave;
 feat_arr[feat_nbr].interval= interval;
 feat_arr[feat_nbr].i= i;
 feat_arr[feat_nbr].j= j;
 feat_arr[feat_nbr].xinterval= xinterval;
 feat_arr[feat_nbr].xi= xi;
 feat_arr[feat_nbr].xj= xj;
 feat_arr[feat_nbr].sigma= sigma;
 feat_arr[feat_nbr].sigma_octave= sigma_octave;
 feat_arr[feat_nbr].ori= ori;
 feat_arr[feat_nbr].descr= descr;
 feat_arr[feat_nbr].descr_nbr= descr_nbr;

 /*
 Compute position w/r to original image and store
 */

 feat_arr[feat_nbr].pos_x= ((double)j+xj)*pow(2,(double)octave);
 feat_arr[feat_nbr].pos_y= ((double)i+xi)*pow(2,(double)octave);

 feat_nbr++;

 (*pfeat_arr)= feat_arr;
 (*pfeat_nbr)= feat_nbr;

}
