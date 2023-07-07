#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

void flow(double endtime, MY_FLOAT *x, MY_FLOAT *y, MY_FLOAT *df)
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
  while (taylor_step_auto(&t,y,direction,2,-16,-16,&tf,NULL,NULL,xjet) != 1);
  for (i=0; i<_NUMBER_OF_STATE_VARS_; i++)
    for (j=0; j<_MAX_SIZE_OF_JET_VAR_; j++)
      df[i*_NUMBER_OF_STATE_VARS_+j]=xjet[i][j+1];
  return;
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