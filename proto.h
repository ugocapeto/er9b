void er9b_downsample_image(
 double *inp_I,
 int inp_xdim,
 int inp_ydim,
 double *out_I,
 int out_xdim,
 int out_ydim,
 double factor
);

void er9b_downsample_image_dimensions(
 int inp_xdim,
 int inp_ydim,
 int *pout_xdim,
 int *pout_ydim,
 double factor
);

void er9b_error_handler(
 char* from
);

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
);

void feature_add_features(
 feat_struct feat,
 double *hist_arr,
 int hist_nbr,
 double mag_thresh,
 feat_struct **pfeat_arr,
 int *pfeat_nbr
);

void feature_adjust_features_image_doubling(
 int interval_nbr,
 double inp_sigma,
 feat_struct *feat_arr,
 int feat_nbr
);

void feature_build_dog_space(
 int octave_nbr,
 int interval_nbr,
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ****pdog_pyr_image
);

void feature_build_scale_space(
 int inp_width,
 int inp_height,
 double *inp_image,
 int octave_nbr,
 int interval_nbr,
 double inp_sigma,
 double ****pgauss_pyr_image,
 int **pgauss_pyr_width,
 int **pgauss_pyr_height
);

int feature_check_extremum_edge_like(
 int octave_nbr,
 int interval_nbr,
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 int img_border,
 int octave,
 int inp_interval,
 int inp_i,
 int inp_j
);

void feature_compute_descriptors(
 int octave_nbr,
 int interval_nbr,
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 feat_struct *feat_arr,
 int feat_nbr
);

void feature_compute_features_orientation_histogram(
 int octave_nbr,
 int interval_nbr,
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 feat_struct **pfeat_arr,
 int *pfeat_nbr
);

void feature_compute_features_sigma(
 int interval_nbr,
 double inp_sigma,
 feat_struct *feat_arr,
 int feat_nbr
);

void feature_create_init_image(
 int width,
 int height,
 int *image_rgb,
 double sigma,
 int image_doubling_flag,
 int *pnew_width,
 int *pnew_height,
 double **pinit_image
);

void feature_descriptor_convert_histogram(
 double ***hist_arr,
 int dwidth,
 int hist_nbr,
 feat_struct *feat
);

double ***feature_descriptor_histogram(
 int width,
 int height,
 double *image,
 int inp_i,
 int inp_j,
 double ori,
 double sigma,
 int dwidth,
 int hist_nbr
);

void feature_descriptor_histogram_interpolate(
 double ***hist_arr,
 double descr_i_sub,
 double descr_j_sub,
 double hist_ind_sub,
 double mag,
 int descr_width,
 int hist_nbr
);

void feature_descriptor_normalize(
 feat_struct *feat
);

void feature_detect_features(
 int octave_nbr,
 int interval_nbr,
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 feat_struct **pfeat_arr,
 int *pfeat_nbr
);

void feature_dog_deriv(
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 int octave,
 int interval,
 int i,
 int j,
 double deriv[3]
);

void feature_dog_hessian(
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 int octave,
 int interval,
 int i,
 int j,
 double hessian[3*3]
);

void feature_get_dominant_orientation(
 double *hist_arr,
 int hist_nbr,
 double *pmax_mag,
 int *pmax_hist_ind
);

int feature_gradient_magnitude_orientation(
 int width,
 int height,
 double *image,
 int i,
 int j,
 double *pmag,
 double *pori
);

void feature_interpolate_extremum_location(
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 int octave,
 int inp_interval,
 int inp_i,
 int inp_j,
 double *pxinterval,
 double *pxi,
 double *pxj,
 double *pxdog
);

int feature_interpolate_extremum_location_main(
 int octave_nbr,
 int interval_nbr,
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 int img_border,
 int octave,
 int inp_interval,
 int inp_i,
 int inp_j,
 int *pinterval,
 int *pi,
 int *pj,
 double *pxinterval,
 double *pxi,
 double *pxj,
 double *pxdog
);

int feature_is_extremum(
 double ***gauss_pyr_image,
 int *gauss_pyr_width,
 int *gauss_pyr_height,
 double ***dog_pyr_image,
 int octave,
 int inp_interval,
 int inp_i,
 int inp_j
);

int feature_main(
 char *filename_image,
 double sigma,
 feat_struct **pfeat_arr,
 int *pfeat_nbr
);

double *feature_orientation_histogram(
 int width,
 int height,
 double *image,
 int inp_i,
 int inp_j,
 int hist_nbr,
 int radius,
 double sigma
);

void feature_show_features(
 char *filename_image,
 feat_struct *feat_arr,
 int feat_nbr,
 char *filename
);

void feature_smooth_orientation_histogram(
 double *hist_arr,
 int hist_nbr
);

void gaussian_blur_image(
 double *inp_I,
 int xdim,
 int ydim,
 double sigma,
 int precision,
 double *I
);

void homography_apply(
 double H_mat[9],
 double x,
 double y,
 double *px2,
 double *py2
);

int homography_main(
  char *filename_image,
  char *filename_H,
  char *filename_image_rect
);

double interpolate_bicubic(
 double *I,
 double x,
 double y,
 int xdim,
 int ydim
);

void interpolate_bicubic_rgb(
 int *image_arr,
 double x,
 double y,
 int xdim,
 int ydim,
 int rgb[3]
);

double interpolate_cubic(
 double p0,
 double p1,
 double p2,
 double p3,
 double x
);

double match_distance_squared(
 feat_struct feat1,
 feat_struct feat2
);

int match_feature(
 feat_struct inp_feat,
 feat_struct *feat_arr,
 int feat_nbr
);

void match_features(
 feat_struct *feat1_arr,
 int feat1_nbr,
 feat_struct *feat2_arr,
 int feat2_nbr,
 match_struct **pmatch_arr,
 int *pmatch_nbr
);

int match_main(
 char *filename_image1,
 char *filename_image2,
 char *filename_match
);

void match_show_matches(
 char *filename_image1,
 char *filename_image2,
 char *filename_match,
 char *filename1,
 char *filename2
);

void orsa_best_number_false_alarms(
 error_struct *error_arr,
 int match_nbr,
 double logalpha0,
 double loge0,
 double *logcn,
 double *logc7,
 double *pbest_nfa,
 int *pbest_k
);

void orsa_characteristic_polynomial(
 double F1[3*3],
 double F2[3*3],
 double a[4]
);

void orsa_compute_sort_errors(
 match_struct *match_arr,
 int match_nbr,
 double F[3*3],
 error_struct *error_arr
);

int orsa_epipolar(
 match_struct *match_arr,
 int match_nbr,
 int match7_ind[7],
 double *F_arr
);

int orsa_find_cubic_roots(
 double coeff[4],
 double x[3]
);

double orsa_log_combi(
 int k,
 int n
);

int orsa_main(
 int width,
 int height,
 char *filename_match,
 char *filename_good_match,
 char *filename_F,
 int ntrials,
 unsigned long seed
);

void orsa_pick_7_random_matches(
 int k[7],
 int n
);

int rectify_compress(
 double JtJ[6*6],
 double B[6],
 double JtJ2[6*6],
 double B2[6],
 int row_to_row2[6]
);

void rectify_compute_disp_range_b(
 int w,
 int h,
 int match_nbr,
 match_struct *match_arr,
 double H_l_mat[9],
 double H_r_mat[9],
 int *pmin_d,
 int *pmax_d
);

void rectify_compute_disp_range(
 int w,
 int h,
 int match_nbr,
 match_struct *match_arr,
 double H_l_mat[9],
 double H_r_mat[9],
 int *pmin_d,
 int *pmax_d
);

void rectify_compute_fundamental_matrix(
 int w,
 int h,
 double theta_l_y,
 double theta_l_z,
 double theta_r_x,
 double theta_r_y,
 double theta_r_z,
 double f,
 double fund_mat[9]
);

void rectify_compute_inverse_k_matrix(
 int w,
 int h,
 double f,
 double inv_k_mat[9]
);

void rectify_compute_inverse_k_matrix_deriv(
 int w,
 int h,
 double f,
 double inv_k_mat_deriv[9]
);

void rectify_compute_k_matrix(
 int w,
 int h,
 double f,
 double k_mat[9]
);

void rectify_compute_rotation(
 double theta,
 char axis,
 double rot_mat[9]
);

void rectify_compute_rotation_deriv(
 double theta,
 char axis,
 double rot_mat_deriv[9]
);

void rectify_compute_rotation_left(
 double theta_l_y,
 double theta_l_z,
 double rot_mat_l[9]
);

void rectify_compute_rotation_right(
 double theta_r_x,
 double theta_r_y,
 double theta_r_z,
 double rot_mat_r[9]
);

void rectify_compute_sampson_error(
 int w,
 int h,
 double theta_l_y,
 double theta_l_z,
 double theta_r_x,
 double theta_r_y,
 double theta_r_z,
 double f,
 int match_nbr,
 match_struct *match_arr,
 double *sampson_error_arr
);

void rectify_compute_sampson_error_jacobian(
 int w,
 int h,
 double theta_l_y,
 double theta_l_z,
 double theta_r_x,
 double theta_r_y,
 double theta_r_z,
 double f,
 int match_nbr,
 match_struct *match_arr,
 double *sampson_error_jacobian_mat
);

double rectify_compute_vertical_disparity_error(
 int w,
 int h,
 int match_nbr,
 match_struct *match_arr,
 double H_l_mat[9],
 double H_r_mat[9]
);

void rectify_fix_center(
 int w,
 int h,
 double theta_l_y,
 double theta_l_z,
 double theta_r_x,
 double theta_r_y,
 double theta_r_z,
 double f,
 double H_l_mat[9],
 double H_r_mat[9]
);

int rectify_main(
 char *filename_match,
 int w,
 int h,
 char *filename_H_l,
 char *filename_H_r,
 char *filename_disp_range,
 double max_mean_error
);

void rectify_minimize_sampson_error(
 int w,
 int h,
 int match_nbr,
 match_struct *match_arr,
 double *ptheta_l_y,
 double *ptheta_l_z,
 double *ptheta_r_x,
 double *ptheta_r_y,
 double *ptheta_r_z,
 double *pf
);

void rectify_print_vertical_disparity_error(
 int w,
 int h,
 int match_nbr,
 match_struct *match_arr,
 double H_l_mat[9],
 double H_r_mat[9]
);

void rectify_uncompress(
 double X2[6],
 int row_to_row2[6],
 double X[6]
);

void rgb_to_grayscale(
 int width,
 int height,
 int *image_rgb,
 double *image_grayscale
);

int sift_main(
 char *imgIn1,
 char *imgIn2,
 char *fileOut,
 char *imgOut
);

int orsa_main(
 int width,
 int height,
 char *filename_match,
 char *filename_good_match,
 int ntrials,         // maximum number of ransac trials
 bool verb,           // verbose
 unsigned long seed,  // seed value (0=reinitialize)
 int mode,            // 0=all 1=ransac 2=optimized ransac (ORSA) 3=automatic
 bool stop            // stop when first meaningful F is found
);

void rectify_compute_homographies(
 char *filename_image_l,
 char *filename_image_r,
 int w,
 int h,
 char *filename_match,
 char *filename_Hl,
 char *filename_Hr
);

int homography_main(
 char *image_in,
 char *filename_H,
 char *image_out,
 char *tiff32_out
);

int showRect_main(
 char *in_png,
 char *out_png,
 char *match_txt,
 char *which,
 char *H_txt
);
