# TaylorInterface.jl

Documentation under construction.

## Author

- [Alexandre Prieur](https://www.alexandre.prieur.eu), PhD student at the [Observatoire de Paris](https://www.obspm.fr)

## Introduction

This package implements a interface in Julia to the taylor tool created by Àngel Jorba and contributors. taylor translates movement equations given in a text file to highly efficient C code, also allowing the integration of arbitrary degree jet transport. Its features include:

- parallelisable code (using OpenMP)
- flexibility in number type (double, complex, MPFR, user-defined...)

For more information, [see here](http://www.maia.ub.es/~angel/taylor/).

At the moment, TaylorInterface supports jet transport for one variable or one symbol, and doesn't support parallelisation of the C code or changing the number type from double. As taylor currently only works on Linux systems, so does TaylorInterface.

## Installation

You can simply install this package from the Julia REPL, using Pkg. Run Julia, enter `]` to enter the package manager, and then:

```julia
julia> ]
(v1.9) pkg> add https://github.com/Alseidon/TaylorInterface.jl
```

Otherwise, you can run
```julia
import Pkg
Pkg.add("https://github.com/Alseidon/TaylorInterface.jl")
```

You also need the taylor tool installed to use this package. You can find it [here (latest version)](https://github.com/joang/taylor2-dist) or install it by running:

```bash
curl -sS https://web.ma.utexas.edu/repos/deb/taylor.gpg.key | gpg --dearmor | sudo tee /usr/share/keyrings/taylor.gpg
echo "deb [signed-by=/usr/share/keyrings/taylor.gpg] http://web.ma.utexas.edu/repos/deb focal main" | sudo tee /etc/apt/sources.list.d/taylor.list
sudo apt update
sudo apt install taylor
```

Now, you might either want to take a look at the [quick start](@ref quickstart), dive into the [internal machinery](@ref internals) of `TaylorInterface.jl`, or simply search the [full docs](@ref fulldocs).