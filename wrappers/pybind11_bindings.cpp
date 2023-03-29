#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <iostream>
#include "Variant2.h"
#include "NotIdGas.h"
#include "Variant1.h"

template <class T> class dumb_ptr{
    private:
        T* ptr;
    public:
        dumb_ptr() : ptr(nullptr) {}
        dumb_ptr(T* ptr) : ptr(ptr) {}
        dumb_ptr(const dumb_ptr& other) : ptr(other.ptr) {}
        T& operator* () const { return *ptr; }
        T* operator->() const { return ptr; }
        operator T() const { return *ptr; }
        T* get() const { return ptr; }
        void destroy() { delete ptr; }
        T& operator[](std::size_t idx) const { return ptr[idx]; }
};

PYBIND11_DECLARE_HOLDER_TYPE(T, dumb_ptr<T>)

#define BaseEos_bindings(Model) \
    .def("Fideal", &Model::Fideal) \
    .def("pressure", [](Model& m, float T, float V, const std::vector<float>* n, py::array_t<float> p_arr){\
                           auto p = p_arr.mutable_unchecked<1>(); \
                           m.pressure(T, V, n, p.mutable_data(0)); \
                           std::cout << "Before return, pressure is " << *p.data(0) << std::endl; \
                           }, py::arg("T"), py::arg("V"), py::arg("n"), py::arg("p").noconvert()) \
    .def("set_Tc", &Model::set_Tc) \
    .def("Fres", &Model::Fres) 

#define VariantEoS_bindings(Model) \
    .def("variant_common_comp", &Model::variant_common_comp) \
    .def("internal_comp", &Model::internal_comp) 

// [](Model &m, float T, float V, const std::vector<float>* n, std::vector<float> p){m.pressure(T, V, n, &p[0]); }
//
void increment_value(float* val){
    (*val)++;
}

namespace py = pybind11;
PYBIND11_MODULE(libdemo, handle){
    handle.doc() = "Is this documentation? I have been told it is the best.";

    // py::class_<Variant2>(handle, "Variant2")
    //     .def(py::init<int, int, float, float, int, float>(), py::arg("ident"), py::arg("nc"), py::arg("Tc"), py::arg("Vc"), py::arg("var1"), py::arg("var2"))
    //     VariantEoS_bindings(Variant2)
    //     BaseEos_bindings(Variant2);

    py::class_<NotIdGas>(handle, "NotIdGas")
        .def(py::init<int, int, float, float>(), py::arg("ident"), py::arg("nc"), py::arg("Tc"), py::arg("Vc")) 
        BaseEos_bindings(NotIdGas); 

    // py::class_<Variant1>(handle, "Variant1")
    //     .def(py::init<int, int, float, float, int, float>(), py::arg("ident"), py::arg("nc"), py::arg("Tc"), py::arg("Vc"), py::arg("var1"), py::arg("var2"))
    //     VariantEoS_bindings(Variant1)
    //     BaseEos_bindings(Variant1);

}
