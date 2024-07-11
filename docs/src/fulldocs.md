# [Full documentation](@id fulldocs)

## Main structures

```@docs
TaylorGenerator
```

```@docs
TaylorHandler
```

## Around the TaylorGenerator

```@docs
generate_dir
```

```@docs
get_taylor_dir
```

```@docs
get_handler
```

## Around the TaylorHandler

```@docs
compile_eqs
```

```@docs
open_lib
```

```@docs
close_lib
```

```@docs
TaylorInterface.clear_dir
```

```@docs
is_open
```

```@docs
check_open
```

## Integration functions

```@docs
flow!
```

```@docs
flow
```

## Default models

```@docs
get_model
```

## Internal functions

### File system navigation
These functions are mainly intended for internal use and navigation within the file system.

```@docs
TaylorInterface.get_dir_src
```

```@docs
TaylorInterface.get_models_dir
```

```@docs
TaylorInterface.get_wrappers
```

### Taylor flags

```@docs
TaylorInterface.get_jet_flag
```