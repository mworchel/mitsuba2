#include <mitsuba/python/python.h>
#include <mitsuba/core/bitmap.h>
#include <mitsuba/core/spectrum.h>
#include <mitsuba/core/transform.h>
#include <mitsuba/render/endpoint.h>
#include <mitsuba/render/medium.h>
#include <mitsuba/render/records.h>
#include <mitsuba/render/scene.h>
#include <mitsuba/render/shape.h>

MTS_PY_EXPORT_VARIANTS(Endpoint) {
    MTS_IMPORT_TYPES()
    MTS_IMPORT_OBJECT_TYPES()
    using EndpointP = mitsuba::Endpoint<FloatP, SpectrumP>;

    MTS_PY_CHECK_ALIAS(Endpoint, m) {
        MTS_PY_CLASS(Endpoint, Object)
            .def("sample_ray", vectorize<Float>(&EndpointP::sample_ray),
                "time"_a, "sample1"_a, "sample2"_a, "sample3"_a, "active"_a = true,
                D(Endpoint, sample_ray))
            .def("sample_direction", vectorize<Float>(&EndpointP::sample_direction),
                "it"_a, "sample"_a, "active"_a = true, D(Endpoint, sample_direction))
            .def("pdf_direction", vectorize<Float>(&EndpointP::pdf_direction),
                "it"_a, "ds"_a, "active"_a = true, D(Endpoint, pdf_direction))
            .def("eval", vectorize<Float>(&EndpointP::eval),
                "si"_a, "active"_a = true, D(Endpoint, eval))
            .def_method(Endpoint, world_transform)
            .def_method(Endpoint, needs_sample_2)
            .def_method(Endpoint, needs_sample_3)
            .def("shape", py::overload_cast<>(&Endpoint::shape, py::const_), D(Endpoint, shape))
            .def("medium", py::overload_cast<>(&Endpoint::medium, py::const_), D(Endpoint, medium))
            .def_method(Endpoint, set_shape, "shape"_a)
            .def_method(Endpoint, set_medium, "medium"_a)
            .def_method(Endpoint, bbox);
    }
}
