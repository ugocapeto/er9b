#include "header.h"
#include "proto.h"

void feature_show_features(
 char *filename_image,
 feat_struct *feat_arr,
 int feat_nbr,
 char *filename
)

{

 int i;
 int j;
 int pixel;
 int feat_ind;
 feat_struct feat;
 int octave;
 int interval;
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
 int feat_i;
 int feat_j;
 int i_offset;
 int j_offset;
 int i_radius;
 int j_radius;
 char *ext;
 int width;
 int height;
 int *image_rgb;
 int err_flag;

 /*
 Load image
 */

 err_flag= load_rgb_image(
  filename_image,
  &image_rgb,
  &width,
  &height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"Filename extension for %s not recognized!\n",
     filename_image);
    fprintf(stdout,"Supported: tiff, TIFF, tif, TIF, png, PNG, jpeg, JPEG, jpg, JPG\n");
    /*
    return 1;
    */
 }

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

    feat_i= (int)(pos_y+0.5);
    feat_j= (int)(pos_x+0.5);

    i_radius= (int)( (double)height/100 + 0.5);
    j_radius= (int)( (double)width/100 + 0.5);

    for ( i_offset= -i_radius ; i_offset<= i_radius ; i_offset++ ) {
       i= feat_i+i_offset;
       if ( i < 0 )
        continue;
       if ( i > height-1 )
        continue;
       for ( j_offset= -j_radius ; j_offset<= j_radius ; j_offset++ ) {
          j= feat_j+j_offset;
          if ( j < 0 )
           continue;
          if ( j > width-1 )
           continue;
          pixel= i*width+j; 
          image_rgb[pixel*3+0]= 255;
          image_rgb[pixel*3+1]= 0;
          image_rgb[pixel*3+2]= 0;
       }
    }
 }

 /*
 Write image with features drawn on it
 */

 err_flag= write_rgb_image(
  filename,
  image_rgb,
  width,
  height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"Filename extension for %s not recognized!\n",
     filename);
    fprintf(stdout,"Supported: tiff, TIFF, tif, TIF, png, PNG, jpeg, JPEG, jpg, JPG\n");
    /*
    return 1;
    */
 }

 free(image_rgb);

}
