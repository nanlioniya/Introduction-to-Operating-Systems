# include <pthread.h>
# include <iostream>
# include <stdio.h>
# include <thread>
# include <unistd.h>
using namespace std;

# define MAX 500

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX]; // Result of Addition
int matD[MAX][MAX]; // Result of Multiplication
long num_t = 2;// number of threads
//best 10

void *Addition(void *arg){
    // Addition -> matC
    long index = (long)arg;
    int from = (index*500)/num_t;
    int to = (index+1)*500/num_t;

    for (int i = from; i < to; i++) {
        for (int j = 0; j < MAX; j++){
            matC[i][j] = matA[i][j] + matB[i][j];
        }   
    }
    return NULL;
}
void *Multiplication(void *arg){
    // Multiplication -> matD
    long index = (long)arg;
    int from = (index*500)/num_t;
    int to = (index+1)*500/num_t;

    for (int i = from; i < to; i++) {
        for (int j = 0; j < MAX; j++) {
            matD[i][j] = 0;
            for (int k = 0; k < MAX; k++) {
                matD[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
    return NULL;
}



int main()
{
    //get input
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matA[i][j];
        }
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matB[i][j];
        }
    }


    // threads
    pthread_t tid[2];// number of threads
    // create threads
    for(long i=0; i<num_t; i++){
        pthread_create(&tid[i], NULL, Addition, (void*)i);
    }
    for(long j=0; j<num_t; j++){
        pthread_join(tid[j], NULL);
    }
    
    pthread_t tid_mul[2];
    for(long i=0; i<num_t; i++){
        pthread_create(&tid_mul[i], NULL, Multiplication, (void*)i);
    }
    for(long j=0; j<num_t; j++){
        pthread_join(tid_mul[j], NULL);
    }

    // calculate SUM of matC
    long long sum_C = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            sum_C +=  matC[i][j];     
    }
    cout << sum_C << endl;
    
    // calculate SUM of matD
    long long sum_D = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            sum_D += matD[i][j];
    }
    cout << sum_D << endl;

    return 0;
}