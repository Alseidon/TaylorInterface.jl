#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

int flow(double endtime, MY_FLOAT *x, MY_FLOAT *y, MY_FLOAT *__unused)
{
  double t,tf;
  int i;
  int direction = (endtime > 0);
  t=0;
  tf=endtime;
  for (i=0; i<_NUMBER_OF_STATE_VARS_; i++) y[i]=x[i]; 
  if (tf == 0.) return;
  int flag_ret = 0;
  const int max_steps = 1000;
  for (int i = 0; i < max_steps; i++)
  {
    flag_ret = taylor_step_auto(&t,y,direction,2,-16,-16,&tf,NULL,NULL,NULL);
    switch (flag_ret)
    {
    case -1:
        puts("Encountered error; exiting");
        //exit(1);
        return -1;
        break;
    
    case 0:
        continue;
        break;

    case 1:
        return 1;
        break;
    
    default:
        puts("Unrecognized return value");
        printf("Unrecognized return value: %i", flag_ret);
        //exit(1);
        return flag_ret;
        break;
    }
  }
  printf("Couldn't finish in %i steps", max_steps);
  return 0;
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