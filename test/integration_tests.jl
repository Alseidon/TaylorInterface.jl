@testset "Integration tests" begin
    #= DEFAULT MODELS =#
    gen = TaylorGenerator("sincos", "sincos.eqs", ".")
    generate_dir(gen)
    han = get_handler(gen, true)

    function flow(x, t, han)
        y = similar(x)
        ccall(han.symbols["flow"], Cint, (Cdouble, Ptr{Cdouble}, Ptr{Cdouble}, Ptr{Cvoid}),
            t, x, y, Ref(nothing)
        )
        return y
    end
    
    x = [1., 0.]
    ts = LinRange(0., 2π, 101)
    ys = map(t->flow(x, t, han), ts)
    y1 = map(i->i[1], ys)
    y2 = map(i->i[2], ys)

    @test y1 ≈ cos.(ts)
    @test y2 ≈ -sin.(ts)
end
