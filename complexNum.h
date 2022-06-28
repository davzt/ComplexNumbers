#ifndef COMPLEXNUM_H
#define COMPLEXNUM_H
#define PY_SSIZE_T_CLEAN
#define PI 3.14159265
#define E 2.718281828
#include <Python.h>
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
PyObject* conjugate(PyObject* self, PyObject* args);
PyObject* sum(PyObject* self, PyObject* args);
PyObject* sub(PyObject* self, PyObject* args);
PyObject* mul(PyObject* self, PyObject* args);
PyObject* truediv(PyObject* self, PyObject* args);
PyObject* zPow(PyObject* self, PyObject* args);
PyObject* ln(PyObject *self, PyObject* args);
PyObject* cPow(PyObject *self, PyObject *args);
PyObject* outAlg(PyObject* self);
PyObject* outTrig(PyObject* self);
PyObject* outExp(PyObject* self);

#endif
