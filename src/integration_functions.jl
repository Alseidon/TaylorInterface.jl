"""
    flow!(han, x, [y], t, df=Ref(nothing))

Wrapper function around the C `flow` function in the `han` TaylorHandler.
    
`df` should be passed as a vector if jet transport is used. In this case, jet transport results will be stored in `df`.

If `y` is passed, the flow result will be stored in it.
"""
function flow!(han, x, y, t, df)
    retval = ccall(han.symbols["flow"], Cint, (Cdouble, Ptr{Cdouble}, Ptr{Cdouble}, Ptr{Cvoid}),
        t, x, y, df
    )
    if retval != 1
        error("return value wasn't 1, but $retval")
    end
    return y
end

function flow!(han, x, t, df=Ref(nothing))
    y = similar(x)
    return flow!(han, x, y, t, df)
end

"""
    flow(han, x, t)

Wrapper function around the C `flow` function in the `han` TaylorHandler. Should only be used if jet transport isn't used; otherwise, use `flow!`.
"""
function flow(han, x, t)
    y = similar(x)
    return flow!(han, x, y, t, Ref(nothing))
end