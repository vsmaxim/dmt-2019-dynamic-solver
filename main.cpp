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


PyObject *constructPlan(PyObject *, PyObject *args) {
    double initialState;

    if (!PyArg_ParseTuple(args, "d", &initialState)) {
        return nullptr;
    }

    auto plan = Solver.constructPlan(initialState);

    auto result = PyList_New(plan.size());
    for (size_t i = 0; i < plan.size(); ++i) {
        auto pythonValue = PyFloat_FromDouble(plan[i]);
        PyList_SetItem(result, i, pythonValue);
    }

    return result;
}


PyObject *getCache(PyObject *, PyObject *args) {
    auto cache = Solver.getCache();
    PyObject * dict = PyDict_New();

    for (int stage = 0; stage < cache.size(); stage++) {
        for ( const auto &[state, value] : cache[stage]) {
            PyObject * dictKey = Py_BuildValue("id", stage, state);
            PyObject * dictValue = Py_BuildValue("dd", value.first, value.second);
            PyDict_SetItem(dict, dictKey, dictValue);
        }
    }

    return dict;
}


static PyMethodDef dynamic_solver_methods[] = {
        {"solve", (PyCFunction) solve, METH_VARARGS, "Dynamic solve with defined initial state"},
        {"set_precision", (PyCFunction)setPrecision, METH_VARARGS, "Set precision for dynamic solver"},
        {"construct_plan", (PyCFunction)constructPlan, METH_VARARGS, "Construct plan from dynamic solver's cache"},
        {"get_cache", (PyCFunction)getCache, METH_VARARGS, "Get cache from dynamic solver"},
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