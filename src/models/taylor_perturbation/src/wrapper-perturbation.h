#ifndef WRAPPER_perturbation_H
#define WRAPPER_perturbation_H

#include "taylor-perturbation.h"

#include "stdio.h"

MY_FLOAT e1;
void set_e1(MY_FLOAT new_value);
MY_FLOAT e2;
void set_e2(MY_FLOAT new_value);
MY_FLOAT coef[10];
void set_coef(MY_FLOAT new_value, int i);
MY_FLOAT freq[10];
void set_freq(MY_FLOAT new_value, int i);

int flow(double endtime, MY_FLOAT *x, MY_FLOAT *y, MY_FLOAT *__unused);

int tstep(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);

int tstep_reverse(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);

#endif