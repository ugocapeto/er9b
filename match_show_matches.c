#include "header.h"
#include "proto.h"

void match_show_matches(
 char *filename_image1,
 char *filename_image2,
 char *filename_match,
 char *filename1,
 char *filename2
)

{

 char *ext;
 int width;
 int height;
 int *image1_rgb;
 int *image2_rgb;
 FILE *fp;
 int match_nbr;
 match_struct *match_arr;
 double x1;
 double y1;
 double x2;
 double y2;
 int match_i1;
 int match_j1;
 int match_i2;
 int match_j2;
 int i_radius;
 int j_radius;
 int i_offset;
 int j_offset;
 int i1;
 int i2;
 int j1;
 int j2;
 int match_ind;
 int pixel1;
 int pixel2;
 int cind;
 double rand_dbl;
 int rgb[3];
 int feat1_ind;
 int feat2_ind;
 int err_flag;

 /*
 Load image 1
 */

 err_flag= load_rgb_image(
  filename_image1,
  &image1_rgb,
  &width,
  &height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"Filename extension for %s not recognized!\n",
     filename_image1);
    fprintf(stdout,"Supported: tiff, TIFF, tif, TIF, png, PNG, jpeg, JPEG, jpg, JPG\n");
    /*
    return 1;
    */
 }

 /*
 Load image 2
 */

 err_flag= load_rgb_image(
  filename_image2,
  &image2_rgb,
  &width,
  &height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"Filename extension for %s not recognized!\n",
     filename_image2);
    fprintf(stdout,"Supported: tiff, TIFF, tif, TIF, png, PNG, jpeg, JPEG, jpg, JPG\n");
    /*
    return 1;
    */
 }

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

 srand(1);

 for ( match_ind= 0 ; match_ind< match_nbr ; match_ind++ ) {
    feat1_ind= match_arr[match_ind].feat1_ind;
    x1= match_arr[match_ind].x1;
    y1= match_arr[match_ind].y1;
    feat2_ind= match_arr[match_ind].feat2_ind;
    x2= match_arr[match_ind].x2;
    y2= match_arr[match_ind].y2;

    match_i1= (int)(y1+0.5);
    match_j1= (int)(x1+0.5);
    match_i2= (int)(y2+0.5);
    match_j2= (int)(x2+0.5);

    for ( cind= 0 ; cind< 3 ; cind++ ) {
       rand_dbl= (double)rand() / (double)RAND_MAX;
       rgb[cind]= (int)(rand_dbl*255);
    }

    i_radius= (int)( (double)height/100 + 0.5);
    j_radius= (int)( (double)width/100 + 0.5);

    for ( i_offset= -i_radius ; i_offset<= i_radius ; i_offset++ ) {
       i1= match_i1+i_offset;
       i2= match_i2+i_offset;
       if ( i1 < 0 )
        continue;
       if ( i1 > height-1 )
        continue;
       if ( i2 < 0 )
        continue;
       if ( i2 > height-1 )
        continue;
       for ( j_offset= -j_radius ; j_offset<= j_radius ; j_offset++ ) {
          j1= match_j1+j_offset;
          j2= match_j2+j_offset;
          if ( j1 < 0 )
           continue;
          if ( j1 > width-1 )
           continue;
          if ( j2 < 0 )
           continue;
          if ( j2 > width-1 )
           continue;
          pixel1= i1*width+j1;
          pixel2= i2*width+j2;
          image1_rgb[pixel1*3+0]= rgb[0];
          image1_rgb[pixel1*3+1]= rgb[1];
          image1_rgb[pixel1*3+2]= rgb[2];
          image2_rgb[pixel2*3+0]= rgb[0];
          image2_rgb[pixel2*3+1]= rgb[1];
          image2_rgb[pixel2*3+2]= rgb[2];
       }
    }
 }

 /*
 Write image 1 with matches drawn on it
 */

 err_flag= write_rgb_image(
  filename1,
  image1_rgb,
  width,
  height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"Filename extension for %s not recognized!\n",
     filename1);
    fprintf(stdout,"Supported: tiff, TIFF, tif, TIF, png, PNG, jpeg, JPEG, jpg, JPG\n");
    /*
    return 1;
    */
 }

 /*
 Write image 2 with matches drawn on it
 */

 err_flag= write_rgb_image(
  filename2,
  image2_rgb,
  width,
  height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"Filename extension for %s not recognized!\n",
     filename1);
    fprintf(stdout,"Supported: tiff, TIFF, tif, TIF, png, PNG, jpeg, JPEG, jpg, JPG\n");
    /*
    return 1;
    */
 }

 free(image1_rgb);

 free(image2_rgb);

 if ( match_nbr > 0 )
  free(match_arr); 

}
