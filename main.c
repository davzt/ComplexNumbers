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
