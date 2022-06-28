#include "complexNum.h"

// available methods to "complex number" object
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

// cn_Type (type of "complex number" object) definition
PyTypeObject cn_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "complex_num",
    .tp_basicsize = sizeof(complex_num),
    .tp_dealloc = (destructor)clean,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Complex number",
    .tp_methods = cn_methods,
};

// method to free complex_num
void clean(complex_num* self){
    Py_XDECREF(self);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

// side function to init complex_num with real, im, angle, norm
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

// creating a complex number
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

// method returning real part of number
PyObject* re(PyObject* self) {
    complex_num* cn = (complex_num*)self;
    return Py_BuildValue("d", cn->re);
}

// method returning imaginary part of complex number
PyObject* im(PyObject* self) {
    complex_num* cn = (complex_num*)self;
    return Py_BuildValue("d", cn->im);
}

// method returning norm of complex number
PyObject* norm(PyObject* self) {
    complex_num* cn = (complex_num*)self;
    return Py_BuildValue("d", cn->norm);
}

// method returning angle of complex number
PyObject* angle(PyObject* self) {
    complex_num* cn = (complex_num*)self;
    return Py_BuildValue("d", cn->angle);
}

// method returning conjugate of complex number
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

//method returning sum of two complex numbers
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

// method returning subtract of two complex numbers
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

// method returning multiplication of two complex numbers
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

// method returning true division of two complex numbers
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

// method returning integer pow of complex number
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

// method returning complex logarithm of complex number with defining number of branch
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

// method returning complex pow of complex number
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

// method printing algebraic form of complex number
PyObject* outAlg(PyObject* self) {
    complex_num* cn = (complex_num*)self;
    printf("%.2f + i * %.2f\n", cn->re, cn->im);
    return Py_None;
}

// method printing trigonometric form of complex number
PyObject* outTrig(PyObject* self) {
    complex_num* cn = (complex_num *)self;
    printf("%.2f * (cos(%.2f) + i * sin(%.2f))\n", cn->norm, cn->angle, cn->angle);
    printf("or %.2f * (%.2f + i * %.2f)\n", cn->norm, cos(cn->angle), sin(cn->angle));
    return Py_None;
}

// method printing exponential form of complex number
PyObject* outExp(PyObject* self) {
    complex_num* cn = (complex_num *)self;
    printf("%.2f * e ^ (i * %.2f)\n", cn->norm, cn->angle);
    return Py_None;
}
