#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Barrier{
    sem_t mutex;
    sem_t barrier;
    int counter;
    int limit;
} Barrier;

typedef struct Shared{
    int *arr;
    int arrSize;
    Barrier barrier;
    bool doneFlag;
} Shared;

typedef struct ThreadID{
    int index;
    int swapCounter;
    Shared *shared;
} ThreadID;

void join_barrier(ThreadID *thID){
    Barrier *b = &thID->shared->barrier;
    sem_wait(&b->mutex);
    b->counter++;
    sem_post(&b->mutex);
    if(b->counter == b->limit){
        sem_post(&b->barrier);
    }
    sem_wait(&b->barrier);
    sem_wait(&b->mutex);
    b->counter--;
    if(b->counter > 0)
        sem_post(&b->barrier);
    sem_post(&b->mutex);
}

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void *phase(void *args){
    ThreadID *thID = (ThreadID *)args;
    int *arr = thID->shared->arr;
    thID->swapCounter = 0;
    if(thID->index + 2 < thID->shared->arrSize){
        if(arr[thID->index + 1] > arr[thID->index + 2]){
            swap(&arr[thID->index + 1], &arr[thID->index + 2]);
            thID->swapCounter ++;
        }
    }
    join_barrier(thID);
    if(arr[thID->index] > arr[thID->index + 1]){
        swap(&arr[thID->index], &arr[thID->index + 1]);
        thID->swapCounter++;
    }
    pthread_exit(NULL);
}

int main(){
    Shared sha;
    sha.doneFlag = false;
    sem_init(&sha.barrier.mutex, 1, 1);
    sem_init(&sha.barrier.barrier, 1, 0);
    sha.barrier.counter = 0;
    printf("Enter size of the array: ");
    scanf("%d", &sha.arrSize);
    int threadsCount = sha.arrSize/2;
    sha.barrier.limit = threadsCount;
    
    sha.arr = (int *)malloc(sizeof(int *) * sha.arrSize);
    int i;
    
    for(i = 0; i < sha.arrSize; i++){
        printf("Enter element: ");
        scanf("%d", &sha.arr[i]);
    }
    
    ThreadID ids[threadsCount];
    for(i = 0; i < threadsCount; i++){
        ids[i].index = i*2;
        ids[i].shared = &sha;
    }
    
    pthread_t workers[threadsCount];
    
    while(!sha.doneFlag){
        int totalSwap = 0;
        for(i = 0; i < threadsCount; i++){
            if(pthread_create(&workers[i], 0, phase, &ids[i]) == -1){
                printf("pthread_create %d error\n", i);
                exit(EXIT_FAILURE);
            }
        }
        for(i = 0; i< threadsCount; i++)
            pthread_join(workers[i], NULL);
        for(i = 0; i < threadsCount; i++)
            totalSwap += ids[i].swapCounter;
        if(!totalSwap){
            printf("DONE!\n");
            sha.doneFlag = true;
        }
    }
    
    for(i = 0; i < sha.arrSize; i++)
        printf("%d, ", sha.arr[i]);
    printf("\n");
    
    exit(EXIT_SUCCESS);
}
