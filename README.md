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

Some changes have been made to FortWrap in order to make the wrapping work, as of now the fork found here can automatically wrap this test case without issues.

Moving forward: 
* Implement internal computations that are not wrapped, to ensure that it is possible to make a minimal wrapper.
* Use `pybind11` to expose the C++ interface and implement python wrapper.