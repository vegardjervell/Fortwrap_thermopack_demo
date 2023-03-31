# Fortwrap_thermopack_demo

Sandbox for playing around with the possibility of using FortWrap with ThermoPack.

The dummy test-case is:

* `constants.f90` : Module that is `use`'d by all other modules, but is not wrapped.
* `BaseEoS` : Abstract class 
   * Inheriting classes must override `Fres`
   * Implements `Fideal`, dummy function for ideal gas residual helmholtz energy
   * Implements `pressure`, which calls `Fres` and `Fideal`
* `NotIdGas` : In `directeos.f90` - Concrete class inheriting from `BaseEoS`
* `VariantEoS` : In `Variants.f90` - Abstract class inheriting from `BaseEoS`
   * Inheriting classes must override `internal_comp`
   * Also contains two parameters not found in `BaseEoS` (`param1` and `param2`)
   * Implements `variant_common_comp`
   * `Variant1` : Concrete class inheriting from `VariantEoS`
     * Implements `internal_comp`
     * Implements `Fres`, which calls `internal_comp` and `variant_common_comp`
   * `Variant2` : Concrete class inheriting from `VariantEoS`
     * Implements `internal_comp`, but differently than `Variant1`
     * Implements `Fres`, which calls `internal_comp` and `variant_common_comp`

Some changes have been made to FortWrap in order to make the wrapping work, and to automate generation of [PyBind11](https://pybind11.readthedocs.io/en/stable/) bindings.

Moving forward: 
* Implement internal computations that are not wrapped, to ensure that it is possible to make a minimal wrapper.
* Improve robustness of pybind-bindings generation.

# Current workflow


First: Navigate to the top-level directory of the `fortwrap` project (where `setup.py` is found) and `pip install -e .`

Then: Navigate to the `fortwrap_thermopack_demo` directory (this directory, from now referred to as `demo`). 

Run the script `build.sh`, which does the following:

 * Compile the Fortran source
 * Build the archive `libdemo_fortran.a`
 * Move the archive and `.mod` files to the `demo/wrappers` directory
 * Run `python -m fortwrap -g -i ../FortWrapOptions.txt` from the `demo/src` directory
 * Compile the resulting `FortranISOWrappers.f90` and add it to the `libdemo_fortran.a` archive
 * Compile the `.cpp` files in the `demo/wrappers` directory
 * Compile `demo/main.cpp`

To build the python wrappings, you must additionally run `cmake .. && make` from the `demo/wrappers/build` directory.

The `demo/wrappers/CMakeLists.txt` does the following:

 * Define the `pybind_module` target
 * Add the `demo/wrappers/.cpp` files to the target
    * It is the binding module `pybind11_bindings.cpp` that is used, not `bindings.cpp`
 * Link to the archive `libdemo_fortran.a`
 * Link to `libgfortran.dylib`