#include "main.h"


PyMethodDef own_methods[] = {
        {
                "print_alg",
                print_alg,
                METH_VARARGS,
                "Print complex number in algebraic form"
        },
        {
                "print_trig",
                print_trig,
                METH_VARARGS,
                "Print complex number in trigonometrical form"
        },
        {
        "cn_init", cn_init, METH_VARARGS, "Init complex number"
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
    PyObject* mod;
    cn_Type.tp_new = PyType_GenericNew;
    if(PyType_Ready(&cn_Type) < 0) return NULL;
    mod = PyModule_Create(&simple_module);
    if (mod == NULL) return NULL;
    Py_INCREF(&cn_Type);
    return mod;
}
