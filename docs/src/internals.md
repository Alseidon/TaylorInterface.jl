# [Internals](@id internals)

## The structure of a taylor directory

A taylor directory is structured as such:

```
taylor_ΝAME/
├── lib.so
├── Makefile
├── eq_file.txt
└── src
    ├── taylor-ΝAME.c
    ├── taylor-ΝAME.h
    ├── taylor-ΝAME.o
    ├── wrapper-ΝAME.c
    ├── wrapper-ΝAME.h
    └── wrapper-ΝAME.o
```

The equation file is a copy of the one given to the `TaylorGenerator`. The `Makefile` contains all the recipes necessary to call taylor and compile the resulting files. taylor generates the `taylor-NAME.c/h` files, which are included by the `wrapper-NAME.c/h` files. Then, gcc compiles all theses files into `.o` files, then into `lib.so`. This final file is the shared library that is opened in Julia.

## [C functions](@id cfunctions)

### The full taylor_step function

The main function defined in the taylor-generated files is `taylor_step_auto` : this function computes a step of the numerical integration (cf. the [taylor manual](https://github.com/joang/taylor2-dist/blob/main/src/manual/manual.pd) for more information). Its call signature is

```C
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
```

`MY_FLOAT` is the number type defined for taylor (double by default). Here is its documentation:

```
single integration step with taylor method. the parameters are:
ti: on input:  time of the initial condition
    on output: new time
x:  on input:  initial condition
    on output: new condition, corresponding to the (output) time ti
dir: flag to integrate forward or backwards.
    1: forward
   -1: backwards
    WARNING: this flag is ignored if step_ctl (see below) is set to 0.
step_ctl: flag for the step size control. the possible values are:
    0: no step size control, so the step and order are provided by
       the user. the parameter ht is used as step, and the parameter
       order (see below) is used as the order.
    1: standard stepsize control. it uses an approximation to the
       optimal order and to the radius of convergence of the series
       to approximate the 'optimal' step size. It tries to keep
       either the absolute or the relative errors below the given
       values. See the paper for more details.
    2: as 1, but adding an extra condition on the stepsize h: the
       terms of the series --after being multiplied by the suitable
       power of h-- cannot grow.
   -1: user defined stepsize control. the code has to be included
       in the routine compute_timestep_user_defined (you can find
       this routine below). The user should also provide code for
       the selection of degree (see the function
       compute_order_user_defined below).
log10abserr: decimal log of the absolute accuracy. the routine
    tries to keep either the absolute or the relative errors below
    the given thresholds.
log10relerr: decimal log of the relative accuracy. the routine
    tries to keep either the absolute or the relative errors below
    the given thresholds.
endtime: if NULL, it is ignored. if step_ctl (see above) is set
    to 0, it is also ignored. otherwise, if the step size is too
    large, it is reduced so that the new time ti is exactly endtime
    (in that case, the function returns 1).
ht: on input:  ignored/used as a time step (see parameter step_ctl)
    on output: time step used if the pointer is not NULL
order: degree of the taylor expansion.
       input: this parameter is only used if step_ctl is 0,
              or if you add the code for the case step_ctl=3.
              its possible values are:
              < 2: the program will select degree 2 (if step_ctl is 0).
              >=2: the program will use this degree (if step_ctl is 0).
       ouput: degree used if the pointer is not NULL
jetInOut: on input: the value of all declared jet variables
          on output: new value of the jet variable, corresponding to the new time
return value:
 0: ok.
 1: ok, and ti=endtime.  
-1: not ok, unable to compute step size.  double_log  underflow/overflow
```

You can use it directly (it is included in the `lib.so`), but it requires some initialisation beforehand if jet transport is at play, or if the number type isn't double. taylor defines the `InitMyFloat(x)` function to initialize any `MY_FLOAT` variable. For jet transport, you need to call `taylor_initialize_jet_library()` before using it, and `InitJet(x)` on your jet variables. You can refer to `wrapper.h` for an example of the latter case.

### [The wrapping functions](@id wrapping_funcs)

`TaylorInterface.jl` adds some convenience functions in the wrapper. First are two simplified versions of `taylor_step_auto`: `tstep` and `tstep_reverse` (respectively when `*endtime` is positive or negative)

```C
int tstep(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);

int tstep_reverse(MY_FLOAT *ti, MY_FLOAT *x, double log10err, MY_FLOAT *endtime);
```

They simply hide some of `taylor_step_auto`'s parameters, and regroup `log10abserr` and `log10relerr`.

Finally, we include a Poincaré map from 0. to `endtime`:

```C
void flow(double endtime, MY_FLOAT *x, MY_FLOAT *y, MY_FLOAT *df);
```

Where `x` is the initial state, `y` stores the final state and `df` stores the non-zero degree jet transport values.