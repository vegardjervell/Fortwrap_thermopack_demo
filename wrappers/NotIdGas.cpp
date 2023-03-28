/* This source file automatically generated on 2023-03-28 using 
   FortWrap wrapper generator version 2.2.2 */

#include "NotIdGas.h"

// Constructor:
NotIdGas::NotIdGas(int ident, int nc, float Tc, float Vc) {
  data_ptr = NULL;
  allocate_notidgas_(&data_ptr); // Allocate Fortran derived type
  directeos__notidgas_ctor_sub_wrap(data_ptr, &ident, &nc, &Tc, &Vc); // Fortran Constructor
}

// Destructor:
NotIdGas::~NotIdGas() {
  deallocate_notidgas_(data_ptr); // Deallocate Fortran derived type
}

void NotIdGas::Fres(float T, float V, const std::vector<float>* n, float* Fres, float* Ft, float* Fv, std::vector<float>* Fn) {
  directeos__notidgas_fres_wrap(data_ptr, &T, &V, &(*n)[0], Fres, Ft, Fv, Fn ? &(*Fn)[0] : NULL);
}

