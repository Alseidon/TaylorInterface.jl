#ifndef WRAPPER_rpb_sun_earth_H
#define WRAPPER_rpb_sun_earth_H
        
#include "taylor-rpb_sun_earth.h"

#include "stdio.h"

void poinc_map(double endtime, double x[6], double y[6], double df[36]);

int tstep(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);

int tstep_reverse(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);

#endif