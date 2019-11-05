/* 
 * Name: Wang, Yanfang
 * Email: ywan168@lsu.edu
 * Project: PA-1 (Multithreading)
 * Instructor: Feng Chen
 * Class: cs4103-sp19
 * Login ID: cs410369
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
/*
 * 
 */
#define M 3
#define N 3
#define K 2
int A [M][K] = {{1,4}, {2,5}, {3,6}};
int B [K][N] = {{8,7,6}, {5,4,3}};
int C [M][N];
struct pos
{int i;
 int j;
};

void *runner(void *param); 

int main(int argc, char** argv) {

    pthread_t* thread;  // pointer to a group of threads
    int num_thread=M*N;
    thread = (pthread_t*) malloc(num_thread*sizeof(pthread_t));
    
    int i, j;
    for (i=0; i<M; i++){
        for (j=0; j<N; j++){ 
            // each element has each thread
            struct pos* position = (struct pos*) malloc(sizeof(struct pos));
            position->i = i;
            position->j = j;   
            /* create the thread */
            if(pthread_create(&thread[i*N+j], NULL, runner, position)){                
                 perror("Can't create thread");
                 free(thread);
                 free(position);
                 exit(-1);
            }
        }
    } 
    for (i = 1; i < num_thread; i++){
           pthread_join(thread[i], NULL);
    }
    /*print out the C matrix */
    
    for (i=0; i<M; i++){
        for(j=0; j<N; j++){
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
}

/* The thread will begin control in this function */
void *runner(void *param){
    struct pos* position = param;
    int n, sum = 0;
    for (n=0; n<K; n++){ 
        sum += A[position->i][n]*B[n][position->j];
    }
    C[position->i][position->j] = sum; 
    pthread_exit(0);
}


