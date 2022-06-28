#include "main.h"


PyMethodDef own_methods[] = {
        {
                "CN",
                create,
                METH_VARARGS,
                "Creating complex number"
        },
        {
                "sum",
                sum,
                METH_VARARGS,
                "Sum"
        },
        {
                "sub",
                sub,
                METH_VARARGS,
                "Subtract"
        },
        {
                "mul",
                mul,
                METH_VARARGS,
                "Multiply"
        },
        {
                "truediv",
                truediv,
                METH_VARARGS,
                "True divide"
        },
        {
                "zPow",
                zPow,
                METH_VARARGS,
                "Integer pow of complex number"
        },
        {
                "cPow",
                cPow,
                METH_VARARGS,
                "Complex pow of complex number"
        },
        {
                "ln",
                ln,
                METH_VARARGS,
                "complex logarithm of complex number"
        },
        {
                "conjugate",
                conjugate,
                METH_VARARGS,
                "Conjugate"
        },
        {NULL, NULL, 0, NULL}
};

static PyModuleDef simple_module = {
        PyModuleDef_HEAD_INIT,
        "complex_numbers",
        "doc",
        -1,
        own_methods
};

PyMODINIT_FUNC PyInit_complex_numbers() {
    PyObject* module;

    cn_Type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&cn_Type) < 0) return NULL;
    module = PyModule_Create(&simple_module);

    if (module == NULL) return NULL;
    Py_INCREF(&cn_Type);

    return module;
}
