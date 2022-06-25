#ifndef COMPLEXNUM
#define COMPLEXNUM
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"
#include <time.h>
#include "math.h"

typedef struct
{
    PyObject_HEAD
    double re, im, angle, norm;
} complex_num;

PyMethodDef cn_methods[];
PyTypeObject cn_Type;
complex_num* cn_init(double re, double im);
complex_num* sum(complex_num cn1, complex_num cn2);
complex_num* sub(complex_num cn1, complex_num cn2);
complex_num* new_cn(PyObject* self);
PyObject *print_alg(PyObject* self);
PyObject *print_trig(PyObject* self);
#endif