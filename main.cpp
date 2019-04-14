#include <iostream>
#include <unordered_map>
#include <Python.h>
#include "solver.h"


DynamicSolver Solver(3, 1);


PyObject *solve(PyObject *, PyObject *args) {
    double initialState;

    if (!PyArg_ParseTuple(args, "d", &initialState)) {
        return nullptr;
    }

    auto solution = Solver.solve(initialState).first;
    return PyFloat_FromDouble(solution);
}


PyObject *setPrecision(PyObject *, PyObject *args) {
    double newPrecision;

    if (!PyArg_ParseTuple(args, "d", &newPrecision)) {
        return nullptr;
    }

    Solver.setPrecision(newPrecision);
    return Py_None;
}


static PyMethodDef dynamic_solver_methods[] = {
        {"solve", (PyCFunction) solve, METH_VARARGS, "Dynamic solve with defined initial state"},
        {"set_precision", (PyCFunction)setPrecision, METH_VARARGS, "Set precision for dynamic solver"},
        {nullptr, nullptr, 0,                  nullptr},
};


static PyModuleDef dynamic_solver_module = {
        PyModuleDef_HEAD_INIT,
        "dynamic_solver",
        "Provides fast dynamic solver for python 3.7",
        0,
        dynamic_solver_methods,
};


PyMODINIT_FUNC PyInit_dynamic_solver() {
    return PyModule_Create(&dynamic_solver_module);
}

int main() {
    return 0;
}