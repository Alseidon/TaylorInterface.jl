@testset "Integration test -- no jet" begin
    #= NO JET =#
    gen = TaylorGenerator("sincos", "sincos.eqs", ".")
    generate_dir(gen, true)
    han = get_handler(gen, true)
    
    x = [1., 0.]
    ts = LinRange(0., 2π, 101)
    ys = map(t->flow(han, x, t), ts)
    y1 = map(i->i[1], ys)
    y2 = map(i->i[2], ys)

    @test y1 ≈ cos.(ts)
    @test y2 ≈ -sin.(ts)
    close_lib(han)
    TaylorInterface.clear_dir(gen)
end

@testset "Integration test -- jet" begin
    #= JET =#
    gen = TaylorGenerator("sincos_jet", "sincos_jet.eqs", ".")
    generate_dir(gen, true)
    han = get_handler(gen, true)
    
    x = [1., 0.]
    df = zeros(4)
    
    ts = LinRange(0., 2π, 101)
    ys = map(t->flow!(han, x, t, df), ts)
    y1 = map(i->i[1], ys)
    y2 = map(i->i[2], ys)
    
    @test y1 ≈ cos.(ts)
    @test y2 ≈ -sin.(ts)
    close_lib(han)
    TaylorInterface.clear_dir(gen)
end

# @testset "Integration test -- extern" begin
    gen = TaylorGenerator("sincos_extern", "sincos_extern.eqs", ".")
    generate_dir(gen, true)
    han = get_handler(gen, true)
    
    x = [1., 0.]
    df = zeros(4)
    k = 2.
    set_extern_var(han, "k", k)

    
    ts = LinRange(0., 2π, 101)
    ys = map(t->flow!(han, x, t, df), ts)
    y1 = map(i->i[1], ys)
    y2 = map(i->i[2], ys)
    
    @test y1 ≈ cos.(k * ts)
    @test y2 ≈ -sin.(k * ts)
    close_lib(han)
    TaylorInterface.clear_dir(gen)
# end
