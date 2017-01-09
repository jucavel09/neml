#include "elasticity.h"

#include "pyhelp.h"
#include "nemlerror.h"

#include "pybind11/pybind11.h"
#include "pybind11/numpy.h"
#include "pybind11/stl.h"

namespace py = pybind11;

PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);

namespace neml {

PYBIND11_PLUGIN(elasticity) {
  py::module m("elasticity", "Models of elasticity.");

  py::class_<ShearModulus, std::shared_ptr<ShearModulus>>(m, "ShearModulus")
      .def(py::init<double>(), py::arg("mu"))
      .def(py::init<std::shared_ptr<Interpolate>>(), py::arg("mu"))
      .def("modulus", &ShearModulus::modulus, "Modulus as a function of temperature.")
      ;

  py::class_<BulkModulus, std::shared_ptr<BulkModulus>>(m, "BulkModulus")
      .def(py::init<double>(), py::arg("K"))
      .def(py::init<std::shared_ptr<Interpolate>>(), py::arg("K"))
      .def("modulus", &BulkModulus::modulus, "Modulus as a function of temperature.")
      ;

  py::class_<LinearElasticModel, std::shared_ptr<LinearElasticModel>>(m, "LinearElasticModel")
      .def("C",
           [](const LinearElasticModel & m, double T) -> py::array_t<double>
           {
            auto C = alloc_mat<double>(6,6);
            m.C(T, arr2ptr<double>(C));
            return C;
           }, "Return stiffness elasticity matrix.")

      .def("S",
           [](const LinearElasticModel & m, double T) -> py::array_t<double>
           {
            auto S = alloc_mat<double>(6,6);
            m.S(T, arr2ptr<double>(S));
            return S;
           }, "Return compliance elasticity matrix.")
      ;

  py::class_<IsotropicLinearElasticModel, std::shared_ptr<IsotropicLinearElasticModel>>(m, "IsotropicLinearElasticModel", py::base<LinearElasticModel>())
      .def(py::init<std::shared_ptr<ShearModulus>, std::shared_ptr<BulkModulus>>(),
           py::arg("shear"), py::arg("bulk"))
      ;

  return m.ptr();
}


}
