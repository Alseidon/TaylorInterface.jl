#include "wrapper-bcp_sun_earth_venus.h"
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
/*
void bcpmap(double x[6], double y[6], double df[36])
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
  tf=(2*M_PI)/0.9156638588046531;
  taylor_make_identity_jets(xjet,x,NULL,NULL);
  for (i=0; i<6; i++) y[i]=x[i]; 
  while (taylor_step_auto(&t,y,1,2,-16,-16,&tf,NULL,NULL,xjet) != 1);
  for (i=0; i<6; i++)
    for (j=0; j<6; j++)
      df[i*6+j]=xjet[i][j+1];
  return;
}
*/

//void bcpmap_years(double endtime, double x[6], double y[6], double df[36])
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

// int tstep_bcp(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime)
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

// int tstep_reverse_bcp(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime)
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

/*
void compute_b_k(MY_FLOAT *x, MY_FLOAT *coeffs, int m, MY_FLOAT *out)
{
  static MY_JET xjet[6];
  double t,tf;
  int i,j;
  double y[6] = { 0. };
  static int flag=0;

  if (flag == 0)
  {
    taylor_initialize_jet_library();
    for(i=0; i<6; i++) InitJet(xjet[i]);
    flag=1;
  }
  t=0;
  tf=(2*M_PI)/0.9156638588046531;
  for (j = 0; j < 6; j++)
  {
    for (i = 0; i < m; i++)
    {
      xjet[j][i] = coeffs[i*6 + j];
    }
    for (i = m; i < _MAX_SIZE_OF_JET_VAR_; i++)
    {
      xjet[j][i] = 0.;
    }
  }
  for (i=0; i<6; i++) y[i]=x[i];

  while (taylor_step_auto(&t,y,1,2,-16,-16,&tf,NULL,NULL,xjet) != 1);
  for (int i = 0; i < 6; i++)
  {
    out[i] = xjet[i][m];
  }
  return;
}
*/