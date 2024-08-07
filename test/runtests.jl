using TaylorInterface
using Test

@testset "Opening, closing, creating models" begin
    #= DEFAULT MODELS =#
    default_models = map(
        s->s[8:end],
        filter(s->s[1:min(length(s), 7)] == "taylor_", readdir(TaylorInterface.get_models_dir()))
    )
    handlers = map(name->get_model(name, false), default_models)
    map(han->compile_eqs(han, true), handlers)
    map(open_lib, handlers)
    map(close_lib, handlers)

    #= CREATING A MODEL =#
    gen_jet = TaylorGenerator(
        eqs_filename = joinpath(TaylorInterface.get_models_dir(),
            "eqs", "rpb_sun_earth.eqs"),
        parent_path = tempdir()
    )
    gen_no_jet = TaylorGenerator(
        eqs_filename = joinpath(TaylorInterface.get_models_dir(),
            "eqs", "rpb_SE_nojet.eqs"),
        parent_path = tempdir()
    )
    generate_dir(gen_jet, true)
    generate_dir(gen_no_jet, true)
    hand_jet = get_handler(gen_jet, true)
    hand_no_jet = get_handler(gen_no_jet, true)
    TaylorInterface.clear_dir(gen_jet)
    TaylorInterface.clear_dir(gen_no_jet)
end

include("integration_tests.jl")