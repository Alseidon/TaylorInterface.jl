var documenterSearchIndex = {"docs":
[{"location":"fulldocs/#fulldocs","page":"Full documentation","title":"Full documentation","text":"","category":"section"},{"location":"fulldocs/#Main-structures","page":"Full documentation","title":"Main structures","text":"","category":"section"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"TaylorGenerator","category":"page"},{"location":"fulldocs/#TaylorInterface.TaylorGenerator","page":"Full documentation","title":"TaylorInterface.TaylorGenerator","text":"TaylorGenerator(name=randstring(12), eqs_filename, parent_path=\".\")\n\nStructure used to generate directories and call taylor. The directory name will be $(parent_path)/taylor_$(name). The equation file should follow the syntax required by taylor.\n\n\n\n\n\n","category":"type"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"TaylorHandler","category":"page"},{"location":"fulldocs/#TaylorInterface.TaylorHandler","page":"Full documentation","title":"TaylorInterface.TaylorHandler","text":"TaylorHandler(path)\n\nStructure used to open, use and close directories generated by TaylorGenerator.\n\n\n\n\n\n","category":"type"},{"location":"fulldocs/#Around-the-TaylorGenerator","page":"Full documentation","title":"Around the TaylorGenerator","text":"","category":"section"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"generate_dir","category":"page"},{"location":"fulldocs/#TaylorInterface.generate_dir","page":"Full documentation","title":"TaylorInterface.generate_dir","text":"generate_dir(generator)\n\nGenerates the directory corresponding to the generator, and builds the library.\n\n\n\n\n\n","category":"function"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"get_taylor_dir","category":"page"},{"location":"fulldocs/#TaylorInterface.get_taylor_dir","page":"Full documentation","title":"TaylorInterface.get_taylor_dir","text":"get_taylor_dir(generator)\n\nReturns the directory associated to the generator.\n\n\n\n\n\n","category":"function"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"get_handler","category":"page"},{"location":"fulldocs/#TaylorInterface.get_handler","page":"Full documentation","title":"TaylorInterface.get_handler","text":"get_handler(generator, open=true)\n\nGet the TaylorHandler corresponding to the generator. If open is true, the library will also be open in the handler.\n\n\n\n\n\n","category":"function"},{"location":"fulldocs/#Around-the-TaylorHandler","page":"Full documentation","title":"Around the TaylorHandler","text":"","category":"section"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"compile_eqs","category":"page"},{"location":"fulldocs/#TaylorInterface.compile_eqs","page":"Full documentation","title":"TaylorInterface.compile_eqs","text":"compile_eqs(generator)\n\nRuns make in the directory of the generator.\n\n\n\n\n\ncompile_eqs(handler)\n\nRuns make in the directory of the handler.\n\n\n\n\n\n","category":"function"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"open_lib","category":"page"},{"location":"fulldocs/#TaylorInterface.open_lib","page":"Full documentation","title":"TaylorInterface.open_lib","text":"open_lib(handler)\n\nOpens the handler's library, storing the loaded library and a dictionary with symbols to functions in the handler.\n\nCurrently, the loaded functions are poinc_map, tstep and tstep_reverse.\n\n\n\n\n\n","category":"function"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"close_lib","category":"page"},{"location":"fulldocs/#TaylorInterface.close_lib","page":"Full documentation","title":"TaylorInterface.close_lib","text":"close_lib(handler)\n\nClose the library referred by the handler.\n\n\n\n\n\n","category":"function"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"clear_lib","category":"page"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"is_open","category":"page"},{"location":"fulldocs/#TaylorInterface.is_open","page":"Full documentation","title":"TaylorInterface.is_open","text":"is_open(handler)\n\nCheck if handler refers to an open library.\n\n\n\n\n\n","category":"function"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"check_open","category":"page"},{"location":"fulldocs/#TaylorInterface.check_open","page":"Full documentation","title":"TaylorInterface.check_open","text":"check_open(handler)\n\nCheck if handler refers to an open library, and opens it if not.\n\n\n\n\n\n","category":"function"},{"location":"fulldocs/#Default-models","page":"Full documentation","title":"Default models","text":"","category":"section"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"get_model","category":"page"},{"location":"fulldocs/#TaylorInterface.get_model","page":"Full documentation","title":"TaylorInterface.get_model","text":"get_model(name, open=true)\n\nGet the TaylorHandler corresponding to a default model in this package. If open is true, the library will also be open in the handler.\n\nWarning: name should NOT contain the prefix \"taylor_h\".\n\n\n\n\n\n","category":"function"},{"location":"fulldocs/#Internal-functions","page":"Full documentation","title":"Internal functions","text":"","category":"section"},{"location":"fulldocs/#File-system-navigation","page":"Full documentation","title":"File system navigation","text":"","category":"section"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"These functions are mainly intended for internal use and navigation within the file system.","category":"page"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"get_dir_src","category":"page"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"get_models_dir","category":"page"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"get_wrappers","category":"page"},{"location":"fulldocs/#Taylor-flags","page":"Full documentation","title":"Taylor flags","text":"","category":"section"},{"location":"fulldocs/","page":"Full documentation","title":"Full documentation","text":"get_jet_flag","category":"page"},{"location":"quickstart/#quickstart","page":"Quick start","title":"Quick start","text":"","category":"section"},{"location":"quickstart/#Generating-a-directory","page":"Quick start","title":"Generating a directory","text":"","category":"section"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"First, you need an equation file, which looks like this (for more information, see the taylor manual):","category":"page"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"const1 = 3.14;\nconst2 = 42.;\n\nvar1 = 2*x + const1;\n\ndiff(x, t) = px;\ndiff(px, t) = var1 + const2 * x * x;\n\njet x, px symbols 2 deg 1;","category":"page"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"Let's save this in a file, namely eqs.txt. Now, we create a TaylorGenerator and generate a directory:","category":"page"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"using TaylorInterface\n\ngenerator = TaylorGenerator(eqs_filename=\"eqs.txt\")\ngenerate_dir(generator)","category":"page"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"This will create a directory, copy the equation file in it, call taylor on this file, wrap the generated C files with some convenience functions, and compile them in a lib.so file in the directory. By default, the directory sits in the current directory, and is named taylor_[RANDOM_STRING], but you can change both parameters with parent_path and name respectively.","category":"page"},{"location":"quickstart/#Opening,-using-and-closing-a-directory","page":"Quick start","title":"Opening, using and closing a directory","text":"","category":"section"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"Now, to open the generated library, we get a TaylorHandler:","category":"page"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"handler = get_handler(generator, open=false)","category":"page"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"If you have the TaylorGenerator corresponding to the directory you want to open, you can use get_handler as we just did. Otherwise, you need the path to the directory stored in a string; if this string is stored in path, then you can use","category":"page"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"handler = TaylorHandler(path)","category":"page"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"To open the library, we use","category":"page"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"open_lib(handler)","category":"page"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"Now, the loaded library is in handler.lib, and a dictionary to some of its functions is stored in handler.symbols. For instance, let's call the Poincaré map for our above example, and for a duration of 1.","category":"page"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"in = [0., 1.]\nout = zero(in)\njacobian = zeros(4)\n\nccall(\n    handler.symbols[\"poinc_map\"],\n    Cvoid,\n    (Cdouble, Ptr{Cdouble}, Ptr{Cdouble}, Ptr{Cdouble}),\n    1., out, in, jacobian\n)\n\nreshape(jacobian, (2, 2))","category":"page"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"And finally, we can close our library:","category":"page"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"close_lib(handler)","category":"page"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"If we don't need the directory anymore, we can delete it:","category":"page"},{"location":"quickstart/","page":"Quick start","title":"Quick start","text":"clear_dir(handler) # clear_dir(generator) also works","category":"page"},{"location":"#TaylorInterface.jl","page":"Home","title":"TaylorInterface.jl","text":"","category":"section"},{"location":"","page":"Home","title":"Home","text":"Documentation under construction.","category":"page"},{"location":"#Author","page":"Home","title":"Author","text":"","category":"section"},{"location":"","page":"Home","title":"Home","text":"Alexandre Prieur, PhD student at the Observatoire de Paris","category":"page"},{"location":"#Introduction","page":"Home","title":"Introduction","text":"","category":"section"},{"location":"","page":"Home","title":"Home","text":"This package implements a interface in Julia to the taylor tool created by Àngel Jorba and contributors. taylor translates movement equations given in a text file to highly efficient C code, also allowing the integration of arbitrary degree jet transport. Its features include:","category":"page"},{"location":"","page":"Home","title":"Home","text":"parallelisable code (using OpenMP)\nflexibility in number type (double, complex, MPFR, user-defined...)","category":"page"},{"location":"","page":"Home","title":"Home","text":"For more information, see here.","category":"page"},{"location":"","page":"Home","title":"Home","text":"At the moment, TaylorInterface supports jet transport for one variable or one symbol, and doesn't support parallelisation of the C code or changing the number type from double. As taylor currently only works on Linux systems, so does TaylorInterface.","category":"page"},{"location":"#Installation","page":"Home","title":"Installation","text":"","category":"section"},{"location":"","page":"Home","title":"Home","text":"You can simply install this package from the Julia REPL, using Pkg. Run Julia, enter ] to enter the package manager, and then:","category":"page"},{"location":"","page":"Home","title":"Home","text":"julia> ]\n(v1.9) pkg> add https://github.com/Alseidon/TaylorInterface.jl","category":"page"},{"location":"","page":"Home","title":"Home","text":"Otherwise, you can run","category":"page"},{"location":"","page":"Home","title":"Home","text":"import Pkg\nPkg.add(url=\"https://github.com/Alseidon/TaylorInterface.jl\")","category":"page"},{"location":"","page":"Home","title":"Home","text":"You also need the taylor tool installed to use this package. You can find it here (latest version) or install it by running:","category":"page"},{"location":"","page":"Home","title":"Home","text":"curl -sS https://web.ma.utexas.edu/repos/deb/taylor.gpg.key | gpg --dearmor | sudo tee /usr/share/keyrings/taylor.gpg\necho \"deb [signed-by=/usr/share/keyrings/taylor.gpg] http://web.ma.utexas.edu/repos/deb focal main\" | sudo tee /etc/apt/sources.list.d/taylor.list\nsudo apt update\nsudo apt install taylor","category":"page"},{"location":"","page":"Home","title":"Home","text":"Now, you might either want to take a look at the quick start, dive into the internal machinery of TaylorInterface.jl, or simply search the full docs.","category":"page"},{"location":"internals/#internals","page":"Internals","title":"Internals","text":"","category":"section"},{"location":"internals/#The-structure-of-a-taylor-directory","page":"Internals","title":"The structure of a taylor directory","text":"","category":"section"},{"location":"internals/","page":"Internals","title":"Internals","text":"A taylor directory is structured as such:","category":"page"},{"location":"internals/","page":"Internals","title":"Internals","text":"taylor_ΝAME/\n├── lib.so\n├── Makefile\n├── eq_file.txt\n└── src\n    ├── taylor-ΝAME.c\n    ├── taylor-ΝAME.h\n    ├── taylor-ΝAME.o\n    ├── wrapper-ΝAME.c\n    ├── wrapper-ΝAME.h\n    └── wrapper-ΝAME.o","category":"page"},{"location":"internals/","page":"Internals","title":"Internals","text":"The equation file is a copy of the one given to the TaylorGenerator. The Makefile contains all the recipes necessary to call taylor and compile the resulting files. taylor generates the taylor-NAME.c/h files, which are included by the wrapper-NAME.c/h files. Then, gcc compiles all theses files into .o files, then into lib.so. This final file is the shared library that is opened in Julia.","category":"page"},{"location":"internals/#C-functions","page":"Internals","title":"C functions","text":"","category":"section"},{"location":"internals/","page":"Internals","title":"Internals","text":"The main function defined in the taylor-generated files is taylor_step_auto : this function computes a step of the numerical integration (cf. the taylor manual for more information). You can use it directly (it is included in the lib.so), but it requires some initialisation beforehand if jet transport is at play, or if the number type isn't double.","category":"page"}]
}