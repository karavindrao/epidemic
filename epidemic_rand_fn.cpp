#include<iostream>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void init_infect(char *arr, int tot_pop, int init_inf){
    int i, j;
    
    // initially everyone is susceptible
    for(i=0; i<tot_pop; i++){
        arr[i] = 's';
    }
    
    // randomly pick init_inf # of infected people
    for(i=0; i<init_inf; i++){
        
        j = rand()%tot_pop;
        
        // make sure arr[j] = 's'
        while(arr[j] != 's'){
            j = rand()%tot_pop;
        }
        
        // found an uninfected person
        arr[j] = 'i';
    }
    
    return;
}

void pop_count(char *arr, int size, int &sus, int &inf, int &rec){
    sus = 0;
    inf = 0;
    rec = 0;
    for(int i=0; i<size; i++){
        if(arr[i] == 's')
            sus++;
        else if(arr[i] == 'i')
            inf++;
        else if(arr[i] == 'r')
            rec++;
    }
    return;
}

void run_update(char *arr, int size, int cont, float inf_prob, float rec_prob){
    int cont_num[size] = {0};   // keeping count of # contacts of each person
    int i, j;
    float p;    // 0 <= p < 1. (randomly infecting)
    char curr[size]={'x'};  // current state of the population before updating
    
    // copying the state as I'm doing synchronous update
    for(i=0; i<size; i++)
        curr[i] = arr[i];
    
    // meat of the function: making random contacts and randomly infecting
    
    for(i=0; i<size; i++){
        // chance of recovery
        if(arr[i] == 'i'){
            p = (float)rand()/RAND_MAX;
            if(p < rec_prob)
                arr[i] = 'r';
        }
            
        /* infection: continue to i++ if i already had cont # of contacts */        
        if(cont_num[i] < cont){            
            // get a j, distinct from i, and which had < cont # of contacts so far
            j = rand()%size;
            while(cont_num[j] >= cont || j == i)
                j = rand()%size;
            
            // update the number of contacts
            cont_num[i]++;
            cont_num[j]++;
            
            /* randomly infect if not recovered.
             * of all possible interactions, these ones change the arr */
            if(curr[i] != 'r'){
                p = (float)rand()/RAND_MAX;
                if(curr[i] == 'i' && curr[j] != 'r' && p < inf_prob)
                    arr[j] = 'i';
                else if(curr[i] == 's' && curr[j] == 'i' && p < inf_prob)
                    arr[i] = 'i';
            }            
        }
    }
    return;
}            
