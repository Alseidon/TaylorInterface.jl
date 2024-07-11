module TaylorInterface

include("taylor_gen.jl")
include("integration_functions.jl")

export TaylorGenerator, TaylorHandler
export get_model, get_taylor_dir
export generate_dir, compile_eqs
export get_handler
export open_lib, close_lib
export is_open, check_open
export flow, flow!

function __regenerate_model_dirs(check=true)
    eqfiles = readdir(joinpath(get_models_dir(), "eqs"), join=true)
    modelnames = map(i->split(i, ['.', '/'])[end-1], eqfiles)
    gens = map(
        (name, eqfile)->TaylorGenerator(name, eqfile, get_models_dir()),
        modelnames, eqfiles
    )
    map(generate_dir, gens)
    if check
        handlers = map(get_handler, gens)
        map(open_lib, handlers)
        map(close_lib, handlers)
    end
    return
end


end
