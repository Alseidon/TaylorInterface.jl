push!(LOAD_PATH, "../src")

using TaylorInterface

import Pkg; Pkg.add("Documenter")
using Documenter

makedocs(
    sitename = "TaylorInterface.jl",
    modules = [TaylorInterface],
    pages = [
        "Home" => "index.md",
        "Quick start" => "quickstart.md",
        "Compared benchmark" => "speed.md",
        "Internals" => "internals.md",
        "Full documentation" => "fulldocs.md"
    ]
)
deploydocs(;
    repo = "github.com/Alseidon/TaylorInterface.jl"
)