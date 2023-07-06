#ifndef WRAPPER_bcp_sun_earth_venus_H
#define WRAPPER_bcp_sun_earth_venus_H
        
#include "taylor-bcp_sun_earth_venus.h"

#include "stdio.h"

// void bcpmap(double x[6], double y[6], double df[36]);

// void bcpmap_years(double endtime, double x[6], double y[6], double df[36]);
void poinc_map(double endtime, double x[6], double y[6], double df[36]);

// int tstep_bcp(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);
int tstep(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);

// int tstep_reverse_bcp(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);
int tstep_reverse(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);

// void compute_b_k(MY_FLOAT *x, MY_FLOAT *coeffs, int m, MY_FLOAT *out);

#endif