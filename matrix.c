#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define MAX 3

int matA[MAX][MAX]; 
int matB[MAX][MAX]; 

int matSumResult[MAX][MAX];
int matDiffResult[MAX][MAX]; 
int matProductResult[MAX][MAX]; 



//Will be used for my operations array.
typedef void*(*Operators)(void*);

void fillMatrix(int matrix[MAX][MAX]) {
    for(int i = 0; i<MAX; i++) {
        for(int j = 0; j<MAX; j++) {
            matrix[i][j] = rand()%10+1;
        }
    }
}

void printMatrix(int matrix[MAX][MAX]) {
    for(int i = 0; i<MAX; i++) {
        for(int j = 0; j<MAX; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the sum of the
// values at the coordinates of matA and matB.
void* computeSum(void* args) { // pass in the number of the ith thread
   int *index = (int*) args;
   int x = (*index)/MAX;
   int y = (*index)%MAX;
   
  
   matSumResult[x][y] = matA[x][y] +matB[x][y];
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the difference of the
// values at the coordinates of matA and matB.
void* computeDiff(void* args) { // pass in the number of the ith thread
  int *index = (int*) args;
  int x = (*index)/MAX;
  int y = (*index)%MAX;
  
  matDiffResult[x][y] = matA[x][y] - matB[x][y];
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the inner product
// of matA and matB.
void* computeProduct(void* args) { // pass in the number of the ith thread
  int *index = (int*)args;
  int x = (*index)/MAX;
  int y = (*index)%MAX;
  
  for(int i = 0; i<MAX; i++){
    matProductResult[x][y] += matA[x][i] * matB[i][y];
  }

}

// Spawn a thread to fill each cell in each result matrix.
// How many threads will you spawn?
int main(int argc, char *argv[]) {
    //int max;
    srand(time(0));  // Do Not Remove. Just ignore and continue below.
    
    // 0. Get the matrix size from the command line and assign it to MAX
    //printf("Enter a matrix size.\n");
    //canf("%d",&max);
    //MAX = max;
    // 1. Fill the matrices (matA and matB) with random values.
    fillMatrix(matA);
    fillMatrix(matB);
    
    // 2. Print the initial matrices.
    printf("Matrix A:\n");
    printMatrix(matA);
    printf("Matrix B:\n");
    printMatrix(matB);
    
    // 3. Create pthread_t objects for our threads.
    pthread_t objects[3][MAX*MAX];
    
    // 4. Create a thread for each cell of each matrix operation.
    // 
    // You'll need to pass in the coordinates of the cell you want the thread
    // to compute.
    // 
    // One way to do this is to malloc memory for the thread number i, populate the coordinates
    // into that space, and pass that address to the thread. The thread will use that number to calcuate 
    // its portion of the matrix. The thread will then have to free that space when it's done with what's in that memory.
    
    Operators ops[3];
    ops[0] = &computeProduct;
    ops[1] = &computeDiff;
    ops[2] = &computeSum;
  
    for(int i = 0; i<3; i++){
      for (int j = 0; j< MAX*MAX; j++){
       int *index = (int*)malloc(sizeof(int));
       int *op_type = (int*)malloc(sizeof(int));
       *op_type =i;
       *index = j;
        
        pthread_create(&objects[*op_type][*index], NULL, ops[*op_type], (void*)index);
      }
    }
    // 5. Wait for all threads to finish.
    
  for(int i = 0; i<3; i++){
    for(int j = 0; j< MAX*MAX; j++){
      pthread_join(objects[i][j],NULL);    }
  }
    // 6. Print the results.
    printf("Results:\n");
    printf("Sum:\n");
    printMatrix(matSumResult);
    printf("Difference:\n");
    printMatrix(matDiffResult);
    printf("Product:\n");
    printMatrix(matProductResult);
    return 0;
  
}