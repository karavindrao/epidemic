#include<iostream>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "epidemic.hpp"

// defining constants
#define TOT_POP 10000   // total population
#define CON_NUM 4     // number of contacts per time
#define TIME 1000     // duration of simulation
#define INF_PROB 0.1   // prob of infection
#define INF_FOUNDER 5   // initial # of infected persons
#define REC_PROB 0.01   // prob of recovery

int main(){            

    // set the seed of random number generator    
    srand(time(NULL));
    
    /* set up the population in a char array
     * 's' is susceptible
     * 'i' is infected 
     * 'r' is recovered */
    char ep_state[TOT_POP]={'x'};
    
    //int s[TIME], i[TIME], r[TIME];       // meanings as in SIR model
    int s, i, r;
    int c;          // index variable
    
    // initialise the population and infected individuals
    init_infect(ep_state, TOT_POP, INF_FOUNDER);        
   
    // run the update
    for(c=0; c<TIME; c++){
        run_update(ep_state, TOT_POP, CON_NUM, INF_PROB, REC_PROB);
        pop_count(ep_state, TOT_POP, s, i, r);        
        printf("%d\t%d\t%d\n", s, i, r);
    }
        
    return 0;
}
