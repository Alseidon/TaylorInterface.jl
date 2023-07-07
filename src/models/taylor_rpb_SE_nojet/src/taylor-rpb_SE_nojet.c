/* taylor Version 2.1, May 26, 2023 */
/* Using coef lib: MY_FLOAT */
/* No jet */
#include "taylor-rpb_SE_nojet.h"

/***********************************************************************
 *
 * Code generated by the TAYLOR translator.
 */

#define _N_DIM_ 6
#define _J_DIM_ 0


#define xInitUpJet() /* */
#define xInitJet(x_) /* */
#define xNormJet(a_,x_) /* */
#define xMultiplyFloatJetA(t_, f_, a_) /* */
#define xAddJetJetA(t_,a_, b_) /* */
#define xAssignJetToJet(t_,s_) /* */
#define xAssignJetToFloat(t_,s_) /* */





/*
next line defines the largest power of 2 such that 2^(LEXP2) and
2^(-LEXP2) do not overflow/underflow the double arithmetic of your
computer.
*/
#define LEXP2 1023 

#define DEBUG_LEVEL 0 /* to print some internal information */

int taylor_step_auto(MY_FLOAT *ti,
                 MY_FLOAT *x,
                 int      dir,
                 int      step_ctl,
                 double   log10abserr,
                 double   log10relerr,
                 MY_FLOAT *endtime,
                 MY_FLOAT *ht,
                 int      *order,
                 MY_JET   *jetInOut)
/*
 * single integration step with taylor method. the parameters are:
 *
 * ti: on input:  time of the initial condition
 *     on output: new time
 *
 * x:  on input:  initial condition
 *     on output: new condition, corresponding to the (output) time ti
 *
 * dir: flag to integrate forward or backwards.
 *     1: forward
 *    -1: backwards
 *     WARNING: this flag is ignored if step_ctl (see below) is set to 0.
 *
 * step_ctl: flag for the step size control. the possible values are:
 *     0: no step size control, so the step and order are provided by
 *        the user. the parameter ht is used as step, and the parameter
 *        order (see below) is used as the order.
 *     1: standard stepsize control. it uses an approximation to the
 *        optimal order and to the radius of convergence of the series
 *        to approximate the 'optimal' step size. It tries to keep
 *        either the absolute or the relative errors below the given
 *        values. See the paper for more details.
 *     2: as 1, but adding an extra condition on the stepsize h: the
 *        terms of the series --after being multiplied by the suitable
 *        power of h-- cannot grow.
 *    -1: user defined stepsize control. the code has to be included
 *        in the routine compute_timestep_user_defined (you can find
 *        this routine below). The user should also provide code for
 *        the selection of degree (see the function
 *        compute_order_user_defined below).
 *
 * log10abserr: decimal log of the absolute accuracy. the routine
 *     tries to keep either the absolute or the relative errors below
 *     the given thresholds.
 *
 * log10relerr: decimal log of the relative accuracy. the routine
 *     tries to keep either the absolute or the relative errors below
 *     the given thresholds.
 *
 * endtime: if NULL, it is ignored. if step_ctl (see above) is set
 *     to 0, it is also ignored. otherwise, if the step size is too
 *     large, it is reduced so that the new time ti is exactly endtime
 *     (in that case, the function returns 1).
 *
 * ht: on input:  ignored/used as a time step (see parameter step_ctl)
 *     on output: time step used if the pointer is not NULL
 *
 * order: degree of the taylor expansion.
 *        input: this parameter is only used if step_ctl is 0,
 *               or if you add the code for the case step_ctl=3.
 *               its possible values are:
 *               < 2: the program will select degree 2 (if step_ctl is 0).
 *               >=2: the program will use this degree (if step_ctl is 0).
 *        ouput: degree used if the pointer is not NULL
 *
 * jetInOut: on input: the value of all declared jet variables
 *           on output: new value of the jet variable, corresponding to the new time
 *
 * return value:
 *  0: ok.
 *  1: ok, and ti=endtime.  
 * -1: not ok, unable to compute step size.  double_log  underflow/overflow  */
{
  MY_FLOAT **taylor_coefficients_auto(MY_FLOAT, MY_FLOAT*, int);
  MY_FLOAT **taylor_coefficients_autoA(MY_FLOAT, MY_FLOAT*, int, int);
  int compute_order_1_auto(double, double, double, int*);
  int comp_order_other_auto(double, double, double);
  double compute_stepsize_1_auto(MY_FLOAT**, MY_JET**, int, double, int);
  double compute_stepsize_2_auto(MY_FLOAT**, MY_JET**, int, double, int);
  double comp_stepsize_other_auto(MY_FLOAT**, MY_JET**, int, int, double, double, double);

  static MY_FLOAT **s,h,mtmp;
  static MY_JET jtmp,jtmp1, **jetJetOut;
  double xi,xnorm,dh;
  int i,j,k,nt,flag_endtime,flag_err;
  static int init=0;
#pragma omp threadprivate(s,h,mtmp,init)
#pragma omp threadprivate(jtmp,jtmp1,jetJetOut)

  if (init == 0) /* initialization of MY_FLOAT and MY_JET variables */
    {
      init=1;
      InitMyFloat(h);
      InitMyFloat(mtmp);
      xInitUpJet();
      xInitJet(jtmp);
      xInitJet(jtmp1);
    }
/*
  sup norm of the initial condition (jet included)
*/
  xnorm=0;
  if (step_ctl != 0)
    {
#if _J_DIM_ != 0
    for (i=0; i<_J_DIM_; i++)
      {
        xNormJet(mtmp,jetInOut[i]);
        MyFloatToDouble(xi,mtmp);
        xi=fabs(xi);
        if (xi > xnorm) xnorm=xi;
      }
#endif
      for (i=_J_DIM_; i<_N_DIM_; i++)
      {
        MyFloatToDouble(xi,x[i]);
        xi=fabs(xi);
        if (xi > xnorm) xnorm=xi;
      }
    }
/*
  we determine the degree of the taylor expansion.
  this value will be stored in the variable nt.
  the flag flag_err returns a value indicating if we are using an
  absolute error estimate (value 1) or a relative one (value 2).
*/
  switch(step_ctl)
    {
    case 0: /* no step size control, fixed degree; both given by the user */
      if (order==NULL)
      {
        fprintf(stderr,"step_ctl=%d needs an input order\n",step_ctl);
        exit(0);
      }
      nt=(*order<2)? 2: *order; /* 2 is the minimum order allowed */
      break;
    case 1:
      nt=compute_order_1_auto(xnorm,log10abserr,log10relerr,&flag_err);
      break;
    case 2:
      nt=compute_order_1_auto(xnorm,log10abserr,log10relerr,&flag_err);
      break;
    case -1:
      nt=comp_order_other_auto(xnorm,log10abserr,log10relerr);
      break;
    default:
      fprintf(stderr, "taylor_step: undefined step size control.\n");
      fprintf(stderr, "you must choose an existing step size control\n");
      fprintf(stderr, "method or supply a step size control procedure.\n");
      exit(0);
    }
  if (order!=NULL) *order=nt;
/*
  computation of the jet of derivatives up to order nt
*/
  if(step_ctl != 0) {
    s=taylor_coefficients_auto_A(*ti,x,nt,1, jetInOut, &jetJetOut);
  } else {
    s=taylor_coefficients_auto_A(*ti,x,nt,0, jetInOut, &jetJetOut); 
 }

/*
  selection of the routine to compute the time step. the value
  step_ctl=3 has been reserved for the user, in case she/he wants to
  code a different method.
*/
  dh=1.0;
  switch(step_ctl)
    {
    case 0: /* no step size control (fixed step size, given by the user) */
      if (ht==NULL)
      {
        fprintf(stderr,"step_ctl=%d needs an input stepsize\n",step_ctl);
        exit(0);
      }
      AssignMyFloat(h,*ht);
      break;
    case 1:
      dh=compute_stepsize_1_auto(s,jetJetOut,nt,xnorm,flag_err);
      MakeMyFloatA(h, dh);
      break;
    case 2:
      dh=compute_stepsize_2_auto(s,jetJetOut,nt,xnorm,flag_err);
      MakeMyFloatA(h, dh);
      break;
    case -1:
      dh=comp_stepsize_other_auto(s,jetJetOut,_N_DIM_,nt,xnorm,log10abserr,log10relerr);
      MakeMyFloatA(h, dh);
      break;
    default:
      fprintf(stderr, "taylor_step: undefined step size control.\n");
      fprintf(stderr, "You must choose an existing step size control\n");
      fprintf(stderr, "method or supply a step size control procedure.\n");
      exit(0);
    }
  if(dh == 0.0) return -1; //changeme
/*
  if step_ctl != 0, we adjust the sign of the computed stepsize.
*/
  flag_endtime=0;
  if (step_ctl != 0)
    {
      if (dir == -1) { NegateMyFloatA(mtmp,h); AssignMyFloat(h, mtmp);} 
/*
      we compare *ti+h with endtime. we modify h if necessary.
*/
      if (endtime != NULL)
        {
          AddMyFloatA(mtmp,h,*ti);
          if (dir == 1) /* time goes forward */
            {
              if (MyFloatA_GE_B(mtmp,*endtime))
                {
                  SubtractMyFloatA(h,*endtime,*ti);
                  flag_endtime=1;
                }
            }
            else /* time goes backwards */
            {
              if (MyFloatA_GE_B(*endtime,mtmp))
                {
                  SubtractMyFloatA(h,*endtime,*ti);
                  flag_endtime=1;
                }
            }
        }
    }
/*
  next lines are the summation of the taylor series (horner's method)
*/
  j=nt-1;
#if _J_DIM_ != 0
  for(i=0; i<_J_DIM_; i++)
  {
    xAssignJetToJet(jetInOut[i],jetJetOut[i][nt]);
    for(k=j; k>=0; k--)
    {
      xMultiplyFloatJetA(jtmp, h, jetInOut[i]);
      xAddJetJetA(jetInOut[i], jtmp, jetJetOut[i][k]);
    }
    xAssignJetToFloat(x[i],jetInOut[i]);
  }
#endif
  for(i=_J_DIM_; i<_N_DIM_; i++)
  {
    AssignMyFloat(x[i],s[i][nt]);
    for(k=j; k>=0; k--)
    {
      MultiplyMyFloatA(mtmp, h, x[i]);
      AddMyFloatA(x[i], mtmp, s[i][k]);
    }
  }
/*
  finally, we set the values of the parameters *ht and *ti.
*/
  if (ht!=NULL) AssignMyFloat(*ht,h);
  if (flag_endtime == 0)
    {
      AssignMyFloat(mtmp, *ti);
      AddMyFloatA(*ti, mtmp, h);
    }
    else
    {
      AssignMyFloat(*ti,*endtime);
    }
  return(flag_endtime);
}
int compute_order_1_auto(double xnorm, double log10abserr, double log10relerr, int* flag_err)
/*
 * this is to determine the 'optimal' degree of the taylor expansion.
 *
 * parameters:
 * xnorm: norm of the initial condition
 * log10abserr: base-10 log of the absolute error required
 * log10relerr: base-10 log of the relative error required
 * flag_err:    flag. returns 1 if absolute error is used
 *                    returns 2 if relative error is used
 *
 * returned value: 'optimal' degree.
*/
{
  double log10eps,tmp;
  int nt;

  log10eps=log10abserr;
  *flag_err=1;
  if (xnorm != (double)0.0)
    {
      tmp=log10relerr+log10(xnorm);
      if (tmp > log10abserr) {log10eps=log10relerr; *flag_err=2;}
    }
/*
  we use 1.16 for the value 0.5*log(10)=1.151292546497...
*/
  nt=(int)(1.5-1.16*log10eps);
  if (nt < 2) nt=2; /* this is the minimum order accepted */

#if DEBUG_LEVEL > 0
      fprintf(stderr, "taylor_step: order is %d\n",nt);
#endif

  return(nt);
}
double compute_stepsize_1_auto(MY_FLOAT **s, MY_JET **jet, int nt, double xnorm, int flag_err)
/*
 * it looks for a step size for an expansion up to order nt. this
 * function requires that nt is the value computed by
 * compute_order_1_
 */
{
  double double_log_MyFloat_auto(MY_FLOAT x);
  static MY_FLOAT z,v1,v2;
  static MY_FLOAT of,uf;
  double lnv1,lnv2,r,lnro1,lnro2,lnro;
  int i;
  static int init=0;
#pragma omp threadprivate(z,v1,v2,of,uf,init)

  if (init == 0)
    {
      init=1;
      InitMyFloat(z);
      InitMyFloat(v1);
      InitMyFloat(v2);
      InitMyFloat(of);
      InitMyFloat(uf);

      r=pow((double)2,(double)LEXP2);
      MakeMyFloatA(of,r);
      r=pow((double)2,(double)(-LEXP2));
      MakeMyFloatA(uf,r);
    }
/*
  we compute the sup norm of the last two coefficients of the taylor
  series, and we store them into v1 and v2.
*/
  MakeMyFloatA(v1,0);
  MakeMyFloatA(v2,0);
#if _J_DIM_ != 0
  for (i=0; i<_J_DIM_; i++)
  {
    xNormJet(z,jet[i][nt-1]);
    if (MyFloatA_GT_B(z,v1)) AssignMyFloat(v1,z);
    xNormJet(z,jet[i][nt]);
    if (MyFloatA_GT_B(z,v2)) AssignMyFloat(v2,z);
  }
#endif
  for(i=_J_DIM_; i<_N_DIM_; i++)
  {
    fabsMyFloatA(z,s[i][nt-1]);
    if (MyFloatA_GT_B(z,v1)) AssignMyFloat(v1,z);
    fabsMyFloatA(z,s[i][nt]);
    if (MyFloatA_GT_B(z,v2)) AssignMyFloat(v2,z);
  }
/*
  computation of the step size. we need the logs of v1 and v2, in
  double precision (there is no need for extended precision). the idea
  is to assign these variables to double variables and then to use the
  standard log function. before doing that, we have to be sure that v1
  can be assigned to a double without under or overflow. for this
  reason we will check for this condition and, if it fails, we will
  call an specific function for this case.
*/
  if (MyFloatA_LE_B(v1,of) && MyFloatA_GE_B(v1,uf))
    {
      MyFloatToDouble(r,v1);
      lnv1=log(r);
    }
    else
    {
      lnv1=double_log_MyFloat_auto(v1);
    }
  if (MyFloatA_LE_B(v2,of) && MyFloatA_GE_B(v2,uf))
    {
      MyFloatToDouble(r,v2);
      lnv2=log(r);
    }
    else
    {
      lnv2=double_log_MyFloat_auto(v2);
    }
  if(lnv1 == 65536.0 || lnv2 == 65536.0 ) return 0.0; //changeme
/*
  if flag_err == 2, this means that we are using a relative error control.
*/
  if (flag_err == 2)
    {
      r = -log10(xnorm);
      lnv1 += r;
      lnv2 += r;
    }
 lnro1= -lnv1/(nt-1);
 lnro2= -lnv2/nt;
 lnro=(lnro1 < lnro2)? lnro1: lnro2;

 r=exp(lnro-2-0.7/(nt-1)); /* exp(-0.7/(nt-1)) is a security factor */
  return(r);
}
double compute_stepsize_2_auto(MY_FLOAT **s, MY_JET **jet, int nt, double xnorm, int flag_err)
/*
 * it looks for a step size for an expansion up to order nt. this
 * function requires that nt is the value computed by
 * compute_order_1_. it also tries to reduce cancellations of big
 * terms in the summation of the taylor series.
 */
{
  double compute_stepsize_1_auto(MY_FLOAT**, MY_JET**, int, double, int);
  static MY_FLOAT h,hj,r,z,a,normj;
  double c,rtmp,dh;
  int i,j;
  static int init=0;
#pragma omp threadprivate(h,hj,r,z,a,normj,init)

  if (init == 0)
    {
      init=1;
      InitMyFloat(h); 
      InitMyFloat(hj);
      InitMyFloat(r);
      InitMyFloat(z);
      InitMyFloat(a);
      InitMyFloat(normj);
    }
/*
  we compute the step size according to the first algorithm
*/
  dh=compute_stepsize_1_auto(s,jet,nt,xnorm,flag_err);
  if(dh == 0.0) return  0.0; // changeme
  MakeMyFloatA(h,dh);
/*
  next lines select a value (z), that will be used to control the size
  of the terms of the Taylor series.
*/
  if (flag_err == 1) {
     MakeMyFloatA(z, 1.0);
  } else if (flag_err == 2) {
    MakeMyFloatA(z,xnorm);
  } else
    {
      printf("compute_stepsize_2 internal error. flag_err: %d\n",flag_err);
      exit(1);
    }
/*
  next loop checks if the sup norm of the terms in the Taylor series are
  lower than z. if a term is greater than z, the step size h is reduced.
*/
  MakeMyFloatA(hj,(double)1.0);

  for(j=1; j<=nt; j++)
  {
    MultiplyMyFloatA(r,h,hj);
    AssignMyFloat(hj,r);

    MakeMyFloatC(normj,"0", (double)0);
#if _J_DIM_ != 0
    for (i=0; i<_J_DIM_; i++)
    {
      xNormJet(a,jet[i][j]);
      if (MyFloatA_GT_B(a,normj)) AssignMyFloat(normj,a);
    }
#endif
    for (i=_J_DIM_; i<_N_DIM_; i++)
    {
      fabsMyFloatA(a,s[i][j]);
      if (MyFloatA_GT_B(a,normj)) AssignMyFloat(normj,a);
    }

    MultiplyMyFloatA(r,normj,hj);
    if (MyFloatA_LE_B(r,z)) continue;
/*
    we reduce h (and hj)
*/
    DivideMyFloatA(hj,z,normj);

    DivideMyFloatA(a,r,z);
    MyFloatToDouble(c,a);
    c=pow(c,(double)1.e0/(double)j);
    MakeMyFloatA(a,c);
    DivideMyFloatA(r,h,a);
    AssignMyFloat(h,r);

#if DEBUG_LEVEL > 1
    fprintf(stderr, "order %2d. reducing h from %14.6e to %14.6e\n",j,c*h,h);
#endif
  }

  MyFloatToDouble(rtmp,h);
  return(rtmp);
}

double double_log_MyFloat_auto(MY_FLOAT x)
/*
 * natural log, in double precision, of a MY_FLOAT positive number.
 */
{
  static MY_FLOAT a,tmp;
  static MY_FLOAT z,of,uf;
  double b,lx;
  int k;
  static int init=0;
#pragma omp threadprivate(a,tmp,z,of,uf,init)

  if (init == 0)
    {
      init=1;
      InitMyFloat(a);
      InitMyFloat(z);
      InitMyFloat(of);
      InitMyFloat(uf);
      InitMyFloat(tmp);

      b=0;
      MakeMyFloatA(z,b);
      b=pow((double)2,(double)LEXP2);
      MakeMyFloatA(of,b);
      b=pow((double)2,(double)(-LEXP2));
      MakeMyFloatA(uf,b);
    }

  if (MyFloatA_EQ_B(x,z))
    {
      puts("double_log_MyFloat error: zero argument");
      puts("(this is because one of the last two terms of your taylor");
      puts(" expansion is exactly zero)");
      /*exit(1);*/
      return 65536.0;
    }

  AssignMyFloat(a,x);

  k=0;
  while(MyFloatA_LT_B(a,uf))
  {
    ++k;
    if(k>3000){fprintf(stderr,"double_log_MyFloat overflow: %d\n", k); /*exit(1);*/ return 65536.0;}
     MultiplyMyFloatA(tmp,a,of);
    AssignMyFloat(a,tmp);
  }
  while(MyFloatA_GT_B(a,of))
  {
    --k;
    if(k<-3000){fprintf(stderr,"double_log_MyFloat underflow: %d\n", k); /*exit(1);*/ return 65536.0;}
     MultiplyMyFloatA(tmp,a,uf);
    AssignMyFloat(a,tmp);
  }

  MyFloatToDouble(b,a);
/*
  lx stands for log(x)
*/
  lx=log(b)-(LEXP2*0.69314718055994530942)*k;

  return(lx);
}


int comp_order_other_auto(double lnxnorm, double log10abserr, double log10relerr){
  puts("---");
  puts("compute_order_user_defined:");
  puts("you have to code this routine");
  puts("or select a different value for the step_ctl parameter");
  puts("---");
  exit(1);

  return(0);
}
double comp_stepsize_other_auto(MY_FLOAT **s, MY_JET **jet, int nd, int nt, double xnorm, double log10abserr, double log10relerr) {

  puts("---");
  puts("compute_timestep_user_defined:");
  puts("you have to code this routine");
  puts("or select a different value for the step_ctl parameter");
  puts("---");
  exit(1);
  return((double)0.00001);
}
/***********************************************************************
 *
 * Procedure generated by the TAYLOR translator. Do not edit!
 *
 * It needs the header file 'taylor.h' to compile.
 * Run taylor with the -header -o taylor.h option to generate a sample 'taylor.h'

 * Translation info is at the end of this file.
 * Version 2.1, May 26, 2023
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
MY_FLOAT **taylor_coefficients_auto_A(MY_FLOAT t, MY_FLOAT *x, int order, int rflag, MY_JET *sIn, MY_JET ***sOut)
{
   /* input: 
      t:     current value of the time variable 
      x:     array represent values of the state variables
      order: order of the taylor coefficients sought
      rflag: recompute flag. If you call this routine with one order 
             first, but then decided that you need a higher order of the
             taylor polynomial, you can pass 0 to rflag. This routine 
             will try to use the values already computed. Provided that 
             both x and t have not been changed, and you did not modify 
             the jet derivatives from the previous call.
      sIn:   array representing the input jet variables
             If NULL, the x values are assigned.
      sOut:  Pointer output jet variables
             If NULL, the pointer is not modified.
      Return Value:
            Two D Array, rows are the taylor coefficients of the
            state variables

     */

    static int          _jz_ivars[2];
    #pragma omp threadprivate( _jz_ivars)
    static MY_FLOAT     _jz_cvars[9];
    #pragma omp threadprivate( _jz_cvars)
    static MY_FLOAT     *_jz_jet[35],  *_jz_save = NULL, *_jz_oneOverN=NULL,*_jz_theNs=NULL;
    static MY_FLOAT     _jz_tvar1, _jz_tvar2, _jz_tvar3, _jz_tvar4; /* tmp vars */
    static MY_FLOAT     _jz_uvar1, _jz_uvar2; /* tmp vars */
    static MY_FLOAT     _jz_svar1, _jz_svar2, _jz_svar3, _jz_svar4, _jz_svar5; /* tmp vars */
    static MY_FLOAT     _jz_wvar3, _jz_wvar4; /* tmp vars */
    static MY_FLOAT     _jz_zvar1, _jz_zvar2; /* tmp vars */
    static MY_FLOAT     _jz_MyFloatZERO, _kthtmp;
    #pragma omp threadprivate(_jz_jet, _jz_save, _jz_oneOverN, _jz_theNs, _jz_tvar1, _jz_tvar2, _jz_tvar3, _jz_tvar4, _jz_uvar1, _jz_uvar2, _jz_svar1, _jz_svar2, _jz_svar3, _jz_svar4, _jz_svar5, _jz_wvar3, _jz_wvar4, _jz_zvar1, _jz_zvar2, _jz_MyFloatZERO, _kthtmp)
    static int          _jz_maxOrderUsed  = -1;
    static int          _jz_lastOrder = 0, _jz_initialized=0, _jz_ginitialized=0;
    int                 _jz_i, _jz_j, _jz_k, _jz_l, _jz_m, _jz_n, _jz_oorder ;
    #pragma omp threadprivate(_jz_maxOrderUsed,_jz_lastOrder, _jz_initialized, _jz_ginitialized)
    /* allocating memory if needed */
    if (_jz_maxOrderUsed < order )  { 
    	 if (_jz_ginitialized == 0) { 
    	   InitMyFloat(_jz_tvar1); InitMyFloat(_jz_tvar2);InitMyFloat(_jz_tvar3);InitMyFloat(_jz_tvar4);
    	   InitMyFloat(_jz_svar1); InitMyFloat(_jz_svar2);InitMyFloat(_jz_svar3);InitMyFloat(_jz_svar4);
    	   InitMyFloat(_jz_svar5); InitMyFloat(_jz_zvar1);InitMyFloat(_jz_zvar2);
    	   InitMyFloat(_jz_uvar1); InitMyFloat(_jz_uvar2);
    	   InitMyFloat(_jz_wvar3);InitMyFloat(_jz_wvar4);
    	   InitMyFloat(_jz_MyFloatZERO); InitMyFloat(_kthtmp);
    	   MakeMyFloatC(_jz_MyFloatZERO, "0", (double)0);
    	   for(_jz_i=0; _jz_i<9; _jz_i++) {
    	       InitMyFloat(_jz_cvars[_jz_i]);
    	   }
    	 }
    	 if (rflag > 0) rflag = 0; /* have to recompute everything */
    	 _jz_oorder=_jz_maxOrderUsed;
    	 _jz_maxOrderUsed  = order;
    	 if (_jz_ginitialized) { 
    	   for(_jz_i=0; _jz_i< _jz_oorder+1; _jz_i++) {ClearMyFloat(_jz_oneOverN[_jz_i]); ClearMyFloat(_jz_theNs[_jz_i]);}
    	   free(_jz_oneOverN); free(_jz_theNs);
    	 }
    	 _jz_theNs = (MY_FLOAT *)malloc((order+1) * sizeof(MY_FLOAT));
    	 _jz_oneOverN = (MY_FLOAT *)malloc((order+1) * sizeof(MY_FLOAT));
    	 for(_jz_i=0; _jz_i<order+1; _jz_i++) {InitMyFloat(_jz_oneOverN[_jz_i]);InitMyFloat(_jz_theNs[_jz_i]);}
    	 MakeMyFloatC(_jz_theNs[0],"0.0", (double)0.0);
    	 MakeMyFloatC(_jz_uvar1,"1.0", (double)1.0);
    	 for(_jz_i = 1; _jz_i <= order; _jz_i++) {
    		 AssignMyFloat(_jz_tvar2, _jz_theNs[_jz_i-1]);
    		 AddMyFloatA(_jz_theNs[_jz_i], _jz_tvar2, _jz_uvar1);
	}
    	 AssignMyFloat(_jz_oneOverN[0],_jz_uvar1);
    	 AssignMyFloat(_jz_oneOverN[1],_jz_uvar1);
    	 for(_jz_i = 2; _jz_i <= order; _jz_i++) {
    		 DivideMyFloatA(_jz_oneOverN[_jz_i], _jz_uvar1,_jz_theNs[_jz_i]);
	}
    	 if (_jz_ginitialized) {
    	    for(_jz_i=0; _jz_i<(_jz_oorder+1)*(35); _jz_i++) { ClearMyFloat(_jz_save[_jz_i]);} free(_jz_save);
    	 }
    	 _jz_save = (MY_FLOAT *)malloc((order+1)* 35 *sizeof(MY_FLOAT));
    	 for(_jz_i=0; _jz_i<(order+1)*(35); _jz_i++) { InitMyFloat(_jz_save[_jz_i]);}
    	 for(_jz_j = 0, _jz_k = 0; _jz_j < 35 ;  _jz_j++, _jz_k += order+1) { _jz_jet[_jz_j] =& (_jz_save[_jz_k]); }

    	 /* True constants, initialized only once. */
	 /* const: i_021=1 */
	 _jz_ivars[0]=1;
	 /* const: c_022=3.0033532813678653e-6 */
	 MakeMyFloatC(_jz_cvars[0],"3.0033532813678653e-6",(double)3.0033532813678653e-6);
	 /* minus: c_042=(i_021-c_022) */
	 SubtractMyFloatA(_jz_cvars[1], MakeMyFloatB(_jz_uvar1,(double)_jz_ivars[0]), _jz_cvars[0]);
	 /* mult: c_048=(c_022*c_022) */
	 MultiplyMyFloatA(_jz_cvars[2], _jz_cvars[0], _jz_cvars[0]);
	 /* const: i_029=2 */
	 _jz_ivars[1]=2;
	 /* mult: c_049=(c_022*i_029) */
	 MultiplyMyFloatA(_jz_cvars[3], _jz_cvars[0], MakeMyFloatB(_jz_tvar1,(double)_jz_ivars[1]));
	 /* const: c_031=3. */
	 MakeMyFloatC(_jz_cvars[4],"3.",(double)3.);
	 /* negate: c_053=(-c_031) */
	 NegateMyFloatA(_jz_cvars[5],_jz_cvars[4]);
	 /* div: c_054=(c_053/i_029) */
	 DivideMyFloatA(_jz_cvars[6], _jz_cvars[5], MakeMyFloatB(_jz_uvar1,(double)_jz_ivars[1]));
	 /* mult: c_062=(c_042*c_042) */
	 MultiplyMyFloatA(_jz_cvars[7], _jz_cvars[1], _jz_cvars[1]);
	 /* mult: c_057=(c_042*i_029) */
	 MultiplyMyFloatA(_jz_cvars[8], _jz_cvars[1], MakeMyFloatB(_jz_tvar1,(double)_jz_ivars[1]));
    }

    if (rflag) {
    	 if (rflag < 0 ) return(NULL);
    	 for(_jz_i = 0; rflag != 0 && _jz_i < 6; _jz_i++) {
    		 if (MyFloatA_NEQ_B(_jz_jet[_jz_i][0], x[_jz_i])) rflag = 0;
    	 }
    }

    if (rflag == 0) {
	 /* initialize all constant vars and state variables */
	 _jz_lastOrder = 1;
		 /* init state variable: */
	 AssignMyFloat(_jz_jet[0][0], x[0]);
		 /* init state variable: */
	 AssignMyFloat(_jz_jet[1][0], x[1]);
		 /* init state variable: */
	 AssignMyFloat(_jz_jet[2][0], x[2]);
		 /* init state variable: */
	 AssignMyFloat(_jz_jet[3][0], x[3]);
		 /* init state variable: */
	 AssignMyFloat(_jz_jet[4][0], x[4]);
		 /* init state variable: */
	 AssignMyFloat(_jz_jet[5][0], x[5]);
	 /* plus: v_067=(v_015+v_017) */
	 AddMyFloatA(_jz_jet[6][0], _jz_jet[1][0], _jz_jet[3][0]);
	 /* minus: v_068=(v_018-v_014) */
	 SubtractMyFloatA(_jz_jet[7][0], _jz_jet[4][0], _jz_jet[0][0]);
	 /* mult: v_043=(v_014*v_014) */
	 MultiplyMyFloatA(_jz_jet[8][0], _jz_jet[0][0], _jz_jet[0][0]);
	 /* mult: v_044=(v_015*v_015) */
	 MultiplyMyFloatA(_jz_jet[9][0], _jz_jet[1][0], _jz_jet[1][0]);
	 /* plus: v_045=(v_043+v_044) */
	 AddMyFloatA(_jz_jet[10][0], _jz_jet[8][0], _jz_jet[9][0]);
	 /* mult: v_046=(v_016*v_016) */
	 MultiplyMyFloatA(_jz_jet[11][0], _jz_jet[2][0], _jz_jet[2][0]);
	 /* plus: v_047=(v_045+v_046) */
	 AddMyFloatA(_jz_jet[12][0], _jz_jet[10][0], _jz_jet[11][0]);
	 /* mult: v_050=(c_049*v_014) */
	 MultiplyMyFloatA(_jz_jet[13][0], _jz_cvars[3], _jz_jet[0][0]);
	 /* minus: v_051=(v_047-v_050) */
	 SubtractMyFloatA(_jz_jet[14][0], _jz_jet[12][0], _jz_jet[13][0]);
	 /* plus: v_052=(c_048+v_051) */
	 AddMyFloatA(_jz_jet[15][0], _jz_cvars[2], _jz_jet[14][0]);
	 /* exponentiation: v_055=(v_052^c_054) */
	 ExponentiateMyFloatA(_jz_jet[16][0], _jz_jet[15][0], _jz_cvars[6]);
	 /* mult: v_069=(c_042*v_055) */
	 MultiplyMyFloatA(_jz_jet[17][0], _jz_cvars[1], _jz_jet[16][0]);
	 /* minus: v_070=(v_014-c_022) */
	 SubtractMyFloatA(_jz_jet[18][0], _jz_jet[0][0], _jz_cvars[0]);
	 /* mult: v_071=(v_069*v_070) */
	 MultiplyMyFloatA(_jz_jet[19][0], _jz_jet[17][0], _jz_jet[18][0]);
	 /* minus: v_072=(v_018-v_071) */
	 SubtractMyFloatA(_jz_jet[20][0], _jz_jet[4][0], _jz_jet[19][0]);
	 /* mult: v_058=(c_057*v_014) */
	 MultiplyMyFloatA(_jz_jet[21][0], _jz_cvars[8], _jz_jet[0][0]);
	 /* plus: v_059=(v_047+v_058) */
	 AddMyFloatA(_jz_jet[22][0], _jz_jet[12][0], _jz_jet[21][0]);
	 /* plus: v_063=(c_062+v_059) */
	 AddMyFloatA(_jz_jet[23][0], _jz_cvars[7], _jz_jet[22][0]);
	 /* exponentiation: v_066=(v_063^c_054) */
	 ExponentiateMyFloatA(_jz_jet[24][0], _jz_jet[23][0], _jz_cvars[6]);
	 /* mult: v_073=(c_022*v_066) */
	 MultiplyMyFloatA(_jz_jet[25][0], _jz_cvars[0], _jz_jet[24][0]);
	 /* plus: v_074=(c_042+v_014) */
	 AddMyFloatA(_jz_jet[26][0], _jz_cvars[1], _jz_jet[0][0]);
	 /* mult: v_075=(v_073*v_074) */
	 MultiplyMyFloatA(_jz_jet[27][0], _jz_jet[25][0], _jz_jet[26][0]);
	 /* minus: v_076=(v_072-v_075) */
	 SubtractMyFloatA(_jz_jet[28][0], _jz_jet[20][0], _jz_jet[27][0]);
	 /* negate: v_077=(-v_017) */
	 NegateMyFloatA(_jz_jet[29][0],_jz_jet[3][0]);
	 /* plus: v_080=(v_069+v_073) */
	 AddMyFloatA(_jz_jet[30][0], _jz_jet[17][0], _jz_jet[25][0]);
	 /* mult: v_081=(v_015*v_080) */
	 MultiplyMyFloatA(_jz_jet[31][0], _jz_jet[1][0], _jz_jet[30][0]);
	 /* minus: v_082=(v_077-v_081) */
	 SubtractMyFloatA(_jz_jet[32][0], _jz_jet[29][0], _jz_jet[31][0]);
	 /* negate: v_086=(-v_080) */
	 NegateMyFloatA(_jz_jet[33][0],_jz_jet[30][0]);
	 /* mult: v_087=(v_016*v_086) */
	 MultiplyMyFloatA(_jz_jet[34][0], _jz_jet[2][0], _jz_jet[33][0]);

	 /* the first derivative of state variables */
	 /* state variable 0: */
	 AssignMyFloat(_jz_jet[0][1], _jz_jet[6][0]);
	 /* state variable 1: */
	 AssignMyFloat(_jz_jet[1][1], _jz_jet[7][0]);
	 /* state variable 2: */
	 AssignMyFloat(_jz_jet[2][1], _jz_jet[5][0]);
	 /* state variable 3: */
	 AssignMyFloat(_jz_jet[3][1], _jz_jet[28][0]);
	 /* state variable 4: */
	 AssignMyFloat(_jz_jet[4][1], _jz_jet[32][0]);
	 /* state variable 5: */
	 AssignMyFloat(_jz_jet[5][1], _jz_jet[34][0]);
	}

	 /* compute the kth order derivatives of all vars */
	 for(_jz_k = _jz_lastOrder; _jz_k < order; _jz_k++) {
		 /* derivative for tmp variables */
		 /* plus: v_067=(v_015+v_017) */
		 AddMyFloatA(_jz_jet[6][_jz_k], _jz_jet[1][_jz_k],_jz_jet[3][_jz_k]);
		 /* minus: v_068=(v_018-v_014) */
		 SubtractMyFloatA(_jz_jet[7][_jz_k], _jz_jet[4][_jz_k],_jz_jet[0][_jz_k]);
		 /* mult: v_043=(v_014*v_014) */
		 { /* multiplication */
			 static MY_FLOAT tmp1, tmp2, tmp;
			 #pragma omp threadprivate(tmp1, tmp2, tmp)
			 if(_jz_initialized==0) {
			   InitMyFloat(tmp1);InitMyFloat(tmp2); InitMyFloat(tmp);
			   }
			 int parity=(_jz_k&1), half=(_jz_k+1)>>1;
			 AssignMyFloat(tmp, _jz_MyFloatZERO);
			 for(_jz_l=0; _jz_l<half; _jz_l++) {
			     MultiplyMyFloatA(tmp1, _jz_jet[0][_jz_l], _jz_jet[0][_jz_k-_jz_l]);
			     AssignMyFloat(tmp2, tmp);
			     AddMyFloatA(tmp, tmp2, tmp1);
			 }
			 AssignMyFloat(tmp2, tmp);
			 AddMyFloatA(tmp1, tmp2, tmp);
			 if(parity==0) {
			     MultiplyMyFloatA(tmp2, _jz_jet[0][half], _jz_jet[0][half]);
			     AddMyFloatA(_jz_jet[8][_jz_k], tmp2, tmp1);
			 } else {
			     AssignMyFloat(_jz_jet[8][_jz_k], tmp1);
			 }
		 }
		 /* mult: v_044=(v_015*v_015) */
		 { /* multiplication */
			 static MY_FLOAT tmp1, tmp2, tmp;
			 #pragma omp threadprivate(tmp1, tmp2, tmp)
			 if(_jz_initialized==0) {
			   InitMyFloat(tmp1);InitMyFloat(tmp2); InitMyFloat(tmp);
			   }
			 int parity=(_jz_k&1), half=(_jz_k+1)>>1;
			 AssignMyFloat(tmp, _jz_MyFloatZERO);
			 for(_jz_l=0; _jz_l<half; _jz_l++) {
			     MultiplyMyFloatA(tmp1, _jz_jet[1][_jz_l], _jz_jet[1][_jz_k-_jz_l]);
			     AssignMyFloat(tmp2, tmp);
			     AddMyFloatA(tmp, tmp2, tmp1);
			 }
			 AssignMyFloat(tmp2, tmp);
			 AddMyFloatA(tmp1, tmp2, tmp);
			 if(parity==0) {
			     MultiplyMyFloatA(tmp2, _jz_jet[1][half], _jz_jet[1][half]);
			     AddMyFloatA(_jz_jet[9][_jz_k], tmp2, tmp1);
			 } else {
			     AssignMyFloat(_jz_jet[9][_jz_k], tmp1);
			 }
		 }
		 /* plus: v_045=(v_043+v_044) */
		 AddMyFloatA(_jz_jet[10][_jz_k], _jz_jet[8][_jz_k],_jz_jet[9][_jz_k]);
		 /* mult: v_046=(v_016*v_016) */
		 { /* multiplication */
			 static MY_FLOAT tmp1, tmp2, tmp;
			 #pragma omp threadprivate(tmp1, tmp2, tmp)
			 if(_jz_initialized==0) {
			   InitMyFloat(tmp1);InitMyFloat(tmp2); InitMyFloat(tmp);
			   }
			 int parity=(_jz_k&1), half=(_jz_k+1)>>1;
			 AssignMyFloat(tmp, _jz_MyFloatZERO);
			 for(_jz_l=0; _jz_l<half; _jz_l++) {
			     MultiplyMyFloatA(tmp1, _jz_jet[2][_jz_l], _jz_jet[2][_jz_k-_jz_l]);
			     AssignMyFloat(tmp2, tmp);
			     AddMyFloatA(tmp, tmp2, tmp1);
			 }
			 AssignMyFloat(tmp2, tmp);
			 AddMyFloatA(tmp1, tmp2, tmp);
			 if(parity==0) {
			     MultiplyMyFloatA(tmp2, _jz_jet[2][half], _jz_jet[2][half]);
			     AddMyFloatA(_jz_jet[11][_jz_k], tmp2, tmp1);
			 } else {
			     AssignMyFloat(_jz_jet[11][_jz_k], tmp1);
			 }
		 }
		 /* plus: v_047=(v_045+v_046) */
		 AddMyFloatA(_jz_jet[12][_jz_k], _jz_jet[10][_jz_k],_jz_jet[11][_jz_k]);
		 /* mult: v_050=(c_049*v_014) */
		 MultiplyMyFloatA(_jz_jet[13][_jz_k], _jz_cvars[3], _jz_jet[0][_jz_k]);
		 /* minus: v_051=(v_047-v_050) */
		 SubtractMyFloatA(_jz_jet[14][_jz_k], _jz_jet[12][_jz_k],_jz_jet[13][_jz_k]);
		 /* plus: v_052=(c_048+v_051) */
		 AssignMyFloat(_jz_jet[15][_jz_k], _jz_jet[14][_jz_k]);
		 /* exponentiation: v_055=(v_052^c_054) */
		 { /* exponentiation */
				 /* expr^(-3/2)/ */ 
			 int  ppk=(-3)*_jz_k, qqk=(2)*_jz_k, pq=-1;
			 static MY_FLOAT tmp1, tmp2, tmp3, tmpC, tmp;
			 #pragma omp threadprivate(tmp, tmp1, tmp2, tmp3, tmpC)
			 if(_jz_initialized==0) {
			  InitMyFloat(tmp1);InitMyFloat(tmp2); InitMyFloat(tmp3);
			  InitMyFloat(tmpC);InitMyFloat(tmp);
			 }
			 AssignMyFloat(tmp,  _jz_MyFloatZERO);
			 for(_jz_l=0; _jz_l<_jz_k; _jz_l++) {
			     MakeMyFloatA(tmpC, ppk);
			     ppk -= pq  ;
			     MultiplyMyFloatA(tmp1, _jz_jet[16][_jz_l],_jz_jet[15][_jz_k-_jz_l]);
			     MultiplyMyFloatA(tmp2, tmpC, tmp1);
			     AddMyFloatA(tmp1,  tmp, tmp2);
			     AssignMyFloat(tmp,  tmp1);
			 }
			 MakeMyFloatA(tmp3,qqk);
			 MultiplyMyFloatA(tmp1, _jz_jet[15][0], tmp3);
			 DivideMyFloatA(_jz_jet[16][_jz_k], tmp, tmp1);
		}
		 /* mult: v_069=(c_042*v_055) */
		 MultiplyMyFloatA(_jz_jet[17][_jz_k], _jz_cvars[1], _jz_jet[16][_jz_k]);
		 /* minus: v_070=(v_014-c_022) */
		 AssignMyFloat(_jz_jet[18][_jz_k], _jz_jet[0][_jz_k]);
		 /* mult: v_071=(v_069*v_070) */
		 { /* multiplication */
			 static MY_FLOAT tmp1, tmp2, tmp;
			 #pragma omp threadprivate(tmp1, tmp2, tmp)
			 if(_jz_initialized==0) {
			   InitMyFloat(tmp1);InitMyFloat(tmp2); InitMyFloat(tmp);
			   }
			 AssignMyFloat(tmp, _jz_MyFloatZERO);
			 for(_jz_l=0; _jz_l<=_jz_k; _jz_l++) {
			     MultiplyMyFloatA(tmp1, _jz_jet[17][_jz_l], _jz_jet[18][_jz_k-_jz_l]);
			     AssignMyFloat(tmp2, tmp);
			     AddMyFloatA(tmp, tmp2, tmp1);
			 }
			 AssignMyFloat(_jz_jet[19][_jz_k], tmp);
		 }
		 /* minus: v_072=(v_018-v_071) */
		 SubtractMyFloatA(_jz_jet[20][_jz_k], _jz_jet[4][_jz_k],_jz_jet[19][_jz_k]);
		 /* mult: v_058=(c_057*v_014) */
		 MultiplyMyFloatA(_jz_jet[21][_jz_k], _jz_cvars[8], _jz_jet[0][_jz_k]);
		 /* plus: v_059=(v_047+v_058) */
		 AddMyFloatA(_jz_jet[22][_jz_k], _jz_jet[12][_jz_k],_jz_jet[21][_jz_k]);
		 /* plus: v_063=(c_062+v_059) */
		 AssignMyFloat(_jz_jet[23][_jz_k], _jz_jet[22][_jz_k]);
		 /* exponentiation: v_066=(v_063^c_054) */
		 { /* exponentiation */
				 /* expr^(-3/2)/ */ 
			 int  ppk=(-3)*_jz_k, qqk=(2)*_jz_k, pq=-1;
			 static MY_FLOAT tmp1, tmp2, tmp3, tmpC, tmp;
			 #pragma omp threadprivate(tmp, tmp1, tmp2, tmp3, tmpC)
			 if(_jz_initialized==0) {
			  InitMyFloat(tmp1);InitMyFloat(tmp2); InitMyFloat(tmp3);
			  InitMyFloat(tmpC);InitMyFloat(tmp);
			 }
			 AssignMyFloat(tmp,  _jz_MyFloatZERO);
			 for(_jz_l=0; _jz_l<_jz_k; _jz_l++) {
			     MakeMyFloatA(tmpC, ppk);
			     ppk -= pq  ;
			     MultiplyMyFloatA(tmp1, _jz_jet[24][_jz_l],_jz_jet[23][_jz_k-_jz_l]);
			     MultiplyMyFloatA(tmp2, tmpC, tmp1);
			     AddMyFloatA(tmp1,  tmp, tmp2);
			     AssignMyFloat(tmp,  tmp1);
			 }
			 MakeMyFloatA(tmp3,qqk);
			 MultiplyMyFloatA(tmp1, _jz_jet[23][0], tmp3);
			 DivideMyFloatA(_jz_jet[24][_jz_k], tmp, tmp1);
		}
		 /* mult: v_073=(c_022*v_066) */
		 MultiplyMyFloatA(_jz_jet[25][_jz_k], _jz_cvars[0], _jz_jet[24][_jz_k]);
		 /* plus: v_074=(c_042+v_014) */
		 AssignMyFloat(_jz_jet[26][_jz_k], _jz_jet[0][_jz_k]);
		 /* mult: v_075=(v_073*v_074) */
		 { /* multiplication */
			 static MY_FLOAT tmp1, tmp2, tmp;
			 #pragma omp threadprivate(tmp1, tmp2, tmp)
			 if(_jz_initialized==0) {
			   InitMyFloat(tmp1);InitMyFloat(tmp2); InitMyFloat(tmp);
			   }
			 AssignMyFloat(tmp, _jz_MyFloatZERO);
			 for(_jz_l=0; _jz_l<=_jz_k; _jz_l++) {
			     MultiplyMyFloatA(tmp1, _jz_jet[25][_jz_l], _jz_jet[26][_jz_k-_jz_l]);
			     AssignMyFloat(tmp2, tmp);
			     AddMyFloatA(tmp, tmp2, tmp1);
			 }
			 AssignMyFloat(_jz_jet[27][_jz_k], tmp);
		 }
		 /* minus: v_076=(v_072-v_075) */
		 SubtractMyFloatA(_jz_jet[28][_jz_k], _jz_jet[20][_jz_k],_jz_jet[27][_jz_k]);
		 /* negation: v_077=(-v_017) */
		 NegateMyFloatA(_jz_jet[29][_jz_k], _jz_jet[3][_jz_k]);
		 /* plus: v_080=(v_069+v_073) */
		 AddMyFloatA(_jz_jet[30][_jz_k], _jz_jet[17][_jz_k],_jz_jet[25][_jz_k]);
		 /* mult: v_081=(v_015*v_080) */
		 { /* multiplication */
			 static MY_FLOAT tmp1, tmp2, tmp;
			 #pragma omp threadprivate(tmp1, tmp2, tmp)
			 if(_jz_initialized==0) {
			   InitMyFloat(tmp1);InitMyFloat(tmp2); InitMyFloat(tmp);
			   }
			 AssignMyFloat(tmp, _jz_MyFloatZERO);
			 for(_jz_l=0; _jz_l<=_jz_k; _jz_l++) {
			     MultiplyMyFloatA(tmp1, _jz_jet[1][_jz_l], _jz_jet[30][_jz_k-_jz_l]);
			     AssignMyFloat(tmp2, tmp);
			     AddMyFloatA(tmp, tmp2, tmp1);
			 }
			 AssignMyFloat(_jz_jet[31][_jz_k], tmp);
		 }
		 /* minus: v_082=(v_077-v_081) */
		 SubtractMyFloatA(_jz_jet[32][_jz_k], _jz_jet[29][_jz_k],_jz_jet[31][_jz_k]);
		 /* negation: v_086=(-v_080) */
		 NegateMyFloatA(_jz_jet[33][_jz_k], _jz_jet[30][_jz_k]);
		 /* mult: v_087=(v_016*v_086) */
		 { /* multiplication */
			 static MY_FLOAT tmp1, tmp2, tmp;
			 #pragma omp threadprivate(tmp1, tmp2, tmp)
			 if(_jz_initialized==0) {
			   InitMyFloat(tmp1);InitMyFloat(tmp2); InitMyFloat(tmp);
			   }
			 AssignMyFloat(tmp, _jz_MyFloatZERO);
			 for(_jz_l=0; _jz_l<=_jz_k; _jz_l++) {
			     MultiplyMyFloatA(tmp1, _jz_jet[2][_jz_l], _jz_jet[33][_jz_k-_jz_l]);
			     AssignMyFloat(tmp2, tmp);
			     AddMyFloatA(tmp, tmp2, tmp1);
			 }
			 AssignMyFloat(_jz_jet[34][_jz_k], tmp);
		 }
		 /* derivative of state variables */
		 _jz_m = _jz_k+1;
		 /* state variable 0: */
		 DivideMyFloatA(_jz_jet[0][_jz_m], _jz_jet[6][_jz_k], _jz_theNs[_jz_m]);
		 /* state variable 1: */
		 DivideMyFloatA(_jz_jet[1][_jz_m], _jz_jet[7][_jz_k], _jz_theNs[_jz_m]);
		 /* state variable 2: */
		 DivideMyFloatA(_jz_jet[2][_jz_m], _jz_jet[5][_jz_k], _jz_theNs[_jz_m]);
		 /* state variable 3: */
		 DivideMyFloatA(_jz_jet[3][_jz_m], _jz_jet[28][_jz_k], _jz_theNs[_jz_m]);
		 /* state variable 4: */
		 DivideMyFloatA(_jz_jet[4][_jz_m], _jz_jet[32][_jz_k], _jz_theNs[_jz_m]);
		 /* state variable 5: */
		 DivideMyFloatA(_jz_jet[5][_jz_m], _jz_jet[34][_jz_k], _jz_theNs[_jz_m]);
		 _jz_initialized=1;
	 }
    _jz_lastOrder = order;
    _jz_ginitialized=1;
    if (sOut) {
     *sOut = NULL;
    }
    return(_jz_jet);
}

MY_FLOAT **taylor_coefficients_autoA(MY_FLOAT t, MY_FLOAT *x, int order, int rflag)
{
    return(taylor_coefficients_auto_A(t,x,order,rflag, NULL, NULL));
}

MY_FLOAT **taylor_coefficients_auto(MY_FLOAT t, MY_FLOAT *x, int order)
{
    return(taylor_coefficients_autoA(t,x,order,0));
}
