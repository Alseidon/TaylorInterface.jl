module TaylorInterface

include("taylor_gen.jl")

export TaylorGenerator, TaylorHandler
export get_model, get_taylor_dir
export generate_dir, compile_eqs
export open_lib, close_lib
export is_open, check_open

end
