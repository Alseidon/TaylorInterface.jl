# TaylorInterface

[![Build Status](https://github.com/Alseidon/TaylorInterface.jl/actions/workflows/CI.yml/badge.svg?branch=main)](https://github.com/Alseidon/TaylorInterface.jl/actions/workflows/CI.yml?query=branch%3Amain)

[![](https://img.shields.io/badge/docs-latest-blue.svg)](https://alseidon.github.io/TaylorInterface.jl/dev)

## Introduction

This package implements a interface in Julia to the taylor tool created by [Àngel Jorba](http://www.maia.ub.es/~angel/) and contributors. taylor translates movement equations given in a text file to highly efficient C code, also allowing the integration of arbitrary degree jet transport. Its features include:

- parallelisable code (using OpenMP)
- flexibility in number type (double, complex, MPFR, user-defined...)

For more information, [see here](http://www.maia.ub.es/~angel/taylor/).

At the moment, TaylorInterface supports jet transport for one variable or one symbol, and doesn't support parallelisation of the C code or changing the number type from double. As taylor currently only works on Linux systems, so does TaylorInterface.

This package is still in development; feel free to contact me for any questions, suggestions or remarks!

## Installation

You can simply install this package from the Julia REPL, using Pkg. Run Julia, enter `]` to enter the package manager, and then:

```julia
julia> ]
(v1.10) pkg> add https://github.com/Alseidon/TaylorInterface.jl
```

Otherwise, you can run
```julia
import Pkg
Pkg.add(url="https://github.com/Alseidon/TaylorInterface.jl")
```

You also need the taylor tool installed to use this package. You can find it [here (latest version)](https://github.com/joang/taylor2-dist) or install it by running:

```bash
curl -sS https://web.ma.utexas.edu/repos/deb/taylor.gpg.key | gpg --dearmor | sudo tee /usr/share/keyrings/taylor.gpg
echo "deb [signed-by=/usr/share/keyrings/taylor.gpg] http://web.ma.utexas.edu/repos/deb focal main" | sudo tee /etc/apt/sources.list.d/taylor.list
sudo apt update
sudo apt install taylor
```

## First approach

This package introduces two structures: `TaylorGenerator` generates a directory containing the files corresponding to a given equation file, and `TaylorHandler` opens the library thus generated and serves as an interface to access its functions.

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

generator = TaylorGenerator("eqs.txt")
generate_dir(generator)
```

This will create a directory, copy the equation file in it, call taylor on this file, wrap the generated C files with some convenience functions, and compile them in a `lib.so` file in the directory. By default, the directory sits in the current directory, and is named `taylor_[RANDOM_STRING]`, but you can change both parameters with `parent_path` and `name` respectively.

Now, to open the generated library, we get a `TaylorHandler`:

```julia
handler = get_handler(generator, false)
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
    handler.symbols["flow"],
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
TaylorInterface.clear_dir(handler) # TaylorInterface.clear_dir(generator) also works
```

## Remarks

We propose some default models that come with the package; you can get them with

```julia
get_model(modelname)
```

At the moment, we propose:
- `rpb_sun_earth`, the restricted three-body problem for the Sun+Earth system, in synodic (co-rotating) coordinates, assuming circular motion
- `bcp_sun_earth_jupiter` and `bcp_sun_earth_venus`, where we add a perturbation from a planet in circular motion either Jupiter or Venus (the model is called bicircular)
- `rpb_SE_nojet`, the same problem as the first, but whereas for the three other cases we computed first-order variational equations, here we remove jet transport for speed.

Note that you will need to compile the model with `compile_eqs(handler)` in order to use it.
