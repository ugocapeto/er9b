typedef struct feat_struct {
 int octave;
 int interval;
 int i;
 int j;
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
} feat_struct;

typedef struct match_struct {
 int feat1_ind;
 double x1;
 double y1;
 int feat2_ind;
 double x2;
 double y2;
} match_struct;

typedef struct error_struct {
 double error;
 int match_ind;
} error_struct;
