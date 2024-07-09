        #ifndef WRAPPER_bcp_sun_earth_jupiter_H
        #define WRAPPER_bcp_sun_earth_jupiter_H

        #include "taylor-bcp_sun_earth_jupiter.h"

        #include "stdio.h"

void flow(double endtime, MY_FLOAT *x, MY_FLOAT *y, MY_FLOAT *df);

int tstep(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);

int tstep_reverse(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);

#endif