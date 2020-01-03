#ifndef PYLGL_H
#define PYLGL_H

#include <Python.h>

#include "lglib.h"

LGL *setup_lgl(PyObject *args, PyObject *kwds);
PyObject *get_solution(LGL *lgl);

#endif /* PYLGL_H */
