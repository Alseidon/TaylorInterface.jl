#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

void poinc_map(double endtime, double x[6], double y[6], double df[36])
{
  static MY_JET xjet[6];
  double t,tf;
  int i,j;
  static int flag=0;
  
  if (flag == 0)
    {
      taylor_initialize_jet_library();
      for(i=0; i<6; i++) InitJet(xjet[i]);
      flag=1;
    }
  t=0;
  tf=endtime;
  taylor_make_identity_jets(xjet,x,NULL,NULL);
  for (i=0; i<6; i++) y[i]=x[i]; 
  while (taylor_step_auto(&t,y,1,2,-16,-16,&tf,NULL,NULL,xjet) != 1);
  for (i=0; i<6; i++)
    for (j=0; j<6; j++)
      df[i*6+j]=xjet[i][j+1];
  return;
}

int tstep(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime)
{
  static MY_JET xjet[6];
  int i;
  static int flag=0;
  if (flag == 0)
    {
      taylor_initialize_jet_library();
      for(i=0; i<6; i++) InitJet(xjet[i]);
      flag = 1;
    }
  taylor_make_identity_jets(xjet,x,NULL,NULL);
  int ret_val = taylor_step_auto(ti,x,1,2,log10err,log10err,endtime,NULL,NULL,xjet);
  return ret_val;
}

int tstep_reverse(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime)
{
  static MY_JET xjet[6];
  int i;
  static int flag=0;
  if (flag == 0)
    {
      taylor_initialize_jet_library();
      for(i=0; i<6; i++) InitJet(xjet[i]);
      flag = 1;
    }
  taylor_make_identity_jets(xjet,x,NULL,NULL);
  int ret_val = taylor_step_auto(ti,x,-1,2,log10err,log10err,endtime,NULL,NULL,xjet);
  return ret_val;
}