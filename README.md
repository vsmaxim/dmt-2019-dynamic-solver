# dmt-2019-dynamic-solver

## About

Solver for first task written in C++ to increase dynamic programming solver speed.

## How to use?

Simply run `pip install git+https://github.com/vsmaxim/dmt-2019-dynamic-solver@master`

## Methods

There are only two methods available now in the module.  
`dynamic_solver.solve(initial_state: float) -> float` - returns optimal solution with defined initial_state  
`dynamic_solver.set_precision(new_precision: float) -> None` - sets new precision for global solver object  
`dynamic_solver.construct_plan(initial_state: float) -> List[float]` - returns optimal plan  
`dynamic_solver.get_cache() -> dict` - utility function to get cache from dynamic solver   
