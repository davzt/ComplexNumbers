#include "complexNum.h"

PyMethodDef cn_methods[] = {
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
    }, {NULL, NULL, 0, NULL}
//    {
//        "set",
//        set_cn,
//        METH_VARARGS,
//        "Set complex number"
//    }
};

PyTypeObject cn_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "complex_num",
    .tp_basicsize = sizeof(complex_num),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Complex number",
    .tp_methods = cn_methods,
};

complex_num* cn_init(double re, double im)
{
    complex_num* cn = PyObject_NEW(complex_num, &cn_Type);
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
    return cn;
}

complex_num* sum(complex_num cn1, complex_num cn2) {
    return cn_init(cn1.re + cn2.re, cn1.im + cn2.im);
}

complex_num* sub(complex_num cn1, complex_num cn2) {
    return cn_init(cn1.re - cn2.re, cn1.im - cn2.im);
}

complex_num* mul(complex_num cn1, complex_num cn2) {
    return cn_init(cn1.re * cn2.re - cn2.im * cn1.im, cn1.re * cn2.im + cn1.im * cn2.re);
}

complex_num* truediv(complex_num cn1, complex_num cn2) {
    if (cn2.re == 0 && cn2.im == 0) {
        printf("Деление на 0");
        return Py_None;
    } else return cn_init((cn1.re * cn2.re + cn1.im * cn2.im)
                          / (cn2.re * cn2.re + cn2.im * cn2.im),
                          (cn2.re * cn1.im - cn1.re * cn2.im) /
                          (cn2.re * cn2.re + cn2.im * cn2.im));
}

complex_num* z_pow(complex_num cn, double n) {
    double cc1, zero = 0;
    if (cn.re == 0 && cn.im == 0 && n == 0) return cn_init(1,0);
    if (n > 0 && modf(n, &cc1) == zero)
        return cn_init(cn.norm * cos(cn.angle * n), cn.norm * sin(cn.angle * n));
    else return Py_None;
}

PyObject *cln(PyObject *self) {
    complex_num* cn = (complex_num *)self;
    printf("%.2f + i * (%.2f + 2pi * n, n - целое)\n", log(cn->norm), cn->angle);
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *c_pow(PyObject *self1, PyObject *self2) {
    complex_num* cn1 = (complex_num *)self1;
    complex_num* cn2 = (complex_num *)self2;
    printf("e ^ ((%.2f + i * %.2f) * (%.2f + i * (%.2f + 2pi * n, n - целое))\n", cn2->re, cn2->im, log(cn1->norm), cn1->angle);
    Py_INCREF(Py_None);
    return Py_None;
}

complex_num* new_cn(PyObject *self)
{
    complex_num* cn = cn_init(0, 0);
    return cn;
}

PyObject *print_alg(PyObject* self)
{
    complex_num* cn = (complex_num *)self;
    printf("%.2f + i * %.2f\n", cn->re, cn->im);
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *print_trig(PyObject* self) {
    complex_num* cn = (complex_num *)self;
    printf("%.2f * (cos(%.2f) + i * sin(%.2f))\n", cn->norm, cn->angle, cn->angle);
    printf("or %.2f * (%.2f + i * %.2f)\n", cn->norm, cos(cn->angle), sin(cn->angle));
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *print_exp(PyObject* self) {
    complex_num* cn = (complex_num *)self;
    printf("%.2f * e ^ (i * %f.2)\n", cn->norm, cn->angle);
    Py_INCREF(Py_None);
    return Py_None;
}

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
        return cn_init(dux, dvx);
    }
    else return Py_None;
}
