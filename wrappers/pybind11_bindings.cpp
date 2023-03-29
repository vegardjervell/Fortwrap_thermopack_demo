#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Variant2.h"
#include "NotIdGas.h"
#include "Variant1.h"


#define BaseEos_bindings(Model) \
    .def("Fideal", &Model::Fideal) \
    .def("pressure", &Model::pressure) \
    .def("set_Tc", &Model::set_Tc) \
    .def("Fres", &Model::Fres) 

#define VariantEoS_bindings(Model) \
    .def("variant_common_comp", &Model::variant_common_comp) \
    .def("internal_comp", &Model::internal_comp) 


namespace py = pybind11;
PYBIND11_MODULE(libdemo, handle){
    handle.doc() = "Is this documentation? I have been told it is the best.";

    py::class_<Variant2>(handle, "Variant2") 
        .def(py::init<int, int, float, float, int, float>(), py::arg("ident"), py::arg("nc"), py::arg("Tc"), py::arg("Vc"), py::arg("var1"), py::arg("var2")) 
        VariantEoS_bindings(Variant2) 
        BaseEos_bindings(Variant2); 

    py::class_<NotIdGas>(handle, "NotIdGas") 
        .def(py::init<int, int, float, float>(), py::arg("ident"), py::arg("nc"), py::arg("Tc"), py::arg("Vc")) 
        BaseEos_bindings(NotIdGas); 

    py::class_<Variant1>(handle, "Variant1") 
        .def(py::init<int, int, float, float, int, float>(), py::arg("ident"), py::arg("nc"), py::arg("Tc"), py::arg("Vc"), py::arg("var1"), py::arg("var2")) 
        VariantEoS_bindings(Variant1) 
        BaseEos_bindings(Variant1); 

}
