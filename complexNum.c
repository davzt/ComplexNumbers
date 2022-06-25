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
    },
    {
        "set",
        set_cn,
        METH_VARARGS,
        "Set complex number"
    }
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
        if (im > 0) cn->angle = M_PI / 2;
        else cn->angle = 3 * M_PI / 2;
    } else {
        if (re < 0) cn->angle = atan(im/re) + M_PI;
        else cn->angle = atan(im/re);
    }
    cn->norm = sqrt(re*re + im*im);
    return cn;
}


complex_num* sum(complex_num cn1, complex_num cn2) {
    return cn_init(cn1.re+cn2.re, cn1.im+cn2.im);
}

complex_num* sub(complex_num cn1, complex_num cn2) {
    return cn_init(cn1.re-cn2.re, cn1.im-cn2.im);
}

complex_num* new_cn(PyObject *self)
{
    complex_num* cn = cn_init(0, 0);
    return cn;
}

PyObject *print_alg(PyObject* self)
{
    complex_num* cn = (complex_num *)self;
    printf("%.2f + i*%.2f", cn->re, cn->im);
    printf("\n");
    Py_INCREF(Py_None);
    return Py_None;
}

PyObject *print_trig(PyObject* self)
{
    complex_num* cn = (complex_num *)self;
    printf("%.2f*(cos(%.2f) + i*sin(%.2f))", cn->norm, cn->angle, cn->angle);
    printf("\n");
    Py_INCREF(Py_None);
    return Py_None;
}

