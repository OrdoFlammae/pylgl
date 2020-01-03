#ifndef PYLGL_SOLVER_H
#define PYLGL_SOLVER_H

#include <Python.h>

#include "lglib.h"

typedef struct {
  PyObject_HEAD;
  LGL *lgl;
} solver_object;

int solver_init(solver_object *self, PyObject *args, PyObject *kwds);
void solver_dealloc(solver_object *self);

PyObject *solver_str(solver_object *self);

PyObject *solver_solve(solver_object *self);

static PyMethodDef solver_methods[] = {
    {"solve", (PyCFunction)solver_solve, METH_NOARGS,
     PyDoc_STR("Solve the cnf")},
    {NULL} // Sentinel
};

static PyTypeObject solver_type = {
    PyVarObject_HEAD_INIT(NULL, 0)            // tp_head
    "solver",                                 // tp_name
    sizeof(solver_object),                    // tp_basicsize
    0,                                        // tp_itemsize
    (destructor)solver_dealloc,               // tp_dealloc
    0,                                        // tp_print
    0,                                        // tp_getattr
    0,                                        // tp_setattr
    0,                                        // tp_compare
    0,                                        // tp_repr
    0,                                        // tp_as_number
    0,                                        // tp_as_sequence
    0,                                        // tp_as_mapping
    0,                                        // tp_hash
    0,                                        // tp_call
    (reprfunc)solver_str,                     // tp_str
    0,                                        // tp_getattro
    0,                                        // tp_setattro
    0,                                        // tp_as_buffer
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, // tp_flags
    0,                                        // tp_doc
    0,                                        // tp_traverse
    0,                                        // tp_clear
    0,                                        // tp_richcompare
    0,                                        // tp_weaklistoffset
    0,                                        // tp_iter
    0,                                        // tp_iternext
    solver_methods,                           // tp_methods
    0,                                        // tp_members
    0,                                        // tp_getset
    0,                                        // tp_base
    0,                                        // tp_dict
    0,                                        // tp_descr_get
    0,                                        // tp_descr_set
    0,                                        // tp_dictoffset
    (initproc)solver_init,                    // tp_init
    0,                                        // tp_alloc
    PyType_GenericNew,                        // tp_new
};

#endif /* PYLGL_SOLVER_H */
