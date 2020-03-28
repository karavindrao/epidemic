# epidemic repository
Agent based SIR model with increasing detail and complexity, written in c++ (it's all c-syntax except calling functions by reference variables, which is cool.)

Description of the folders:
## random
An agent is free to interact with any other agent in the population. Number of interactions per agent per unit time (a parameter that can be changed) is fixed, as is the total population. Track the number of susceptible (uninfected), infected, and recovered cases.

**random/epidemic_rand.cpp** has the main function

**random/epidemic_rand_fn.cpp** has the definitions of functions

**random/epidemic_rand.hpp** is the header file for functions defined in random/epidemic_rand_fn.cpp

## spatial
An agent interacts only with and all of its immediate neighbours in each time step. The range of interaction is a parameter. Total population is fixed. Track the number of susceptible (uninfected), infected, and recovered cases.

**spatial/epidemic_spat.cpp** has the main function

**spatial/epidemic_spat_fn.cpp** has the definitions of functions

**spatial/epidemic_spat.hpp** is the header file for functions defined in spatial/epidemic_spat_fn.cpp
