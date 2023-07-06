#ifndef WRAPPER_bcp_sun_earth_venus_H
#define WRAPPER_bcp_sun_earth_venus_H
        
#include "taylor-bcp_sun_earth_venus.h"

#include "stdio.h"

void poinc_map(double endtime, double x[6], double y[6], double df[36]);

int tstep(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);

int tstep_reverse(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);

#endif