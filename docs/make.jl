push!(LOAD_PATH, "../src")

using TaylorInterface

using Documenter

makedocs(
    sitename = "TaylorInterface.jl",
    modules = [TaylorInterface],
    pages = [
        "Home" => "index.md",
    ]
)
deploydocs(;
    repo = "github.com/Alseidon/TaylorInterface.jl"
)