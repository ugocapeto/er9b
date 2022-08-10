#include "header.h"
#include "proto.h"

int homography_main( 
  char *filename_image,
  char *filename_H,
  char *filename_image_rect
)

{

 char *ext;
 double H[9];
 double H_inv[9];
 int width;
 int height;
 int *image_arr;
 FILE *fp;
 int i;
 int j;
 double B[9];
 int *image_rect_arr;
 int i_rect;
 int j_rect;
 int pixel_rect;
 int cind;
 double x_rect;
 double y_rect;
 double x;
 double y;
 int xdim;
 int ydim;
 int rgb[3];
 int err_flag;

 /*
 Load image
 */

 err_flag= load_rgb_image(
  filename_image,
  &image_arr,
  &width,
  &height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"Filename extension for %s not recognized!\n",
     filename_image);
    fprintf(stdout,"Supported: tiff, TIFF, tif, TIF, png, PNG, jpeg, JPEG, jpg, JPG\n");
    return 1; 
 }

 /*
 Load homography
 */

 fp= fopen(filename_H,"r");

 for ( i= 0 ; i< 3 ; i++ ) {
    for ( j= 0 ; j< 3 ; j++ ) {
       fscanf(fp,"%lg",&H[i*3+j]);
    }
 }

 fclose(fp);

 /*
 Invert the homography so that
 a pixel in the rectified image can refer to
 a position in the unrectified image
 */

 math_lu_decomposition_inverse(
  3,
  H,
  H_inv
 );

 /*
 Check !
 Matrix B should be the identity matrix if all went well
 */

 math_matrix_matrix_product(
  H,
  3,
  3,
  H_inv,
  3,
  3,
  B
 );

 /*
 Allocate memory for the rectified image
 */

 image_rect_arr= (int *)calloc(width*height,3*sizeof(int));

 /*
 For each pixel in the rectified image,
 get the position in the original image, and
 interpolate the rgb intensities
 */

 for ( i_rect= 0 ; i_rect< height ; i_rect++ ) {
    for ( j_rect= 0 ; j_rect< width ; j_rect++ ) {
       pixel_rect= i_rect*width+j_rect;

       /*
       Initialize to white
       */

       for ( cind= 0 ; cind< 3 ; cind++ )
        image_rect_arr[3*pixel_rect+cind]= 255;

       /*
       Get corresponding pixel in original image
       */

       x_rect= (double)j_rect;
       y_rect= (double)i_rect;

       /*
       Apply inverse homography
       */

       homography_apply(
        H_inv,
        x_rect,
        y_rect,
        &x,
        &y
       );

       /*
       Check if in bounds
       */

       xdim= width;
       ydim= height;

       if ( !(x >= 0) )
        continue;
       if ( !(x <= (xdim-1)) )
        continue;
       if ( !(y >= 0) )
        continue;
       if ( !(y <= (ydim-1)) )
        continue;

       /*
       Perform a bicubic interpolation
       to get the rgb intensities in original image
       */

       interpolate_bicubic_rgb(
        image_arr,
        x,
        y,
        xdim,
        ydim,
        rgb
       );

       /*
       Update color
       */

       for ( cind= 0 ; cind< 3 ; cind++ )
        image_rect_arr[3*pixel_rect+cind]= rgb[cind];
    }
 }

 /*
 Let's dump the rectified image into filename_image_rect
 */

 err_flag= write_rgb_image(
  filename_image_rect,
  image_rect_arr,
  width,
  height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"Filename extension for %s not recognized!\n",
     filename_image_rect);
    fprintf(stdout,"Supported: tiff, TIFF, tif, TIF, png, PNG, jpeg, JPEG, jpg, JPG\n");
    return 1;
 }

 free(image_arr);

 free(image_rect_arr);

 return 0;

}
