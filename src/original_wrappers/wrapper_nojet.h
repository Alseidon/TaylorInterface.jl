#include "stdio.h"


void poinc_map(double endtime, double x[6], double y[6], double* __unused);

int tstep(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);

int tstep_reverse(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);

#endif