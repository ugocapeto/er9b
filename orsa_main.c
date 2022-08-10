#include "header.h"
#include "proto.h"

static int compare_match(
 const void *p1,
 const void *p2
)

/*
It's a lexicographical comparison
Compare x1, then y1, then x2, and then y2 
*/

{

 /*
 Compare x1
 */

 if ( ((match_struct *)p1)->x1 < ((match_struct *)p2)->x1 )
  return -1;
 if ( ((match_struct *)p1)->x1 > ((match_struct *)p2)->x1 )
  return +1;

 /*
 If here, same x1
 */

 /*
 Compare y1
 */

 if ( ((match_struct *)p1)->y1 < ((match_struct *)p2)->y1 )
  return -1;
 if ( ((match_struct *)p1)->y1 > ((match_struct *)p2)->y1 )
  return +1;

 /*
 If here, same x1 and same y1
 */

 /*
 Compare x2
 */

 if ( ((match_struct *)p1)->x2 < ((match_struct *)p2)->x2 )
  return -1;
 if ( ((match_struct *)p1)->x2 > ((match_struct *)p2)->x2 )
  return +1;

 /*
 If here, same x1, same y1, and same x2
 */

 /*
 Compare y2
 */

 if ( ((match_struct *)p1)->y2 < ((match_struct *)p2)->y2 )
  return -1;
 if ( ((match_struct *)p1)->y2 > ((match_struct *)p2)->y2 )
  return +1;

 /*
 If here, same x1, same y1, same x2, and same y2
 */

 return 0;

}

int orsa_main(
 int width,
 int height,
 char *filename_match,
 char *filename_good_match,
 char *filename_F,
 int ntrials,
 unsigned long seed
)

{

 FILE *fp;
 int match_nbr;
 match_struct *match_arr;
 int match_ind;
 double x1;
 double y1;
 double x2;
 double y2;
 int match2_nbr;
 match_struct *match2_arr;
 int dup_flag;
 int prev_match_ind;
 double prev_x1;
 double prev_y1;
 double prev_x2;
 double prev_y2;
 double dup_tol;
 double N[3*3];
 double norm;
 double normalized_x1;
 double normalized_y1;
 double normalized_x2;
 double normalized_y2;
 int ind;
 double logalpha0;
 double loge0;
 double *logcn;
 double *logc7;
 int random7[7];
 int sample7[7];
 double F_arr[3*9];
 int iter;
 int F_nbr;
 int F_ind;
 int i;
 double F[3*3];
 double best_nfa;
 int best_k;
 int *inliers_arr;
 int inliers_nbr;
 int match2_ind;
 double error_max;
 error_struct *error_arr;
 double min_nfa;
 double bestF[3*3];
 double FN[3*3];
 double Nt[3*3];
 double denormalized_F[3*3];
 double denormalized_error_max;
 match_struct *backup_match_arr;
 int vec_index_nbr;
 int *vec_index_arr;
 int max_iter;
 int optim;
 int better;
 int optimized_orsa= 0;
 int feat1_ind;
 int feat2_ind;
 int prev_feat1_ind;
 int prev_feat2_ind;
 int j;

 /*
 Read the file containing the matches
 Put the matches in match_arr
 */

 fp= fopen(filename_match,"r");

 match_nbr= 0;
 match_arr= 0;

 while ( fscanf(fp,"%d %lg %lg %d %lg %lg",
          &feat1_ind,&x1,&y1,&feat2_ind,&x2,&y2) == 6 ) {
    if ( match_nbr == 0 ) {
       match_arr= (match_struct *)calloc(match_nbr+1,sizeof(match_struct));
    }
    else {
       match_arr= (match_struct *)realloc(match_arr,(match_nbr+1)*sizeof(match_struct));
    }
    match_arr[match_nbr].feat1_ind= feat1_ind;
    match_arr[match_nbr].x1= x1;
    match_arr[match_nbr].y1= y1;
    match_arr[match_nbr].feat2_ind= feat2_ind;
    match_arr[match_nbr].x2= x2;
    match_arr[match_nbr].y2= y2;
    match_nbr++;
 }

 fclose(fp);

 /*
 Initialize seed for random number generator
 */

 srand(seed);

 /*
 Sort the matches lexicographically using library function qsort()
 */

 qsort(
  match_arr,
  match_nbr,
  sizeof(match_struct),
  compare_match
 );

 /*
 Print the matches after the sort
 to make sure it's correctly sorted
 */

 /*
 for ( match_ind= 0 ; match_ind< match_nbr ; match_ind++ ) {
    feat1_ind= match_arr[match_ind].feat1_ind;
    x1= match_arr[match_ind].x1;
    y1= match_arr[match_ind].y1;
    feat2_ind= match_arr[match_ind].feat2_ind;
    x2= match_arr[match_ind].x2;
    y2= match_arr[match_ind].y2;
    fprintf(stdout,"feat1_ind= %d x1= %g y1= %g feat2_ind= %d x2= %g y2= %g\n",
     feat1_ind,x1,y1,feat2_ind,x2,y2);
 }
 */

 /*
 Process the matches and get rid of duplicate matches
 Put the matches in match2_arr
 */

 match2_nbr= 0;
 match2_arr= 0;

 for ( match_ind= 0 ; match_ind< match_nbr ; match_ind++ ) {
    feat1_ind= match_arr[match_ind].feat1_ind;
    x1= match_arr[match_ind].x1;
    y1= match_arr[match_ind].y1;
    feat2_ind= match_arr[match_ind].feat2_ind;
    x2= match_arr[match_ind].x2;
    y2= match_arr[match_ind].y2;

    /*
    Since the match array has been sorted,
    duplicate matches are adjacent in the match array
    */

    /*
    See if this match is a duplicate
    by looking at previous match
    */

    dup_flag= 0;
    prev_match_ind= match_ind-1;
    if ( prev_match_ind >= 0 ) {
       prev_feat1_ind= match_arr[prev_match_ind].feat1_ind;
       prev_x1= match_arr[prev_match_ind].x1;
       prev_y1= match_arr[prev_match_ind].y1;
       prev_feat2_ind= match_arr[prev_match_ind].feat2_ind;
       prev_x2= match_arr[prev_match_ind].x2;
       prev_y2= match_arr[prev_match_ind].y2;
       /*
       if ( prev_x1 == x1 &&
            prev_y1 == y1 &&
            prev_x2 == x2 &&
            prev_y2 == y2 ) {
          dup_flag= 1;
       }
       */ 
       dup_tol= 1.0e-12;
       if ( fabs(x1-prev_x1) < dup_tol*(double)width &&
            fabs(y1-prev_y1) < dup_tol*(double)height &&
            fabs(x2-prev_x2) < dup_tol*(double)width &&
            fabs(y2-prev_y2) < dup_tol*(double)height ) {
          dup_flag= 1;
       }
    }

    if ( dup_flag == 1 )
     continue;

    /*
    If here,
    not a duplicate
    */

    if ( match2_nbr == 0 ) {
       match2_arr= (match_struct *)calloc(match2_nbr+1,sizeof(match_struct));
    }
    else {
       match2_arr= (match_struct *)realloc(match2_arr,(match2_nbr+1)*sizeof(match_struct));
    }
    match2_arr[match2_nbr].feat1_ind= feat1_ind;
    match2_arr[match2_nbr].x1= x1;
    match2_arr[match2_nbr].y1= y1;
    match2_arr[match2_nbr].feat2_ind= feat2_ind;
    match2_arr[match2_nbr].x2= x2;
    match2_arr[match2_nbr].y2= y2;
    match2_nbr++;
 }

 /*
 Replace match_arr by match2_arr
 */

 if ( match_nbr > 0 )
  free(match_arr);

 match_nbr= match2_nbr;
 match_arr= match2_arr;

 fprintf(stdout," Number of matches (after removal of duplicates)= %d\n",match_nbr);

 /*
 Check that there are enough matches
 */

 if ( match_nbr <= 7 ) {
    fprintf(stdout," More than 7 matches are needed!\n");
    return 1;
 }

 /*
 Backup the matches before normalization
 */

 backup_match_arr= (match_struct *)calloc(match_nbr,sizeof(match_struct));

 for ( match_ind= 0 ; match_ind< match_nbr ; match_ind++ ) {
    feat1_ind= match_arr[match_ind].feat1_ind;
    x1= match_arr[match_ind].x1;
    y1= match_arr[match_ind].y1;
    feat2_ind= match_arr[match_ind].feat2_ind;
    x2= match_arr[match_ind].x2;
    y2= match_arr[match_ind].y2;
    backup_match_arr[match_ind].feat1_ind= feat1_ind;
    backup_match_arr[match_ind].x1= x1;
    backup_match_arr[match_ind].y1= y1;
    backup_match_arr[match_ind].feat2_ind= feat2_ind;
    backup_match_arr[match_ind].x2= x2;
    backup_match_arr[match_ind].y2= y2;
 }

 /*
 Normalize the coordinates of the matches
 */

 norm= 1 / sqrt( (double)width * (double)height );

 for ( match_ind= 0 ; match_ind< match_nbr ; match_ind++ ) {
    feat1_ind= match_arr[match_ind].feat1_ind;
    x1= match_arr[match_ind].x1;
    y1= match_arr[match_ind].y1;
    feat2_ind= match_arr[match_ind].feat2_ind;
    x2= match_arr[match_ind].x2;
    y2= match_arr[match_ind].y2;

    normalized_x1= ( x1 - 0.5 * (double)width ) * norm;
    normalized_y1= ( y1 - 0.5 * (double)height ) * norm;
    normalized_x2= ( x2 - 0.5 * (double)width ) * norm;
    normalized_y2= ( y2 - 0.5 * (double)height ) * norm;

    match_arr[match_ind].x1= normalized_x1;
    match_arr[match_ind].y1= normalized_y1;
    match_arr[match_ind].x2= normalized_x2;
    match_arr[match_ind].y2= normalized_y2;
 }

 /*
 Compute normalization matrix N
 */

 N[0*3+0]= norm;
 N[0*3+1]= 0;
 N[0*3+2]= -0.5 * (double)width * norm;
 N[1*3+0]= 0;
 N[1*3+1]= norm;
 N[1*3+2]= -0.5 * (double)height * norm;
 N[2*3+0]= 0;
 N[2*3+1]= 0;
 N[2*3+2]= 1;

 /*
 fprintf(stdout,"N=");
 for ( ind= 0 ; ind< 3*3 ; ind++ )
  fprintf(stdout," %g",N[ind]);
 fprintf(stdout,"\n");
 */

 /*
 Compute log proba of random data term to have error at most 1 pixel
 */

 logalpha0= log10(2)+
  0.5*log10( ((double)width*(double)width + (double)height*(double)height) /
             ((double)width * (double)height) );

 /*
 Pre-compute log probas
 */

 loge0= log10( 3 * ((double)match_nbr-7) );

 logcn= (double *)calloc(match_nbr+1,sizeof(double));
 for ( ind= 0 ; ind<= match_nbr ; ind++ ) {
    logcn[ind]= orsa_log_combi(ind,match_nbr);
 }

 /*
 fprintf(stdout,"logcn=");
 for ( ind= 0 ; ind< match_nbr+1 ; ind++ )
  fprintf(stdout," %g",logcn[ind]);
 fprintf(stdout,"\n");
 */

 logc7= (double *)calloc(match_nbr+1,sizeof(double));
 for ( ind= 0 ; ind<= match_nbr ; ind++ ) {
    logc7[ind]= orsa_log_combi(7,ind);
 }

 /*
 fprintf(stdout,"logc7=");
 for ( ind= 0 ; ind< match_nbr+1 ; ind++ )
  fprintf(stdout," %g",logc7[ind]);
 fprintf(stdout,"\n");
 */

 vec_index_nbr= match_nbr;
 vec_index_arr= (int *)calloc(vec_index_nbr,sizeof(int));
 for ( match_ind= 0 ; match_ind< match_nbr ; match_ind++ )
  vec_index_arr[match_ind]= match_ind;

 if ( optimized_orsa == 1 ) {

    /*
    Reduce the number of trials by 10%
    We'll add those back when we have found a meaningful model
    */

    max_iter = ntrials - ntrials/10;
 }
 else {
    max_iter = ntrials;
 }

 iter= 0;

 min_nfa= 1.0e32;

 optim= 0;

 inliers_arr= 0;
 inliers_nbr= 0;

 /*
 Allocate memory for errors
 */

 error_arr= (error_struct *)calloc(match_nbr,sizeof(error_struct));

 START:

 iter++;

 /*
 Pick 7 matches at random
 */

 orsa_pick_7_random_matches(
  random7,
  vec_index_nbr
 );

 for ( ind= 0 ; ind< 7 ; ind++ )
  sample7[ind]= vec_index_arr[ random7[ind] ];

 /*
 Get the fundamental matrices
 Either 1 fundamental matrix is returned or 3
 */

 F_nbr= orsa_epipolar(
  match_arr,
  match_nbr,
  sample7,
  F_arr
 );

 /*
 Loop on 1 fundamental matrix or 3
 */

 /*
 for ( F_ind= 0 ; F_ind< F_nbr ; F_ind++ ) {
 */
 for ( F_ind= F_nbr-1 ; F_ind>= 0 ; F_ind-- ) {

    for ( i= 0 ; i< 9 ; i++ )
     F[i]= F_arr[F_ind*9+i];

    /*
    fprintf(stdout,"F=");
    for ( ind= 0 ; ind< 9 ; ind++ )
     fprintf(stdout," %g",F[ind]);
    fprintf(stdout,"\n");
    */

    /*
    Compute the errors for all matches and sort them
    */

    orsa_compute_sort_errors(
     match_arr,
     match_nbr,
     F,
     error_arr
    );

    /*
    Compute the best nfa (number of false alarms)
    */

    orsa_best_number_false_alarms(
     error_arr,
     match_nbr,
     logalpha0,
     loge0,
     logcn,
     logc7,
     &best_nfa,
     &best_k
    );

    /*
    Initialize to
    haven't found a better model 
    */

    better= 0;

    if ( best_nfa < min_nfa ) {

       /*
       Have found a better model
       */

       better= 1;

       min_nfa= best_nfa;

       fprintf(stdout," iter= %d log(nfa)= %g\n",iter,min_nfa);

       /*
       Free inliers_arr
       */

       if ( inliers_nbr > 0 )
        free(inliers_arr);

       /*
       Update the inliers
       */

       inliers_nbr= best_k+1;
       inliers_arr= (int *)calloc(inliers_nbr,sizeof(int));

       for ( match2_ind= 0 ; match2_ind<= best_k ; match2_ind++ ) {
          match_ind= error_arr[match2_ind].match_ind;
          inliers_arr[match2_ind]= match_ind;
       }

       error_max= error_arr[best_k].error;

       /* 
       Update optimum fundamental matrix
       */

       for ( i= 0 ; i< 9 ; i++ )
        bestF[i]= F[i];
    } 

    if ( optimized_orsa == 1 ) {

       if ( (better == 1 && min_nfa < 0) ||
            (iter == max_iter && !optim) ) {

          /*
          We either have found a meaningful model or
          we have gone through 90% of trials
          */

          if ( !optim ) {

             /*
             Add back the 10% iterations we took out
             */

             optim= 1;
             max_iter= ntrials;
          }

          /*
          From now on,
          we are gonna pick samples from the inliers
          */

          if ( vec_index_nbr > 0 )
           free(vec_index_arr);

          vec_index_nbr= inliers_nbr;
          vec_index_arr= (int *)calloc(vec_index_nbr,sizeof(int));
          for ( match2_ind= 0 ; match2_ind< vec_index_nbr ; match2_ind++ )
           vec_index_arr[match2_ind]= inliers_arr[match2_ind];;
       }
    }
 } /* loop on the fundamental matrices */

 /*
 Let's see if we are done
 */

 if ( iter < max_iter )
  goto START;

 error_max= sqrt(error_max); 

 /*
 Denormalize the max error
 */

 denormalized_error_max= error_max/norm;

 fprintf(stdout," Number of inliers = %d\n",inliers_nbr);
 fprintf(stdout," Max error = %g\n",denormalized_error_max);

 /*
 Denormalize the best fundamental matrix
 F = Nt * F * N
 */

 for ( i= 0 ; i< 9 ; i++ )
  F[i]= bestF[i];

 math_matrix_matrix_product(
  F,
  3,
  3,
  N,
  3,
  3,
  FN
 );

 math_matrix_transpose(
  N,
  3,
  3,
  Nt
 );

 math_matrix_matrix_product(
  Nt,
  3,
  3,
  FN,
  3,
  3,
  denormalized_F
 );

 fprintf(stdout," Best F = [");
 fprintf(stdout," %g %g %g;",
  denormalized_F[0*3+0],denormalized_F[0*3+1],denormalized_F[0*3+2]);
 fprintf(stdout," %g %g %g;",
  denormalized_F[1*3+0],denormalized_F[1*3+1],denormalized_F[1*3+2]);
 fprintf(stdout," %g %g %g ]\n",
  denormalized_F[2*3+0],denormalized_F[2*3+1],denormalized_F[2*3+2]);

 /*
 Write the denormalized F
 */

 fp= fopen(filename_F,"w"); 

 for ( i= 0 ; i< 3 ; i++ ) {
    for ( j= 0 ; j< 3 ; j++ ) {
       fprintf(fp,"%g ",denormalized_F[i*3+j]);
    }
 }

 fclose(fp);

 /*
 Write the good matches
 */

 fp= fopen(filename_good_match,"w");

 for ( match2_ind= 0 ; match2_ind< inliers_nbr ; match2_ind++ ) {
    match_ind= inliers_arr[match2_ind];
    feat1_ind= backup_match_arr[match_ind].feat1_ind;
    x1= backup_match_arr[match_ind].x1;
    y1= backup_match_arr[match_ind].y1;
    feat2_ind= backup_match_arr[match_ind].feat2_ind;
    x2= backup_match_arr[match_ind].x2;
    y2= backup_match_arr[match_ind].y2;
    fprintf(fp,"%d ",feat1_ind);
    fprintf(fp,"%g ",x1);
    fprintf(fp,"%g ",y1);
    fprintf(fp,"%d ",feat2_ind);
    fprintf(fp,"%g ",x2);
    fprintf(fp,"%g ",y2);
    fprintf(fp,"\n");
 }

 fclose(fp);

 /*
 Free match_arr
 */

 if ( match_nbr > 0 )
  free(match_arr);

 /*
 Free backup_match_arr
 */

 if ( match_nbr > 0 )
  free(backup_match_arr);

 /*
 Free logcn
 */

 if ( match_nbr+1 > 0 )
  free(logcn);

 /*
 Free logc7
 */

 if ( match_nbr+1 > 0 )
  free(logc7);

 /*
 Free vec_index_arr
 */

 if ( vec_index_nbr > 0 )
  free(vec_index_arr);

 /*
 Free error_arr
 */

 if ( match_nbr > 0 )
  free(error_arr);

 /*
 Free inliers_arr
 */

 if ( inliers_nbr > 0 )
  free(inliers_arr);

 return 0;

}
