#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

// declarations of some nested functions here:
void sign_correction(int side, int &i1, int &i2);

// end of declarations

void initialise(char **arr, int side, int init_infect){
    int i, j, k;
    
    // initially all are susceptible
    for(i=0; i<side; i++)
        for(j=0; j<side; j++)
            arr[i][j] = 's';
        
    // place the infected persons randomly
    for(k=0; k<init_infect; k++){
        // generate a random location in the world
        i = rand()%side;
        j = rand()%side;
        
        // make sure the location is not infected
        while(arr[i][j] == 'i'){
            i = rand()%side;
            j = rand()%side;
        }
        
        // now infect the location
        arr[i][j] = 'i';
    }
    
    return;
}

void pop_count(char **arr, int side, int &sus, int &inf, int &rec){
    /* def: 's' = sus
     * 'i' = inf
     * 'r' = rec */
    // initialise all counts to zero
    sus = 0;
    inf = 0;
    rec = 0;
    int p, q;
    
    for(p=0; p<side; p++){
        for(q=0; q<side; q++){
            if(arr[p][q] == 's')
                sus++;
            else if(arr[p][q] == 'i')
                inf++;
            else if(arr[p][q] == 'r')
                rec++;
        }
    }
    
    return;
}

void run_update(char **arr, int side, int neigh, float inf_prob, float rec_prob){
    int p, q, r, s, x, y;
    float rn;
    
    // making a current copy of arr for synchronous update
    char **curr;
    curr = (char **)malloc(sizeof(char *)*side);
    for(p=0; p<side; p++){
        curr[p] = (char *)malloc(sizeof(char)*side);
        for(q=0; q<side; q++)
            curr[p][q] = arr[p][q];
    }
    
    /* meat of the function: 
     * the update, by randomly infecting neighbours within the distance neigh */
    for(p=0; p<side; p++){
        for(q=0; q<side; q++){
            // recovery
            if(curr[p][q] == 'i'){
                rn = (float)rand()/RAND_MAX;
                if(rn < rec_prob)
                    arr[p][q] = 'r';
            }
            
            // interaction with neighbours and possible infection:            
            // finding the neighbours
            for(x=-neigh; x<=neigh; x++){
                for(y=-neigh; y<=neigh; y++){
                    // choosing by manhattan metric
                    if(abs(x)+abs(y) <= neigh){
                        r = p+x;
                        s = q+y;
                        // get the sign corrected neighbours by pbc
                        sign_correction(side, r, s);
                        // randomly infecting
                        if(curr[p][q] != 'r'){
                            rn = (float)rand()/RAND_MAX;
                            if(curr[p][q] == 'i' && curr[r][s] != 'r' && rn < inf_prob)
                                arr[r][s] = 'i';
                            else if(curr[p][q] == 's' && curr[r][s] == 'i' && rn < inf_prob)
                                arr[p][q] = 'i';
                        }
                    }
                }
            }
        }
    }
    return;
}

void sign_correction(int side, int &i1, int &i2){
    // correcting i1
    if(i1 < 0)
        i1 = (i1+side)%side;
    else if(i1 >= side)
        i1 = i1%side;
    
    // correcting i2
    if(i2 < 0)
        i2 = (i2+side)%side;
    else if(i2 >= side)
        i2 = i2%side;
    
    return;
}       
        
