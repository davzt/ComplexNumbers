#ifndef COMPLEXNUM_H
#define COMPLEXNUM_H
#define PY_SSIZE_T_CLEAN
#define _USE_MATH_DEFINES
#include <Python.h>
#include <time.h>
#include <math.h>

typedef struct
{
    PyObject_HEAD
    double re, im, angle, norm;
} complex_num;

PyMethodDef cn_methods[];
PyTypeObject cn_Type;
void init(double re, double im);
void clean(complex_num* self);
PyObject* create(PyObject* self, PyObject* args);
PyObject* re(PyObject* self);
PyObject* im(PyObject* self);
PyObject* norm(PyObject* self);
PyObject* angle(PyObject* self);
PyObject* sum(PyObject* cn1, PyObject* cn2);
PyObject* sub(PyObject* self, PyObject* args);
PyObject* mul(PyObject* self, PyObject* args);
PyObject* truediv(PyObject* self, PyObject* args);
PyObject* zPow(PyObject* self, PyObject* args);
PyObject *ln(PyObject *self, PyObject* args);
PyObject *cPow(PyObject *self, PyObject *args);
PyObject* outAlg(PyObject* self);
PyObject* outTrig(PyObject* self);
PyObject* outExp(PyObject* self);

#endif
