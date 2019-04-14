from distutils.core import setup, Extension, DEBUG

dynamic_solver_module = Extension('dynamic_solver', sources=['main.cpp'])

setup(
    name='dynamic_solver',
    version='1.0',
    description='Python package with fast dynamic solver included',
    ext_modules=[dynamic_solver_module],
)