#include "header.h"
#include "proto.h"

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
)

{

 int iter;
 double theta_l_y;
 double theta_l_z;
 double theta_r_x;
 double theta_r_y;
 double theta_r_z;
 double f;
 double *sampson_error_arr;
 int match_ind;
 double *E;
 double error;
 double *J;
 double *Jt;
 double JtJ[6*6];
 double B[6];
 int n2;
 double JtJ2[6*6];
 double B2[6];
 int row_to_row2[6];
 int i;
 int j;
 double H2[6*6];
 double lambda;
 double X2[6];
 double X[6];
 double try_theta_l_y;
 double try_theta_l_z;
 double try_theta_r_x;
 double try_theta_r_y;
 double try_theta_r_z;
 double try_g;
 double g;
 double try_f;
 double try_error;
 double lambda_fact;
 int max_iter;
 double relative_tol;
 double target_rmse;
 double error_max;
 double err_first;
 double err_second;
 double lambda_init;

 iter=-1;

 theta_l_y= 0;
 theta_l_z= 0;
 theta_r_x= 0;
 theta_r_y= 0;
 theta_r_z= 0;
 g= 0;
 f= pow(3,g)*(double)(w+h);

 lambda_init= 1.0e-3;
 lambda_fact= 10.0;
 /* commented out
 max_iter= 300;
 */
 max_iter= 10000;
 relative_tol= 1.0e-3;
 target_rmse= 0.1;

 error_max= target_rmse*target_rmse*match_nbr;

 /*
 Allocate memory for the Sampson error
 */

 sampson_error_arr= (double *)calloc(match_nbr,sizeof(double));

 /*
 Compute Sampson error
 */

 rectify_compute_sampson_error(
  w,
  h,
  theta_l_y,
  theta_l_z,
  theta_r_x,
  theta_r_y,
  theta_r_z,
  f,
  match_nbr,
  match_arr,
  sampson_error_arr
 );

 err_first= math_vector_vector_product(
  (double *)sampson_error_arr,
  match_nbr,
  (double *)sampson_error_arr,
  match_nbr
 );
 /* Monasse uses that but I don't think it's right 
 err_first= sqrt(err_first/(double)match_nbr);
 */
 err_first= sqrt(err_first)/(double)match_nbr;

 fprintf(stdout," Initial average rectification error = %f\n",err_first);

 /*
 Allocate memory for E
 */

 E= (double *)calloc(match_nbr,sizeof(double));

 /*
 Compute E
 */

 for ( match_ind= 0 ; match_ind< match_nbr ; match_ind++ ) {
    E[match_ind]= 0.0-sampson_error_arr[match_ind];
 }

 /*
 Compute error
 */

 error= math_vector_vector_product(
  (double *)E,
  match_nbr,
  (double *)E,
  match_nbr
 );

 /*
 Allocate memory for the jacobian J of the Sampson error
 */

 J= (double *)calloc(match_nbr,6*sizeof(double));

 /*
 Compute the jacobian J of the Sampson error
 */

 rectify_compute_sampson_error_jacobian(
  w,
  h,
  theta_l_y,
  theta_l_z,
  theta_r_x,
  theta_r_y,
  theta_r_z,
  f,
  match_nbr,
  match_arr,
  J
 );

 /*
 Allocate memory for Jt
 */

 Jt= (double *)calloc(6,match_nbr*sizeof(double));

 /*
 Compute Jt
 */

 math_matrix_transpose(
  J,
  match_nbr,
  6,
  Jt
 );

 /*
 Compute JtJ = Jt*J
 It's a 6x6 matrix
 */

 math_matrix_matrix_product(
  Jt,
  6,
  match_nbr,
  J,
  match_nbr,
  6,
  JtJ
 );

 /*
 fprintf(stdout,"JtJ=");
 for ( i= 0 ; i< 6*6 ; i++ )
  fprintf(stdout," %g",JtJ[i]);
 fprintf(stdout,"\n");
 */

 /*
 Compute B = Jt * E
 It's a vector of length 6
 */

 math_matrix_vector_product(
  Jt,
  6,
  match_nbr,
  E,
  match_nbr,
  B
 );

 /*
 fprintf(stdout,"B=");
 for ( i= 0 ; i< 6 ; i++ )
  fprintf(stdout," %g",B[i]);
 fprintf(stdout,"\n");
 */

 /*
 Compress JtJ and B
 to remove possible trivial equations
 n2 is the new number of equations (rows/cols)
 row_to_row2 indicates the new row index
 going from JtJ/B to JtJ2/B2
 */

 n2= rectify_compress(
  JtJ,
  B,
  JtJ2,
  B2,
  row_to_row2
 );

 /*
 fprintf(stdout,"JtJ2=");
 for ( i= 0 ; i< n2*n2 ; i++ )
  fprintf(stdout," %g",JtJ2[i]);
 fprintf(stdout,"\n");
 */

 /*
 fprintf(stdout,"B2=");
 for ( i= 0 ; i< n2 ; i++ )
  fprintf(stdout," %g",B2[i]);
 fprintf(stdout,"\n");
 */

 lambda= lambda_init;

 START:

 iter++;

 /*
 Compute H = Jt*J+lambda*diag(Jt*J)
 using the compressed matrices
 */

 for ( i= 0 ; i< n2 ; i++ ) {
    for ( j= 0 ; j< n2 ; j++ ) {
       H2[i*n2+j]= JtJ2[i*n2+j];
    }
 }
 for ( i= 0 ; i< n2 ; i++ ) {
    H2[i*n2+i]+= lambda*JtJ2[i*n2+i]; 
 }

 /*
 fprintf(stdout,"H2=");
 for ( i= 0 ; i< n2*n2 ; i++ )
  fprintf(stdout," %g",H2[i]);
 fprintf(stdout,"\n");
 */

 /*
 Solve H*X=B
 using the compressed matrices
 */

 math_lu_decomposition_solve(
  n2,
  H2,
  B2,
  X2
 );

 /*
 fprintf(stdout,"X2=");
 for ( i= 0 ; i< n2 ; i++ )
  fprintf(stdout," %g",X2[i]);
 fprintf(stdout,"\n");
 */

 /*
 Uncompress the variable increments stored in X
 */

 rectify_uncompress(
  X2,
  row_to_row2,
  X
 );

 /*
 fprintf(stdout,"X=");
 for ( i= 0 ; i< 6 ; i++ )
  fprintf(stdout," %g",X[i]);
 fprintf(stdout,"\n");
 */

 /*
 Add the increments
 */

 try_theta_l_y= theta_l_y+X[0];
 try_theta_l_z= theta_l_z+X[1];
 try_theta_r_x= theta_r_x+X[2];
 try_theta_r_y= theta_r_y+X[3];
 try_theta_r_z= theta_r_z+X[4];
 try_g= g+X[5];
 try_f= pow(3,try_g)*(double)(w+h);

 /*
 Compute Sampson error
 */

 rectify_compute_sampson_error(
  w,
  h,
  try_theta_l_y,
  try_theta_l_z,
  try_theta_r_x,
  try_theta_r_y,
  try_theta_r_z,
  try_f,
  match_nbr,
  match_arr,
  sampson_error_arr
 );

 /*
 Compute E
 */

 for ( match_ind= 0 ; match_ind< match_nbr ; match_ind++ ) {
    E[match_ind]= 0.0-sampson_error_arr[match_ind];
 }

 /*
 Compute error
 */

 try_error= math_vector_vector_product(
  E,
  match_nbr,
  E,
  match_nbr
 );

 /* commented out
 if ( fabs(try_error-error) <= relative_tol*error )
  goto END;
 */

 if ( try_error > error ) {
    lambda *= lambda_fact;
 }
 else {
    lambda/= lambda_fact;

    error= try_error;

    theta_l_y= try_theta_l_y;
    theta_l_z= try_theta_l_z;
    theta_r_x= try_theta_r_x;
    theta_r_y= try_theta_r_y;
    theta_r_z= try_theta_r_z;
    g= try_g;
    f= pow(3,g)*(double)(w+h);

    /*
    Compute the jacobian J of the Sampson error
    */

    rectify_compute_sampson_error_jacobian(
     w,
     h,
     theta_l_y,
     theta_l_z,
     theta_r_x,
     theta_r_y,
     theta_r_z,
     f,
     match_nbr,
     match_arr,
     J
    );

    /*
    Compute Jt
    */

    math_matrix_transpose(
     J,
     match_nbr,
     6,
     Jt
    );

    /*
    Compute JtJ = Jt*J
    It's a 6x6 matrix
    */

    math_matrix_matrix_product(
     Jt,
     6,
     match_nbr,
     J,
     match_nbr,
     6,
     JtJ
    );

    /*
    Compute B = Jt * E
    It's a vector of length 6
    */

    math_matrix_vector_product(
     Jt,
     6,
     match_nbr,
     E,
     match_nbr,
     B
    ); 

    /*
    fprintf(stdout,"JtJ=");
    for ( i= 0 ; i< 6*6 ; i++ )
     fprintf(stdout," %g",JtJ[i]);
    fprintf(stdout,"\n");
    */

    /*
    fprintf(stdout,"B=");
    for ( i= 0 ; i< 6 ; i++ )
     fprintf(stdout," %g",B[i]);
    fprintf(stdout,"\n");
    */

    /*
    Compress JtJ and B
    to remove possible trivial equations
    */

    n2= rectify_compress(
     JtJ,
     B,
     JtJ2,
     B2,
     row_to_row2
    );

    /*
    fprintf(stdout,"JtJ2=");
    for ( i= 0 ; i< n2*n2 ; i++ )
     fprintf(stdout," %g",JtJ2[i]);
    fprintf(stdout,"\n");
    */

    /*
    fprintf(stdout,"B2=");
    for ( i= 0 ; i< n2 ; i++ )
     fprintf(stdout," %g",B2[i]);
    fprintf(stdout,"\n");
    */
 }

 /* commented out
 if ( iter < max_iter && error > error_max )
  goto START;
 */
 if ( iter < max_iter )
  goto START;

 END:

 /* Monasse uses that but I don't think it's right
 err_second= sqrt(error/(double)match_nbr);
 */
 err_second= sqrt(error)/(double)match_nbr;

 fprintf(stdout," Final average rectification error = %f\n",err_second);

 /*
 Free the Sampson error
 */

 if ( match_nbr > 0 )
  free(sampson_error_arr);

 /*
 Free E
 */

 if ( match_nbr > 0 )
  free(E);

 /*
 Free the jacobian J of the Sampson error
 */

 if ( match_nbr > 0 )
  free(J);

 /*
 Free Jt
 */

 if ( match_nbr > 0 )
  free(Jt);

 *ptheta_l_y= theta_l_y;
 *ptheta_l_z= theta_l_z;
 *ptheta_r_x= theta_r_x;
 *ptheta_r_y= theta_r_y;
 *ptheta_r_z= theta_r_z;
 *pf= f;

}
