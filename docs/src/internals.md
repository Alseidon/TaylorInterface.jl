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

## C functions

The main function defined in the taylor-generated files is `taylor_step_auto` : this function computes a step of the numerical integration (cf. the [taylor manual](https://github.com/joang/taylor2-dist/blob/main/src/manual/manual.pd) for more information). You can use it directly (it is included in the `lib.so`), but it requires some initialisation beforehand if jet transport is at play, or if the number type isn't double.