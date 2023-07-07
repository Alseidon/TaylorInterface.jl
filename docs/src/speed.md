# Compared benchmarks

## Running the code

You can run the following code to compare `DifferentialEquations.jl` and `TaylorInterface.jl`

```julia
using DifferentialEquations, TaylorInterface, BenchmarkTools
# import Pkg; Pkg.add(url="https://github.com/Alseidon/TaylorInterface.jl")
# If you haven't installed TaylorInterface

# The problem
f(u, p, t) = 0.0001 * u
u0 = 1 / 2
t_fin = 100.

# TaylorInterface
tmp_eqfile = tempname()
eqfile_text = """
diff(x, t) = 0.0001 * x
"""
open(tmp_eqfile, "w") do file
    write(file, eqfile_text)
end

taylor_gen = TaylorGenerator(eqs_filename=tmp_eqfile, parent_path=tempdir())
generate_dir(taylor_gen)

handler = get_handler(taylor_gen, true)

function f_taylor(
    u_ini::Float64,
    dict::Dict{String, Ptr{Nothing}},
    t::Number;
)
    u_ref = Ref{Cdouble}(u_ini)
    ti = Ref{Cdouble}(0.)
    endtime = Ref{Cdouble}(t)
    return_val = 0
    while (return_val != 1)
        return_val = ccall(
            dict["tstep"],
            Cint,
            (Ptr{Cdouble}, Ref{Cdouble}, Cdouble, Ref{Cdouble}),
            ti,
            u_ref,
            -16.,
            endtime,
        )
    end
    return u_ref.x
end

# DifferentialEquations
function f_diffeq(u0, func, t)
    prob = ODEProblem(func, u0, (0., t))
    return solve(prob, reltol = 1e-16, abstol = 1e-16)[end]
end


# TESTING
## Warmup lap
f_taylor(u0, handler.symbols, t_fin)
f_diffeq(u0, f, t_fin) 

## Tests
@benchmark f_taylor($(u0), $(handler.symbols), $(t_fin))
@benchmark f_diffeq($(u0), $(f), $(t_fin)) 
```

## Results
On a AMD Ryzen 7 3700U, `f_taylor` runs in 184.488 ns ± 92.744 ns, whereas `f_diffeq` runs in 29.223 μs ± 75.737 μs.