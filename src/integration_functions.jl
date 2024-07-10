function flow!(x, y, t, han)
    retval = ccall(han.symbols["flow"], Cint, (Cdouble, Ptr{Cdouble}, Ptr{Cdouble}, Ptr{Cvoid}),
        t, x, y, Ref(nothing)
    )
    if retval != 1
        @error "return value wasn't 1, but $retval"
    end
    return y
end

function flow(x, t, han)
    y = similar(x)
    return flow!(x, y, t, han)
end