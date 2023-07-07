#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

void poinc_map(double endtime, MY_FLOAT *x, MY_FLOAT *y, MY_FLOAT *__unused)
{
  double t,tf;
  int i;
  t=0;
  tf=endtime;
  for (i=0; i<_NUMBER_OF_STATE_VARS_; i++) y[i]=x[i]; 
  while (taylor_step_auto(&t,y,1,2,-16,-16,&tf,NULL,NULL,NULL) != 1);
  return;
}

int tstep(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime)
{
  int ret_val = taylor_step_auto(ti,x,1,2,log10err,log10err,endtime,NULL,NULL,NULL);
  return ret_val;
}

int tstep_reverse(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime)
{
  int ret_val = taylor_step_auto(ti,x,-1,2,log10err,log10err,endtime,NULL,NULL,NULL);
  return ret_val;
}