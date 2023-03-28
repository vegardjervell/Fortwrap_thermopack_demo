/* This source file automatically generated on 2023-03-28 using 
   FortWrap wrapper generator version 2.2.2 */

#include "BaseEos.h"

void BaseEos::Fideal(float T, float V, const std::vector<float>* n, float* Fid, float* Ft, float* Fv, std::vector<float>* Fn) {
  base_eos__fideal_wrap(data_ptr, &T, &V, &(*n)[0], Fid, Ft, Fv, Fn ? &(*Fn)[0] : NULL);
}

void BaseEos::pressure(float T, float V, const std::vector<float>* n, float* p) {
  base_eos__pressure_wrap(data_ptr, &T, &V, &(*n)[0], p);
}

void BaseEos::set_Tc(float Tc) {
  base_eos__set_tc_wrap(data_ptr, &Tc);
}

