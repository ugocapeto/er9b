#include "header.h"
#include "proto.h"

int match_main(
 char *filename_image1,
 char *filename_image2,
 char *filename_match
)

{

 FILE *fp;
 double sigma;
 feat_struct *feat1_arr;
 feat_struct *feat2_arr;
 int feat1_nbr;
 int feat2_nbr;
 match_struct *match_arr;
 int match_nbr;
 int match_ind;
 int err_flag;
 int feat_ind;
 int descr_nbr;
 double *descr;

 /*
 Get the features in image 1
 */

 sigma= 1.6;
 err_flag= feature_main(
  filename_image1,
  sigma,
  &feat1_arr,
  &feat1_nbr
 );

 fprintf(stdout," Number of features in image 1 = %d\n",feat1_nbr);

 feature_show_features(
  filename_image1,
  feat1_arr,
  feat1_nbr,
  "feat1.png"
 );

 /*
 Get the features in image 2
 */

 sigma= 1.6;
 err_flag= feature_main(
  filename_image2,
  sigma,
  &feat2_arr,
  &feat2_nbr
 );

 fprintf(stdout," Number of features in image 2 = %d\n",feat2_nbr);

 feature_show_features(
  filename_image2,
  feat2_arr,
  feat2_nbr,
  "feat2.png"
 );

 /*
 Match the features
 */

 match_features(
  feat1_arr,
  feat1_nbr,
  feat2_arr,
  feat2_nbr,
  &match_arr,
  &match_nbr
 );

 fprintf(stdout," Number of matches = %d\n",match_nbr);

 /*
 Write the matches
 */

 fp= fopen(filename_match,"w");

 for ( match_ind= 0 ; match_ind< match_nbr ; match_ind++ ) {
    fprintf(fp,"%d ",match_arr[match_ind].feat1_ind);
    fprintf(fp,"%g ",match_arr[match_ind].x1);
    fprintf(fp,"%g ",match_arr[match_ind].y1);
    fprintf(fp,"%d ",match_arr[match_ind].feat2_ind);
    fprintf(fp,"%g ",match_arr[match_ind].x2);
    fprintf(fp,"%g ",match_arr[match_ind].y2);
    fprintf(fp,"\n");
 }

 fclose(fp);

 /*
 Show the matches in input rgb images
 */

 match_show_matches(
  filename_image1,
  filename_image2,
  filename_match,
  "match1.png",
  "match2.png"
 );

 /*
 Free the features in image 1
 */

 for ( feat_ind= 0 ; feat_ind< feat1_nbr ; feat_ind++ ) {
    descr_nbr= feat1_arr[feat_ind].descr_nbr;
    descr= feat1_arr[feat_ind].descr;
    if ( descr_nbr > 0 )
     free(descr);
 }
 if ( feat1_nbr > 0 )
  free(feat1_arr);

 /*
 Free the features in image 2
 */

 for ( feat_ind= 0 ; feat_ind< feat2_nbr ; feat_ind++ ) {
    descr_nbr= feat2_arr[feat_ind].descr_nbr;
    descr= feat2_arr[feat_ind].descr;
    if ( descr_nbr > 0 )
     free(descr);
 }
 if ( feat2_nbr > 0 )
  free(feat2_arr);

 /*
 Free match_arr
 */

 if ( match_nbr > 0 )
  free(match_arr);

 return 0;

}
