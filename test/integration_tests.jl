@testset "Integration tests" begin
    #= DEFAULT MODELS =#
    gen = TaylorGenerator("sincos", "sincos.eqs", ".")
    generate_dir(gen)
    han = get_handler(gen, true)
    
    x = [1., 0.]
    ts = LinRange(0., 2π, 101)
    ys = map(t->flow(x, t, han), ts)
    y1 = map(i->i[1], ys)
    y2 = map(i->i[2], ys)

    @test y1 ≈ cos.(ts)
    @test y2 ≈ -sin.(ts)
    close_lib(han)
    TaylorInterface.clear_dir(gen)
end
