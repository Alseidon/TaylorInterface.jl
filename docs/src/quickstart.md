# [Quick start](@id quickstart)

## Generating a directory

First, you need an equation file, which looks like this (for more information, see the [taylor manual](https://github.com/joang/taylor2-dist/blob/main/src/manual/manual.pdf)):

```
const1 = 3.14;
const2 = 42.;

var1 = 2*x + const1;

diff(x, t) = px;
diff(px, t) = var1 + const2 * x * x;

jet x, px symbols 2 deg 1;
```

Let's save this in a file, namely `eqs.txt`. Now, we create a `TaylorGenerator` and generate a directory:

```julia
using TaylorInterface

generator = TaylorGenerator(eqs_filename="eqs.txt")
generate_dir(generator)
```

This will create a directory, copy the equation file in it, call taylor on this file, wrap the generated C files with some convenience functions, and compile them in a `lib.so` file in the directory. By default, the directory sits in the current directory, and is named `taylor_[RANDOM_STRING]`, but you can change both parameters with `parent_path` and `name` respectively.

## Opening, using and closing a directory

Now, to open the generated library, we get a `TaylorHandler`:

```julia
handler = get_handler(generator, open=false)
```

If you have the `TaylorGenerator` corresponding to the directory you want to open, you can use `get_handler` as we just did. Otherwise, you need the path to the directory stored in a string; if this string is stored in `path`, then you can use

```julia
handler = TaylorHandler(path)
```

To open the library, we use

```julia
open_lib(handler)
```

Now, the loaded library is in `handler.lib`, and a dictionary to some of its functions is stored in `handler.symbols`. For instance, let's call the Poincaré map for our above example, and for a duration of 1.

```julia
in = [0., 1.]
out = zero(in)
jacobian = zeros(4)

ccall(
    handler.symbols["poinc_map"],
    Cvoid,
    (Cdouble, Ptr{Cdouble}, Ptr{Cdouble}, Ptr{Cdouble}),
    1., out, in, jacobian
)

reshape(jacobian, (2, 2))
```

And finally, we can close our library:

```julia
close_lib(handler)
```

If we don't need the directory anymore, we can delete it:
```julia
clear_dir(handler) # clear_dir(generator) also works
```