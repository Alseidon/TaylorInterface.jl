# [Introduction](@id introduction)

## Initial value problem

At the beginning was an equation... As such:
```math
\frac{dx}{dt}(t) = f(x, t)
```

Where ``x`` is a vector in ``\mathbb{R}^n``, and ``f(x, t)`` a vector field which can depend on the time ``t``. We are interested, given an initial condition ``x_0``, on the evolution of the function ``x(t)`` which:
- follows the above equation;
- satisfies ``x(0) = x_0``.

This is called an [initial value problem](https://en.wikipedia.org/wiki/Initial_value_problem). `TaylorInterface.jl` allows us to integrate the above equation, using Taylor's method (see, for instance, `TaylorIntegration.jl`'s [documentation](https://perezhz.github.io/TaylorIntegration.jl/stable/taylor_method/) which sums it up very well.)

Let's take, as an example, a harmonic oscillator: a mass with one degree of liberty ``x``, subject to a force ``F(x) = - k x``, with ``k>0`` a constant. Its state is described by its position ``x`` and its velocity ``v``, and the equations of motions are

```math
\begin{align}
\dot{x}(t) &= v(t) \\
\dot{v}(t) &= -C * x(t)
\end{align}
```

where we denoted the derivative with respect to time with a dot, and rewritten the constant ``k / m`` as ``C`` (dividing by the mass).

## Diving in the code

The first step is to write the equations in a file, according to the syntax defined in [this manual](https://github.com/joang/taylor2-dist/blob/main/src/manual/manual.pdf). This is the manual of taylor, a tool used by `TaylorInterface.jl` behind the scenes. The equation file will be converted to fast functions in C, which then `TaylorInterface.jl` gives access to. But let's write our equation file -- which we can do from Julia:

```Julia
equations_filename = "equations.txt"
equations = """
c = 1.0;

diff(x, t) = v;
diff(v, t) = -(c * x);
"""

open(equations_filename, "w") do eq_file
    write(eq_file, equations)
end
```

Now, let's transform them to C code!
```Julia
using TaylorInterface
# if you haven't installed it yet, run the line below
# import Pkg; Pkg.add(url="https://github.com/Alseidon/TaylorInterface.jl")

generator = TaylorGenerator(name="oscillator", eqs_filename=equations_filename)
generate_dir(generator)
```

The last line will create a directory called `taylor_oscillator` and put all the C code in it. It also compiles it into a shared library, which we now want to open:

```Julia
handler = get_handler(generator)
```

As the compilation has already been taken care of, we can simply open the library:

```Julia
open_lib(handler)
```

`handler` offers two keywords to interact with the library:
- `handler.lib` offers direct access to the library
- `handler.symbols` is a dictionary linking some function names (as strings) to their symbols. Indeed, the package adds some wrapping functions around the initial taylor output, to improve usability. Currently, there are `flow`, `tstep` and `tstep_reverse` (for more info, see [here](@ref cfunctions)).

Here, we want to get the value of ``x(t)`` at a certain time ``t``, given an initial condition ``x_0``. To do this, we define the following function:

```Julia
function flow_oscillator(x0, t)
    x_fin = zero(x0)
    ccall(
        handler.symbols["flow"],
        Cvoid, (Cdouble, Ptr{Cdouble}, Ptr{Cdouble}, Ptr{Cdouble}),
        t, x0, x_fin, Ptr{Cvoid}()
    )
    return x_fin
end
```

And there you go! Let's visualise the movement of our oscillator:

```Julia
using Plots

x0 = [1., 0]

times = 0:0.1:10π
xs = [flow_oscillator(x0, t) for t in times]
positions = [x[1] for x in xs]
velocities = [x[2] for x in xs]

plot(times, positions, label="positions")
plot!(times, velocities, label="velocities")
xlabel!("\\\$t\\\$")
show()
```

And thus, you can see nice 2π-periodic oscillations.