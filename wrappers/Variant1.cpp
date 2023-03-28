/* This source file automatically generated on 2023-03-28 using 
   FortWrap wrapper generator version 2.2.2 */

#include "Variant1.h"

// Constructor:
Variant1::Variant1(int ident, int nc, float Tc, float Vc, int var1, float var2) {
  data_ptr = NULL;
  allocate_variant1_(&data_ptr); // Allocate Fortran derived type
  variants__variant1_ctor_sub_wrap(data_ptr, &ident, &nc, &Tc, &Vc, &var1, &var2); // Fortran Constructor
}

// Destructor:
Variant1::~Variant1() {
  deallocate_variant1_(data_ptr); // Deallocate Fortran derived type
}

void Variant1::internal_comp(float T, float V, const std::vector<float>* n, float* computed) {
  variants__variant1_internal_comp_wrap(data_ptr, &T, &V, &(*n)[0], computed);
}

void Variant1::Fres(float T, float V, const std::vector<float>* n, float* Fres, float* Ft, float* Fv, std::vector<float>* Fn) {
  variants__variant1_fres_wrap(data_ptr, &T, &V, &(*n)[0], Fres, Ft, Fv, Fn ? &(*Fn)[0] : NULL);
}

