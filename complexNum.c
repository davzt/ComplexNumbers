#include "complexNum.h"

static PyMethodDef cn_methods[] = {
    {
        "outAlg",
        outAlg,
        METH_VARARGS,
        "Print complex number in algebraic form"
    },
    {
        "outTrig",
        outTrig,
        METH_VARARGS,
        "Print complex number in trigonometrical form"
    },
    {
        "outExp",
        outExp,
        METH_VARARGS,
        "Print complex number in exponential form"
    },
    {
        "re",
        re,
        METH_VARARGS,
        "Real part of complex number"
    },
    {
        "im",
        im,
        METH_VARARGS,
        "Image complex number"
    },
    {
        "norm",
        norm,
        METH_VARARGS,
        "Norm of complex number"
    },
    {
        "angle",
        angle,
        METH_VARARGS,
        "Angle of complex number"
    },
    {NULL, NULL, 0, NULL}
};

PyTypeObject cn_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "complex_num",
    .tp_basicsize = sizeof(complex_num),
    .tp_dealloc = (destructor)clean,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Complex number",
    .tp_methods = cn_methods,
};

void clean(complex_num* self){
    Py_XDECREF(self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

void init(complex_num* cn, double re, double im) {
    cn->re = re;
    cn->im = im;
    if (re == 0) {
        if (im > 0) cn->angle = PI / 2;
        else cn->angle = 3 * PI / 2;
    } else {
        if (re < 0) cn->angle = atan(im / re) + PI;
        else cn->angle = atan(im / re);
    }
    cn->norm = sqrt(re * re + im * im);
}

PyObject* create(PyObject* self, PyObject* args) {
    double re, im;
    if (!PyArg_ParseTuple(args, "dd", &re, &im)) {
    PyErr_SetString(PyExc_TypeError, "PARAMETERS MUST BE DOUBLE");
    return NULL;
    }
    complex_num* cn = PyObject_NEW(complex_num, &cn_Type);
    init(cn, re, im);
    return (PyObject*)cn;
}

PyObject* re(PyObject* self) {
    complex_num* cn = (complex_num*)self;
    return Py_BuildValue("d", cn->re);
}

PyObject* im(PyObject* self) {
    complex_num* cn = (complex_num*)self;
    return Py_BuildValue("d", cn->im);
}

PyObject* norm(PyObject* self) {
    complex_num* cn = (complex_num*)self;
    return Py_BuildValue("d", cn->norm);
}

PyObject* angle(PyObject* self) {
    complex_num* cn = (complex_num*)self;
    return Py_BuildValue("d", cn->angle);
}

PyObject* conjugate(PyObject* self, PyObject* args) {
    complex_num *c;
    double re, im;
    if (!PyArg_ParseTuple(args, "O!", &cn_Type, &c)) {
        PyErr_SetString(PyExc_TypeError, "PARAMETER MUST BE COMPLEX_NUM");
        return NULL;
    }
    re = c->re;
    im = - c->im;
    return create(self, Py_BuildValue("(dd)", re, im));
}

PyObject* sum(PyObject* self, PyObject* args) {
    complex_num *c1, *c2;
    double im, re;
    if (!PyArg_ParseTuple(args, "O!O!", &cn_Type, &c1, &cn_Type, &c2)) {
        PyErr_SetString(PyExc_TypeError, "PARAMETERS MUST BE COMPLEX_NUM");
        return NULL;
    }
    re = c1->re + c2->re;
    im = c1->im + c2->im;
    return create(self, Py_BuildValue("(dd)", re, im));
}


PyObject* sub(PyObject* self, PyObject* args) {
    complex_num *c1, *c2;
    double im, re;
    if (!PyArg_ParseTuple(args, "O!O!", &cn_Type, &c1, &cn_Type, &c2)) {
         PyErr_SetString(PyExc_TypeError, "PARAMETERS MUST BE COMPLEX_NUM");
         return NULL;
    }
    re = c1->re - c2->re;
    im = c1->im - c2->im;
    return create(self, Py_BuildValue("(dd)", re, im));
}

PyObject* mul(PyObject* self, PyObject* args) {
    complex_num *c1, *c2;
    double im, re;
    if (!PyArg_ParseTuple(args, "O!O!", &cn_Type, &c1, &cn_Type, &c2)) {
         PyErr_SetString(PyExc_TypeError, "PARAMETERS MUST BE COMPLEX_NUM");
         return NULL;
    }
    re = c1->re * c2->re - c2->im * c1->im;
    im = c1->re * c2->im + c1->im * c2->re;
    return create(self, Py_BuildValue("(dd)", re, im));
}

PyObject* truediv(PyObject* self, PyObject* args) {
    complex_num *c1, *c2;
    double im, re;
    if (!PyArg_ParseTuple(args, "O!O!", &cn_Type, &c1, &cn_Type, &c2)) {
         PyErr_SetString(PyExc_TypeError, "PARAMETERS MUST BE COMPLEX_NUM");
         return NULL;
    }
    if (c2->re == 0 && c2->im == 0) {
        PyErr_SetString(PyExc_ValueError, "DIVISION BY ZERO");
        return NULL;
    } else {
        re = (c1->re * c2->re + c1->im * c2->im) / (c2->re * c2->re + c2->im * c2->im);
        im = (c2->re * c1->im - c1->re * c2->im) / (c2->re * c2->re + c2->im * c2->im);
    }
    return create(self, Py_BuildValue("(dd)", re, im));
}

PyObject* zPow(PyObject* self, PyObject* args) {
    complex_num* c;
    double re, im;
    int n;
    if (!PyArg_ParseTuple(args, "O!i", &cn_Type, &c, &n)) {
         PyErr_SetString(PyExc_TypeError, "PARAMETERS MUST BE COMPLEX_NUM AND INTEGER");
         return NULL;
    }
    if (c->re == 0 && c->im == 0 && n == 0) {
        re = 0;
        im = 0;
        return create(self, Py_BuildValue("(dd)", re, im));
    }
    if (n > 0) {
        re = pow(c->norm, n) * cos(c->angle * n);
        im = pow(c->norm, n) * sin(c->angle * n);
        return create(self, Py_BuildValue("(dd)", re, im));
    }
    else return Py_None;
}

PyObject* ln(PyObject *self, PyObject* args) {
    complex_num* c;
    int n;
    double im, re;
    if (!PyArg_ParseTuple(args, "O!i", &cn_Type, &c, &n)) {
         PyErr_SetString(PyExc_TypeError, "PARAMETER MUST BE COMPLEX_NUM AND THE NUMBER OF THE LOGARITHM'S BRANCH MUST BE INTEGER");
         return NULL;
    }
    if (c->norm != 0) {
        re = log(c->norm);
        im = c->angle + 2 * PI * n;
        printf("%.2f + i * (%.2f + 2pi * n, n - integer)\n", log(c->norm), c->angle);
        return create(self, Py_BuildValue("(dd)", re, im));
    }
    else {
        PyErr_SetString(PyExc_ValueError, "ln(0) IS NOT DEFINED");
        return NULL;
    }
}

PyObject* cPow(PyObject *self, PyObject *args) {
    complex_num* c1, *c2;
    double re, im;
    if (!PyArg_ParseTuple(args, "O!O!", &cn_Type, &c1, &cn_Type, &c2)) {
         PyErr_SetString(PyExc_TypeError, "PARAMETERS MUST BE COMPLEX_NUM AND THE NUMBER OF THE LOGARITHM'S BRANCH MUST BE INTEGER");
         return NULL;
    }
    if (c1->norm != 0) {
        printf("e ^ ((%.2f + i * %.2f) * (%.2f + i * (%.2f + 2pi * n, n - integer))\n", c2->re, c2->im, log(c1->norm),
        c1->angle);
        return Py_None;
    }
    else {
        if (c2->norm == 0) {
            printf("1");
            return Py_None;
        }
        PyErr_SetString(PyExc_ValueError, "ln(0) IS NOT DEFINED");
        return NULL;
    }
}

PyObject* outAlg(PyObject* self) {
    complex_num* cn = (complex_num*)self;
    printf("%.2f + i * %.2f\n", cn->re, cn->im);
    return Py_None;
}

PyObject* outTrig(PyObject* self) {
    complex_num* cn = (complex_num *)self;
    printf("%.2f * (cos(%.2f) + i * sin(%.2f))\n", cn->norm, cn->angle, cn->angle);
    printf("or %.2f * (%.2f + i * %.2f)\n", cn->norm, cos(cn->angle), sin(cn->angle));
    return Py_None;
}

PyObject* outExp(PyObject* self) {
    complex_num* cn = (complex_num *)self;
    printf("%.2f * e ^ (i * %.2f)\n", cn->norm, cn->angle);
    return Py_None;
}
