#include "header.h"
#include "proto.h"

int orsa_find_cubic_roots(
 double coeff[4],
 double x[3]
)

/*
Either 1 real solution or 3
*/

{

 double a1;
 double a2;
 double a3;
 double Q;
 double R;
 double Q3;
 double d;
 double theta;
 double sqrtQ;
 double e;

 x[0]= 0;
 x[1]= 0;
 x[2]= 0;

    a1 = coeff[2] / coeff[3];
    a2 = coeff[1] / coeff[3];
    a3 = coeff[0] / coeff[3];

    Q = (a1 * a1 - 3 * a2) / 9;
    R = (2 * a1 * a1 * a1 - 9 * a1 * a2 + 27 * a3) / 54;
    Q3 = Q * Q * Q;
    d = Q3 - R * R;

    if (d >= 0) { // 3 real roots
        theta = acos(R / sqrt(Q3));
        sqrtQ = sqrt(Q);
        x[0] = -2 * sqrtQ * cos( theta             / 3) - a1 / 3;
        x[1] = -2 * sqrtQ * cos((theta + 2 * M_PI) / 3) - a1 / 3;
        x[2] = -2 * sqrtQ * cos((theta + 4 * M_PI) / 3) - a1 / 3;
        return 3;
    } else { // 1 real root
        e = pow(sqrt(-d) + fabs(R), 1. / 3.);
        if (R > 0)
            e = -e;
        x[0] = (e + Q / e) - a1 / 3.;
        return 1;
    }

}
