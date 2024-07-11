#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

int flow(double endtime, MY_FLOAT *x, MY_FLOAT *y, MY_FLOAT *df)
{
  static MY_JET xjet[_NUMBER_OF_STATE_VARS_];
  double t,tf;
  int i,j;
  int direction = (endtime > 0);
  static int flag=0;
  
  if (flag == 0)
    {
      taylor_initialize_jet_library();
      for(i=0; i<_NUMBER_OF_STATE_VARS_; i++) InitJet(xjet[i]);
      flag=1;
    }
  t=0;
  tf=endtime;
  taylor_make_identity_jets(xjet,x,NULL,NULL);
  for (i=0; i<_NUMBER_OF_STATE_VARS_; i++) y[i]=x[i]; 
  if (tf == 0.) return 1;
  int flag_ret = 0;
  const int max_steps = 1000;
  for (int i = 0; i < max_steps; i++)
  {
    flag_ret = taylor_step_auto(&t,y,direction,2,-16,-16,&tf,NULL,NULL,xjet);
    switch (flag_ret)
    {
    case -1:
        puts("Encountered error; exiting");
        exit(1);
        break;
    
    case 0:
        continue;
        break;

    case 1:
        for (i=0; i<_NUMBER_OF_STATE_VARS_; i++)
          for (j=0; j<_MAX_SIZE_OF_JET_VAR_; j++)
            df[i*_NUMBER_OF_STATE_VARS_+j]=xjet[i][j+1];
        return 1;
        break;
    
    default:
        printf("Unrecognized return value: %i", flag_ret);
        fflush(stdout);
        //exit(1);
        return flag_ret;
        break;
    }
  }
  printf("Couldn't finish in %i steps", max_steps);
  printf("Time: %f / %f ", t, tf);
  fflush(stdout);
  return 0;
}

int tstep(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime)
{
  static MY_JET xjet[_NUMBER_OF_STATE_VARS_];
  int i;
  static int flag=0;
  if (flag == 0)
    {
      taylor_initialize_jet_library();
      for(i=0; i<_NUMBER_OF_STATE_VARS_; i++) InitJet(xjet[i]);
      flag = 1;
    }
  taylor_make_identity_jets(xjet,x,NULL,NULL);
  int ret_val = taylor_step_auto(ti,x,1,2,log10err,log10err,endtime,NULL,NULL,xjet);
  return ret_val;
}

int tstep_reverse(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime)
{
  static MY_JET xjet[_NUMBER_OF_STATE_VARS_];
  int i;
  static int flag=0;
  if (flag == 0)
    {
      taylor_initialize_jet_library();
      for(i=0; i<_NUMBER_OF_STATE_VARS_; i++) InitJet(xjet[i]);
      flag = 1;
    }
  taylor_make_identity_jets(xjet,x,NULL,NULL);
  int ret_val = taylor_step_auto(ti,x,-1,2,log10err,log10err,endtime,NULL,NULL,xjet);
  return ret_val;
}