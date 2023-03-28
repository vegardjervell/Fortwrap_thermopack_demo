/* This source file automatically generated on 2023-03-28 using 
   FortWrap wrapper generator version 2.2.2 */

#ifndef NOTIDGAS_H_
#define NOTIDGAS_H_

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif


#ifndef SWIG // Protect declarations from SWIG
#include <cstdlib>
#include <vector>
#include "InterfaceDefs.h"
#include "BaseEos.h"

extern "C" {
  void allocate_notidgas_(ADDRESS *caddr);
  void deallocate_notidgas_(ADDRESS caddr);
  void directeos__notidgas_ctor_sub_wrap(ADDRESS instance, int* ident, int* nc, float* Tc, float* Vc);
  void directeos__notidgas_fres_wrap(ADDRESS c_this, float* T, float* V, const float n[], float* Fres, float* Ft, float* Fv, float Fn[]);
}
#endif // SWIG

/**
 * \brief Not Ideal gas EoS
 */
class DLLEXPORT NotIdGas : public BaseEos {

public:
  NotIdGas(int ident, int nc, float Tc, float Vc);
  ~NotIdGas();

  /**
   * \brief Compute residual and derivatives for ideal gas
   */
  void Fres(float T, float V, const std::vector<float>* n, float* Fres, float* Ft=NULL, float* Fv=NULL, std::vector<float>* Fn=NULL);

};

#endif /* NOTIDGAS_H_ */
