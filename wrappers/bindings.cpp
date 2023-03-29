#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "NotIdGas.h"
#include "Variant1.h"
#include "Variant2.h"

#define Base_bindings(Model) \
            .def("Fres", &Model::Fres)\
            .def("Fideal", &Model::Fideal)\
            .def("pressure", &Model::pressure)

#define Variant_bindings(Model) \
            .def("internal_comp", &Model::internal_comp)

namespace py = pybind11;
PYBIND11_MODULE(libdummy, handle){
    handle.doc() = "Is this documentation? I have been told it is the best."

    py::class_<NotIdGas>(handle, "cpp_NotIdGas")
        .def(py::init<int, int, float, float>())
        Base_bindings(NotIdGas)

    py::class_<Variant1>(handle, "cpp_Variant1")
        .def(py::init<int, int, float, float, int>())
        Base_bindings(Variant1)
        Variant_bindings(Variant1)

    py::class_<Variant1>(handle, "cpp_Variant1")
        .def(py::init<int, int, float, float, int>())
        Base_bindings(Variant2)
        Variant_bindings(Variant2)
}