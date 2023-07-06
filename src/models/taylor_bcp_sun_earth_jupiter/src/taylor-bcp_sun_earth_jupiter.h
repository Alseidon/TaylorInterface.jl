/* taylor Version 2.1, May 26, 2023 */
/* Using coef lib: MY_FLOAT */
/* Using jet lib: jet_1. n symbol, degree 1 */
/************************************************************************
 *
 *  A sample taylor.h
 *     Here is a list of macros/functions needed to compile the auto
 *     generated taylor polynomial procedure.  
 *
 */


#ifdef __cplusplus
extern "C"
{
#endif
/***********************************************************************
 *
 * Code generated by the TAYLOR translator.
 */

#ifndef _NUMBER_OF_JET_VARS_
#define _NUMBER_OF_STATE_VARS_         6
#define _NUMBER_OF_JET_VARS_           6
#define _NUMBER_OF_MAX_SYMBOLS_        6
#define _MAX_DEGREE_OF_JET_VARS_       1
#define _JET_COEFFICIENTS_COUNT_TOTAL_ 7
#define _MAX_SIZE_OF_JET_VAR_          7
#endif

#ifndef _TAYLOR_H_
#define _TAYLOR_H_
typedef double MY_FLOAT;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
/*
 *  MY_FLOAT is the data type to be used in computing derivatives. 
 *  It may be 'float', 'double' or user defined private data types
 *  like 'long double', 'complex' etc. 
 */

/* for double or long double, don't need to initialize */
#define   InitMyFloat(r)            
#define   ClearMyFloat(r)           
 
/* assign b to a */
#define   AssignMyFloat(a, b)       {(a)=(b);}

/* create a MY_FLOAT from a, assigne to r. a is an integer or a float */
#define   MakeMyFloatA(r,a)         (r=(double)(a))

/* create a MY_FLOAT from string, a is an integer or a float, s is its string representation */
#define   MakeMyFloatC(r,s,a)       (r=(double)(a))

/* create a MY_FLOAT from a, assign to r and return r */
#define   MakeMyFloatB(r,a)         (r=(double)(a),r)

/* addition r=a+b   */
#define   AddMyFloatA(r,a,b)        (r=(a)+(b))
#define   AddMyFloatD               AddMyFloatA
#define   AddMyFloatSI              AddMyFloatA

/* substraction r=a-b */
#define   SubtractMyFloatA(r,a,b)   (r=(a)-(b))
#define   SubtractMyFloatD          SubtractMyFloatA
#define   SubtractMyFloatSI         SubtractMyFloatA
#define   SubtractSIMyFloat         SubtractMyFloatA
#define   SubtractDMyFloat          SubtractMyFloatA

/* multiplication r=a*b */
#define   MultiplyMyFloatA(r,a,b)   (r=(a)*(b))
#define   MultiplyMyFloatD          MultiplyMyFloatA
#define   MultiplyMyFloatSI         MultiplyMyFloatA

/* division r=a/b */
#define   DivideMyFloatA(r,a,b)     (r=(a)/(b))
#define   DivideMyFloatD(r,a,b)     (r=(a)/(double)(b))
#define   DivideMyFloatSI           DivideMyFloatD
#define   DivideDMyFloat(r,a,b)     (r=(double)(a)/(b))
#define   DivideSIMyFloat           DivideDMyFloat

/* division by an integer r=a/i */
#define   DivideMyFloatByInt(r,a,i)    (r=(a)/(double)(i))
/* negation r=-a*/
#define   NegateMyFloatA(r,a)          (r= -(a))

/* square root r=sqrt(a) */
#define   sqrtMyFloatA(r,a)            (r=sqrt(a))
/* exponentiation r=a^b */
#define   ExponentiateMyFloatA(r,a,b)  (r=pow((a),(b)))
/* exponentiation r=a^b, b is an integer */
#define   ExponentiateMyFloatIA(r,a,b) (r=pow((a),(double)(b)))
/* sin(a)  r=sin(a) */
#define   sinMyFloatA(r,a)             (r=sin((a)))
/* cos(a)  r=cos(a) */
#define   cosMyFloatA(r,a)             (r=cos((a)))
/* tan(a)  r=tan(a) */
#define   tanMyFloatA(r,a)             (r=tan((a)))
/* atan(a) r=atan(a) */
#define   atanMyFloatA(r,a)            (r=atan((a)))
/* exp(a)  r=exp(a) */
#define   expMyFloatA(r,a)             (r=exp((a)))
/* log(a)  r=log(a) */
#define   logMyFloatA(r,a)             (r=log((a)))
/* sinh(a) r=sinh(a) */
#define   sinhMyFloatA(r,a)            (r=sinh(a))
/* cosh(a) r=cosh(a) */
#define   coshMyFloatA(r,a)            (r=cosh(a))
/* tanh(a) r=tanh(a) */
#define   tanhMyFloatA(r,a)            (r=tanh(a))


/* log10(a)  r=log10(a) */
#define   log10MyFloatA(r,a)           (r=log10((a)))
/* fabs(a) r=fabs(a) */
#define   fabsMyFloatA(r,a)            (r=fabs(a))

/* convert to int */
#define   MyFloatToInt(ir,fa)          (ir=(int)(fa))
/* convert to double */
#define   MyFloatToDouble(ir,fa)       (ir=(double)(fa))
/* convert to string */
#define   MyFloatToString3(s,fmt,a)    sprintf(s,fmt,(double)(a))
#define   MyFloatToString(s,a)         MyFloatToString3(s,"% .15e",a)


/* boolean operation  */
#define   MyFloatA_GE_B(a,b)        ((a)>=(b))
#define   MyFloatA_GT_B(a,b)        ((a)> (b))
#define   MyFloatA_LE_B(a,b)        ((a)<=(b))
#define   MyFloatA_LT_B(a,b)        ((a)< (b))
#define   MyFloatA_EQ_B(a,b)        ((a)==(b))
#define   MyFloatA_NEQ_B(a,b)       ((a)!=(b))
#define   MyFloatA_CMP_B(a,b)       ((a)-(b))
#define   MyFloatA_CMPABS_B(a,b)    (fabs(a)-fabs(b))


#define   OutputMyFloat3(file,fmt,a) fprintf(file,fmt,(double)(a))
#define   OutputMyFloat(a)           OutputMyFloat3(stdout,"%g ",a)

#define   InputMyFloat3(file,fmt,a)  fscanf(file,fmt,&(a))
#define   InputMyFloat(a)            InputMyFloat3(stdin,"%lf ",a)

#define   StringToMyFloat4(s,fmt,a,n) (sscanf(s,fmt,&(a),n),(s)+*(n))
#define   StringToMyFloat3(s,fmt,a)  sscanf(s,fmt,&(a))
#define   StringToMyFloat(s,a)       StringToMyFloat3(s,"%lf ",a)

/************************************************************************/

#endif

/*** MY_JET ***/
#ifndef _MY_JET_H_
#define _MY_JET_H_

#define MY_JET_DATA(x,i) ((x)[i])

/*** MY_COEF ***/
#ifndef _MY_COEF_H_
#define _MY_COEF_H_

#define _MY_COEF_MAX_NUM_SYMBOLS_ 0
#define _MY_COEF_MAX_DEGREE_ 0
#define _MY_COEF_TOTAL_COEFFICIENTS_COUNT_ 1
#define MY_COEF MY_FLOAT



#define MY_COEF_FUN(x) mycoef_myfloat_ ## x ## _auto
#endif /* _MY_COEF_H_ */

/* HEADER jet_1_t_auto */

#include <stdio.h>

typedef MY_COEF* jet_1_t_auto;
typedef jet_1_t_auto* jet_1_ptr_auto;

int* jet_1_monomial_counts_auto(void);
int* jet_1_monomial_offsets_auto(void);

void jet_1_initup2_auto(int, int);
#define jet_1_initup_auto() jet_1_initup2_auto(_NUMBER_OF_MAX_SYMBOLS_,_MAX_DEGREE_OF_JET_VARS_)
size_t jet_1_init_auto(jet_1_ptr_auto);
void jet_1_clean_auto(jet_1_ptr_auto);
void jet_1_cleanup_auto(void);

int jet_1_get_num_symbs_auto(void);
int jet_1_get_deg_auto(void);
int jet_1_set_num_symbs_auto(int);
int jet_1_set_deg_auto(int);

/* assign */
void jet_1_set_auto(jet_1_t_auto, jet_1_t_auto);

void jet_1_set_coef_auto(jet_1_t_auto, MY_COEF);
void jet_1_set_myfloat_auto(jet_1_t_auto, MY_FLOAT);
void jet_1_set_d_auto(jet_1_t_auto, double);
void jet_1_set_si_auto(jet_1_t_auto, int);

void jet_1_set_coef_array_auto(jet_1_t_auto, MY_COEF*);
void jet_1_set_jet_2_coef_array_auto(MY_COEF*, jet_1_t_auto);

void jet_1_set_myfloat_array_auto(jet_1_t_auto, MY_FLOAT*);
void jet_1_set_jet_2_myfloat_array_auto(MY_FLOAT*, jet_1_t_auto);

MY_FLOAT* jet_1_to_myfloat_auto(jet_1_t_auto);

void jet_1_eval_auto(MY_COEF[1], jet_1_t_auto, MY_FLOAT[]);

/* access to coef */
MY_COEF* jet_1_get_coef_auto(jet_1_t_auto, const int[]);
MY_COEF* jet_1_coef0_auto(jet_1_t_auto);
MY_COEF* jet_1_coef1_auto(jet_1_t_auto, int);

/* norms */
void jet_1_nrminf_auto(MY_FLOAT[1], jet_1_t_auto);
void jet_1_nrm2_auto(MY_FLOAT[1], jet_1_t_auto);

/* elemental arithmetic */
void jet_1_neg_auto(jet_1_t_auto, jet_1_t_auto);

void jet_1_add2_auto(jet_1_t_auto, jet_1_t_auto, jet_1_t_auto);
void jet_1_sub2_auto(jet_1_t_auto, jet_1_t_auto, jet_1_t_auto);
void jet_1_mul2_auto(jet_1_t_auto, jet_1_t_auto, jet_1_t_auto);
void jet_1_div2_auto(jet_1_t_auto, jet_1_t_auto, jet_1_t_auto);

void jet_1_add2_coef_auto(jet_1_t_auto, jet_1_t_auto, MY_COEF);
void jet_1_sub2_coef_auto(jet_1_t_auto, jet_1_t_auto, MY_COEF);
void jet_1_coef_sub2_auto(jet_1_t_auto, MY_COEF, jet_1_t_auto);
void jet_1_mul2_coef_auto(jet_1_t_auto, jet_1_t_auto, MY_COEF);
void jet_1_div2_coef_auto(jet_1_t_auto, jet_1_t_auto, MY_COEF);
void jet_1_coef_div2_auto(jet_1_t_auto, MY_COEF, jet_1_t_auto);

void jet_1_add2_myfloat_auto(jet_1_t_auto, jet_1_t_auto, MY_FLOAT);
void jet_1_sub2_myfloat_auto(jet_1_t_auto, jet_1_t_auto, MY_FLOAT);
void jet_1_myfloat_sub2_auto(jet_1_t_auto, MY_FLOAT, jet_1_t_auto);
void jet_1_mul2_myfloat_auto(jet_1_t_auto, jet_1_t_auto, MY_FLOAT);
void jet_1_div2_myfloat_auto(jet_1_t_auto, jet_1_t_auto, MY_FLOAT);
void jet_1_myfloat_div2_auto(jet_1_t_auto, MY_FLOAT, jet_1_t_auto);

void jet_1_add2_d_auto(jet_1_t_auto, jet_1_t_auto, double);
void jet_1_sub2_d_auto(jet_1_t_auto, jet_1_t_auto, double);
void jet_1_d_sub2_auto(jet_1_t_auto, double, jet_1_t_auto);
void jet_1_mul2_d_auto(jet_1_t_auto, jet_1_t_auto, double);
void jet_1_div2_d_auto(jet_1_t_auto, jet_1_t_auto, double);
void jet_1_d_div2_auto(jet_1_t_auto, double, jet_1_t_auto);

void jet_1_add2_si_auto(jet_1_t_auto, jet_1_t_auto, int);
void jet_1_sub2_si_auto(jet_1_t_auto, jet_1_t_auto, int);
void jet_1_si_sub2_auto(jet_1_t_auto, int, jet_1_t_auto);
void jet_1_mul2_si_auto(jet_1_t_auto, jet_1_t_auto, int);
void jet_1_div2_si_auto(jet_1_t_auto, jet_1_t_auto, int);
void jet_1_si_div2_auto(jet_1_t_auto, int, jet_1_t_auto);

/* elemental functions */
void jet_1_set_sqrt_auto(jet_1_t_auto, jet_1_t_auto);

void jet_1_set_pow_myfloat_auto(jet_1_t_auto, jet_1_t_auto, MY_FLOAT);

void jet_1_set_exp_auto(jet_1_t_auto, jet_1_t_auto);
void jet_1_set_log_auto(jet_1_t_auto, jet_1_t_auto);

void jet_1_set_sin_auto(jet_1_t_auto, jet_1_t_auto);
void jet_1_set_cos_auto(jet_1_t_auto, jet_1_t_auto);
void jet_1_set_tan_auto(jet_1_t_auto, jet_1_t_auto);
void jet_1_set_atan_auto(jet_1_t_auto, jet_1_t_auto);

void jet_1_set_sinh_auto(jet_1_t_auto, jet_1_t_auto);
void jet_1_set_cosh_auto(jet_1_t_auto, jet_1_t_auto);

/* I/O handles */
void jet_1_fprintf_auto(FILE *file, const char *, jet_1_t_auto);
#define jet_1_printf_auto(fmt,a) jet_1_fprintf_auto(stdout,fmt,a)

void jet_1_fscanf_auto(FILE *file, const char *, jet_1_t_auto);
void jet_1_sscanf_auto(const char *, const char *, jet_1_t_auto);

/* Macros used in the integration */
typedef jet_1_t_auto MY_JET;
#define InitUpJet2(nsymbs,deg)     jet_1_initup2_auto(nsymbs,deg)
#define InitUpJet()                InitUpJet2(_NUMBER_OF_MAX_SYMBOLS_,_MAX_DEGREE_OF_JET_VARS_)
#define InitJet(a)                 jet_1_init_auto(&(a))
#define ClearJet(a)                jet_1_clean_auto(&(a))
#define ClearUpJet()               jet_1_cleanup_auto()
#define GetJetVarDegree()          jet_1_get_deg_auto()
#define GetJetNumSymbols()         jet_1_get_num_symbs_auto()
#define SetJetVarDegree(a)         jet_1_set_deg_auto(a)
#define SetJetNumSymbols(a)        jet_1_set_num_symbs_auto(a)
#define InitJetParameter(a,i)      undefined

#define NormJet(a,x)               {MakeMyFloatC(a,"0",0);jet_1_nrminf_auto(&(a),x);}
#define NormJet2(a,x)              {MakeMyFloatC(a,"0",0);jet_1_nrm2_auto(&(a),x);}

#define NegateJetA(t,s)            jet_1_neg_auto(t,s)
#define AssignJetToFloat(t,s)      AssignMyFloat(t,*jet_1_to_myfloat_auto(s))
#define AssignFloatToJet(t,f)      jet_1_set_myfloat_auto(t,f)


#define AssignJetToFloatArray(t,s)  jet_1_set_jet_2_myfloat_array_auto(t,s)
#define AssignFloatArrayToJet(t,f)  jet_1_set_myfloat_array_auto(t,f)


#define AssignJetToJet(t,s)        jet_1_set_auto(t,s)
#define AddJetJetA(t,a,b)          jet_1_add2_auto(t,a,b)
#define AddFloatJetA(t,a,b)        jet_1_add2_myfloat_auto(t,b,a)
#define AddJetFloatA(t,a,b)        jet_1_add2_myfloat_auto(t,a,b)

#define MultiplyJetFloatA(t,a,b)   jet_1_mul2_myfloat_auto(t,a,b)
#define MultiplyJetJetA(t,a,b)     jet_1_mul2_auto(t,a,b)
#define MultiplyFloatJetA(t,a,b)   jet_1_mul2_myfloat_auto(t,b,a)

#define DivideFloatJetA(t,a,b)     jet_1_myfloat_div2_auto(t,a,b)
#define DivideJetJetA(t,a,b)       jet_1_div2_auto(t,a,b)
#define DivideJetFloatA(t,a,b)     jet_1_div2_myfloat_auto(t,a,b)

#define SubtractFloatJetA(t,a,b)   jet_1_myfloat_sub2_auto(t,a,b)
#define SubtractJetFloatA(t,a,b)   jet_1_sub2_myfloat_auto(t,a,b)
#define SubtractJetJetA(t,a,b)     jet_1_sub2_auto(t,a,b)

#define ExponentiateJetCstA(t,s,e) jet_1_set_pow_myfloat_auto(t,s,e)

#define cosJetA(t,a)               jet_1_set_cos_auto(t,a)
#define sinJetA(t,a)               jet_1_set_sin_auto(t,a)
#define sqrtJetA(t,a)              jet_1_set_sqrt_auto(t,a)
#define tanJetA(r,a)               jet_1_set_tan_auto(r,a)
#define atanJetA(r,a)              jet_1_set_atan_auto(r,a)
#define expJetA(r,a)               jet_1_set_exp_auto(r,a)
#define logJetA(r,a)               jet_1_set_log_auto(r,a)
#define sinhJetA(r,a)              jet_1_set_sinh_auto(r,a)
#define coshJetA(r,a)              jet_1_set_cosh_auto(r,a)
#define tanhJetA(r,a)              undefined
#define log10JetA(r,a)             undefined

#define InputJetFromString(t,a)    taylor_input_jet_from_string(t,a)
#define InputJet(t,a,b)            taylor_input_jet_from_stdin(t,b)
#define OutputJet2File(file,fmt,t) jet_1_fprintf_auto(file,fmt,t)
#define OutputJet(fmt,t)           OutputJet2File(stdout,fmt,t)
#define InputFile2Jet(file,fmt,t) jet_1_fscanf_auto(file,fmt,t)

#define EvalJet(v,x,s)             jet_1_eval_auto(&(v),x,s)
#define JetCoefficient(x,idx)      jet_1_get_coef_auto(x,idx)
/* END MACROS MY_JET */

/* END HEADER jet_1_t_auto */

#define MY_JET_FUN(x) jet_1_ ## x ## _auto
#endif /* _MY_JET_H_ */

/* JET IO Helpers */

/* Set Jet values  */
int taylor_make_jet(MY_JET a, MY_COEF *mycoefs, MY_FLOAT *myfloats, double *values);
int taylor_make_identity_jets(MY_JET *inOut, MY_COEF *mycoefs, MY_FLOAT *myfloats, double *values);
int taylor_make_unit_jet(MY_JET a, int idx, MY_COEF *mycoef, MY_FLOAT *myfloat, double *value);
int taylor_set_jet(MY_JET a, MY_COEF *mycoefs, MY_FLOAT *myfloats, double *values, int include_state);

/* Convert Jet to array */
MY_COEF *taylor_convert_jet_to_array(MY_JET a, int include_state);

/* Input/Output Jet */
int taylor_input_jet_from_stdin(MY_JET a, int idx) ;
int taylor_input_jet_from_string(MY_JET a, const char *str);
int taylor_output_jet(FILE *file, const char *fmt, MY_JET a);

/* Init/Cleanup Library/Jet */
void taylor_initialize_jet_library();
void taylor_initialize_jet_library2(int nsymbs, int degree);
void taylor_initialize_jet_variable(MY_JET *jet);
void taylor_clear_jet_variable(MY_JET *jet);
void taylor_clear_up_jet_library();
int taylor_set_jet_variable_number_of_symbols(int);
int taylor_set_jet_variable_degree(int);

void taylor_jet_reduce(MY_JET, double *);
MY_FLOAT *taylor_get_jet_data_array(MY_JET);
const char **taylor_get_variable_names();
const char **taylor_get_jet_monomials();

/* END... JET IO Helpers */


MY_FLOAT **taylor_coefficients_auto(MY_FLOAT t, MY_FLOAT *x, int order);

MY_FLOAT **taylor_coefficients_autoA(MY_FLOAT t, MY_FLOAT *x, int order, int reuse_last_computation);

MY_FLOAT **taylor_coefficients_auto_A(MY_FLOAT t, MY_FLOAT *x, int order, int reuse_last_computation, MY_JET *jetIn, MY_JET ***jetOut);
int       taylor_step_auto(MY_FLOAT *ti, MY_FLOAT *x, int dir, int step_ctl,
                         double log10abserr, double log10relerr,
                         MY_FLOAT *endtime, MY_FLOAT *ht, int *order, MY_JET *jetInOut);

/************************************************************************/

#ifdef __cplusplus
}
#endif
