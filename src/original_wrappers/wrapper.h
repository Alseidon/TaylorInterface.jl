#include "stdio.h"

void flow(double endtime, MY_FLOAT *x, MY_FLOAT *y, MY_FLOAT *df);

int tstep(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);

int tstep_reverse(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);

#endif