#include "header.h"
#include "proto.h"

int main(
 int argc,
 char* argv[]
)

/*
Same as er9 excepth that here
it's my own implementation
*/

{

 FILE *fp;
 char filename[80];
 char filename1[80];
 char filename2[80];
 char filename1_rect[80];
 char filename2_rect[80];
 char *ext;
 int width;
 int height;
 int *I1_arr;
 int *I2_arr;
 int err_flag;
 int ntrials;
 unsigned long seed;
 double max_mean_error;

 /*
 Let's read in the input file
 */

 fp= fopen("er9b_input.txt","r");

 /*
 Get filename for image 1
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"image 1 (input) = %s\n",filename);

 strcpy(filename1,filename);

 /*
 Get filename for image 2
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"image 2 (input) = %s\n",filename);

 strcpy(filename2,filename);

 /*
 Get filename for rectified image 1
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"rectified image 1 (output) = %s\n",filename);

 strcpy(filename1_rect,filename);

 /*
 Get filename for rectified image 2
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"rectified image 2 (output) = %s\n",filename);

 strcpy(filename2_rect,filename);

 /*
 Get the number of trials used to get the good matches
 */

 fscanf(fp,"%d",&ntrials);

 fprintf(stdout,"Number of trials (good matches) = %d\n",
  ntrials);

 /*
 Get the max mean vertical disparity error allowed
 */

 fscanf(fp,"%lg",&max_mean_error);

 fprintf(stdout,"Max mean error (vertical disparity) = %g\n",
  max_mean_error);

 /*
 Done reading the input file
 */

 fclose(fp);

 /*
 Load image 1
 */

 err_flag= load_rgb_image(
  filename1,
  &I1_arr,
  &width,
  &height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"Filename extension for %s not recognized!\n",
     filename1);
    fprintf(stdout,"Supported: tiff, TIFF, tif, TIF, png, PNG, jpeg, JPEG, jpg, JPG\n");
    return 1;
 }

 /*
 Load image 2
 */

 err_flag= load_rgb_image(
  filename2,
  &I2_arr,
  &width,
  &height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"Filename extension for %s not recognized!\n",
     filename2);
    fprintf(stdout,"Supported: tiff, TIFF, tif, TIF, png, PNG, jpeg, JPEG, jpg, JPG\n");
    return 1;
 }

 /*
 Check image 1 rect format
 */

 ext= strrchr(filename1_rect,'.');

 if ( strcmp(ext+1,"tiff") == 0 ||
      strcmp(ext+1,"TIFF") == 0 ||
      strcmp(ext+1,"tif")  == 0 ||
      strcmp(ext+1,"TIF")  == 0 ) {
 }
 else if ( strcmp(ext+1,"png") == 0 ||
      strcmp(ext+1,"PNG") == 0 ) {
 }
 else if ( strcmp(ext+1,"jpeg") == 0 ||
           strcmp(ext+1,"JPEG") == 0 ||
           strcmp(ext+1,"jpg")  == 0 ||
           strcmp(ext+1,"JPG")  == 0 ) {
 }
 else {
    fprintf(stdout,"Filename extension for %s not recognized!\n",
     filename1_rect);
    fprintf(stdout,"Supported: tiff, TIFF, tif, TIF, png, PNG, jpeg, JPEG, jpg, JPG\n");
    return 1;
 }

 /*
 Check image 2 rect format
 */

 ext= strrchr(filename2_rect,'.');

 if ( strcmp(ext+1,"tiff") == 0 ||
      strcmp(ext+1,"TIFF") == 0 ||
      strcmp(ext+1,"tif")  == 0 ||
      strcmp(ext+1,"TIF")  == 0 ) {
 }
 else if ( strcmp(ext+1,"png") == 0 ||
      strcmp(ext+1,"PNG") == 0 ) {
 }
 else if ( strcmp(ext+1,"jpeg") == 0 ||
           strcmp(ext+1,"JPEG") == 0 ||
           strcmp(ext+1,"jpg")  == 0 ||
           strcmp(ext+1,"JPG")  == 0 ) {
 }
 else {
    fprintf(stdout,"Filename extension for %s not recognized!\n",
     filename2_rect);
    fprintf(stdout,"Supported: tiff, TIFF, tif, TIF, png, PNG, jpeg, JPEG, jpg, JPG\n");
    return 1;
 }

 /*
 Get the matches
 */

 fprintf(stdout,"Getting the features and matching them ...\n");

 err_flag= match_main(
  filename1,
  filename2,
  "match.txt"
 );

 fprintf(stdout,"Getting the features and matching them ... done.\n");

 /*
 Filter out the outliers
 */

 fprintf(stdout,"Filtering the outliers ...\n");

 seed = 1;

 err_flag= orsa_main(
  width,
  height,
  "match.txt",
  "good_match.txt",
  "F.txt",
  ntrials,
  seed
 );

 fprintf(stdout,"Filtering the outliers ... done.\n");

 /*
 Show the matches in input rgb images
 */

 match_show_matches(
  filename1,
  filename2,
  "good_match.txt",
  "good_match1.png",
  "good_match2.png"
 );

 /*
 Compute the homographies
 */

 fprintf(stdout,"Computing the rectifying homographies ...\n");

 err_flag= rectify_main(
  "good_match.txt",
  width,
  height,
  "H1.txt",
  "H2.txt",
  "disp_range.txt",
  max_mean_error
 );

 fprintf(stdout,"Computing the rectifying homographies ... done.\n");

 /*
 Check if rectification has been successful
 */

 if ( err_flag == 1 ) {
    fprintf(stdout,"Could not properly rectify the 2 images.\n");
    return 1;
 }

 /*
 Apply homography to image 1
 */

 fprintf(stdout,"Applying homography to image 1 ...\n");

 err_flag= homography_main(
  filename1,
  "H1.txt",
  filename1_rect
 );

 fprintf(stdout,"Applying homography to image 1 ... done.\n");

 /*
 Apply homography to image 2
 */

 fprintf(stdout,"Applying homography to image 2 ...\n");

 err_flag= homography_main(
  filename2,
  "H2.txt",
  filename2_rect
 );

 fprintf(stdout,"Applying homography to image 2 ... done.\n");

 /*
 Free memory
 */

 free(I1_arr);

 free(I2_arr);

 return 0;

}
