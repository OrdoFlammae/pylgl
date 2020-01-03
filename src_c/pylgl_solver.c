#include "pylgl_solver.h"

#include "lglib.h"
#include "pylgl.h"

int solver_init(solver_object *self, PyObject *args, PyObject *kwds) {
  self->lgl = setup_lgl(args, kwds);

  return 0;
}

void solver_dealloc(solver_object *self) { lglrelease(self->lgl); }

void lgl_trav_count(void *voidptr, int value) {
  int *count = voidptr;

  if (value == 0) {
    (*count)++;
  }
}

void lgl_trav_tostring(void *voidptr, int value) {
  PyObject **str = voidptr;
  PyObject *toConcat;

  if (value != 0) {
    toConcat = PyString_FromFormat("%i ", value);
  } else {
    toConcat = PyString_FromString("0\n");
  }

  PyString_ConcatAndDel(str, toConcat);
}

PyObject *solver_str(solver_object *self) {
  int count = 0;
  PyObject *result;
  PyObject *tmp;

  lglctrav(self->lgl, &count, lgl_trav_count);
  result = PyString_FromFormat("p cnf %i %i\n", lglmaxvar(self->lgl), count);
  PySys_WriteStdout("Still here!\n");

  tmp = PyString_FromString("");
  lglctrav(self->lgl, &tmp, lgl_trav_tostring);

  PyString_ConcatAndDel(&result, tmp);

  return result;
}

PyObject *solver_solve(solver_object *self) {
  PyObject *result = NULL;
  int rc;

  if (self->lgl == NULL) {
    return NULL;
  }

  Py_BEGIN_ALLOW_THREADS /* release GIL */
      rc = lglsat(self->lgl);
  Py_END_ALLOW_THREADS;

  switch (rc) {
  case LGL_SATISFIABLE:
    result = get_solution(self->lgl);
    break;
  case LGL_UNSATISFIABLE:
    result = PyUnicode_FromString("UNSAT");
    break;
  case LGL_UNKNOWN:
    result = PyUnicode_FromString("UNKNOWN");
    break;
  default:
    PyErr_Format(PyExc_SystemError, "picosat return value: %d", rc);
  }

  return result;
}
