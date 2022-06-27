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
        if (im > 0) cn->angle = 3.14 / 2;
        else cn->angle = 3 * 3.14 / 2;
    } else {
        if (re < 0) cn->angle = atan(im / re) + 3.14;
        else cn->angle = atan(im / re);
    }
    cn->norm = sqrt(re * re + im * im);
}

PyObject* create(PyObject* self, PyObject* args) {
    double re, im;
    if (!PyArg_ParseTuple(args, "dd", &re, &im)) return NULL;
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

PyObject* sum(PyObject* self, PyObject* args) {
    complex_num *c1, *c2;
    double im, re;
    if (!PyArg_ParseTuple(args, "O!O!", &cn_Type, &c1, &cn_Type, &c2)) return NULL;
    re = c1->re + c2->re;
    im = c1->im + c2->im;
    return create(self, Py_BuildValue("(dd)", re, im));
}


PyObject* sub(PyObject* self, PyObject* args) {
    complex_num *c1, *c2;
    double im, re;
    if (!PyArg_ParseTuple(args, "O!O!", &cn_Type, &c1, &cn_Type, &c2)) return NULL;
    re = c1->re - c2->re;
    im = c1->im - c2->im;
    return create(self, Py_BuildValue("(dd)", re, im));
}

PyObject* mul(PyObject* self, PyObject* args) {
    complex_num *c1, *c2;
    double im, re;
    if (!PyArg_ParseTuple(args, "O!O!", &cn_Type, &c1, &cn_Type, &c2)) return NULL;
    re = c1->re * c2->re - c2->im * c1->im;
    im = c1->re * c2->im + c1->im * c2->re;
    return create(self, Py_BuildValue("(dd)", re, im));
}

PyObject* truediv(PyObject* self, PyObject* args) {
    complex_num *c1, *c2;
    double im, re;
    if (!PyArg_ParseTuple(args, "O!O!", &cn_Type, &c1, &cn_Type, &c2)) return NULL;
    if (c2->re == 0 && c2->im == 0) {
        printf("Деление на 0");
        return Py_None;
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
    if (!PyArg_ParseTuple(args, "O!i", &cn_Type, &c, &n)) return NULL;
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
    if (!PyArg_ParseTuple(args, "O!", &cn_Type, &c)) return NULL;
    printf("%.2f + i * (%.2f + 2pi * n, n - целое)\n", log(c->norm), c->angle);
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject* cPow(PyObject *self, PyObject *args) {
    complex_num* c1, *c2;
    if (!PyArg_ParseTuple(args, "O!O!", &cn_Type, &c1, &cn_Type, &c2)) return NULL;
    printf("e ^ ((%.2f + i * %.2f) * (%.2f + i * (%.2f + 2pi * n, n - целое))\n", c2->re, c2->im, log(c1->norm),
    c1->angle);
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject* outAlg(PyObject* self) {
    complex_num* cn = (complex_num*)self;
    printf("%.2f + i * %.2f\n", cn->re, cn->im);
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject* outTrig(PyObject* self) {
    complex_num* cn = (complex_num *)self;
    printf("%.2f * (cos(%.2f) + i * sin(%.2f))\n", cn->norm, cn->angle, cn->angle);
    printf("or %.2f * (%.2f + i * %.2f)\n", cn->norm, cos(cn->angle), sin(cn->angle));
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject* outExp(PyObject* self) {
    complex_num* cn = (complex_num *)self;
    printf("%.2f * e ^ (i * %.2f)\n", cn->norm, cn->angle);
    Py_INCREF(Py_None);
    return Py_None;
}
/*
double diffx(double (*f)(double, double), double x, double y) {
    const double delta = 1.0e-6;
    return (f(x + delta, y) - f(x, y)) / delta;
}

double diffy(double (*f)(double, double), double x, double y) {
    const double delta = 1.0e-6;
    return (f(x, y + delta) - f(x, y)) / delta;
}

double u(x, y) {
    return x * x - 2 * y;
}

double v(x, y) {
    return y * y - 2 * y + x;
}

complex_num * complex_derivative (double (*u)(double, double), double (*v)(double, double), double x, double y) {
    double dux = diffx(u, x, y);
    double duy = diffy(u, x, y);
    double dvx = diffx(v, x, y);
    double dvy = diffy(v, x, y);
    if (dux == dvy && - dvx == duy) {
        return init(dux, dvx);
    }
    else return Py_None;
}
*/