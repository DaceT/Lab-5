 // #include <stdio.h>
 #include <pthread.h>
 #include <stdlib.h>
 #include <time.h>
 #include <unistd.h>

 #define SIZE 5

 int array[SIZE];
 int mid;
 pthread tids[4];

 void fillArrayWithRandomNumbers(int arr[SIZE]) {
     for(int i = 0; i<SIZE; i++) array[i] = rand()%100;
 }

 void printArray(int arr[SIZE]) {
     for(int i = 0; i<SIZE; i++) printf("%5d", arr[i]);
     printf("\n");
 }

 typedef struct StartEndIndexes {
     int start;
     int end;
 } StartEndIndexes;

 // Runs mergesort on the array segment described in the
 // argument. Spawns two threads to mergesort each half
 // of the array segment, and then merges the results.
 void* mergeSort(void* args) {
     mid = siz_arr.size()%2
    
     pthread_create(&tids[1], NULL, &mergeSort, (void *)StartEndIndexes)
        
    
    
     return NULL;
 }

 int main() {
     srand(time(0));
     StartEndIndexes sei;
     sei.start = 0; //s
     sei.end = SIZE - 1; //e
    
     // 1. Fill array with random numbers.
     fillArrayWithRandomNumbers(array);
    
     // 2. Print the array.
     printf("Unsorted array: ");
     printArray(array);
    
    
     // 3. Create a thread for merge sort.  
     // 
     StartEndIndexes->start = 0;
     StartEndIndexes->end = sizeOf[array];
    
     pthread_create(&tids[0], NULL, &mergeSort, (void *)StartEndIndexes)
        
    
    
    
 //     int array[SIZE];
 //     int mid;
 //     pthread tids[4];
    
     // YOU CAN DO THIS
    
    
    
     // 4. Wait for mergesort to finish.
     pthread_join(tid,NULL)
     // 5. Print the sorted array.
     printf("Sorted array:   ");
     printArray(array);
 }