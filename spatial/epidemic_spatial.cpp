#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#include "epidemic_spatial.hpp"

#define SIDE_LEN 100    // side length of the world
#define NEIGH 1         // number of neighbours infection can spread
#define TIME 1000       // duration of the simulation
#define INF_FOUNDER 5   // initial # of infected persons
#define INF_PROB 0.1    // prob of infection
#define REC_PROB 0.01   // prob of recovery

int main(){
    // set the seed of random number generator    
    srand(time(NULL));
    
    int p, q;          // index variable
    
    /* set up the population in a char array
     * 's' is susceptible
     * 'i' is infected 
     * 'r' is recovered */
    char **ep_state;
    ep_state = (char **)malloc(sizeof(char *)*SIDE_LEN);
    for(p=0; p<SIDE_LEN; p++)
        ep_state[p] = (char *)malloc(sizeof(char)*SIDE_LEN);        
    
    int s, i, r;    // meanings as in SIR model
    
    
    // initialise the population and infected individuals
    initialise(ep_state, SIDE_LEN, INF_FOUNDER);
    
    // serial updates
    for(p=0; p<TIME; p++){
        run_update(ep_state, SIDE_LEN, NEIGH, INF_PROB, REC_PROB);
        pop_count(ep_state, SIDE_LEN, s, i, r);
        printf("%d\t%d\t%d\n", s, i, r);
    }        
    
    return 0;
}
