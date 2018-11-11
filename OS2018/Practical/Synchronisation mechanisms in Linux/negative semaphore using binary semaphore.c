#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct NegativeSemaphore{
    int value;
    int wake;
    sem_t mutex;
    sem_t delay;
} NegativeSemaphore;

void OUR_DOWN();

void OUR_UP();

void *thread_function(void *args);

NegativeSemaphore S;

int main(){
    S.value = 2;
    S.wake = 0;
    sem_init(&S.mutex, 1, 1);
    sem_init(&S.delay, 1, 0);
    
    char nameA = 'A', nameB = 'B', nameC = 'C', nameD = 'D', nameE = 'E';
    pthread_t a, b, c, d, e;
    pthread_create(&a, 0, thread_function, &nameA);
    pthread_create(&b, 0, thread_function, &nameB);
    pthread_create(&c, 0, thread_function, &nameC);
    pthread_create(&d, 0, thread_function, &nameD);
    pthread_create(&e, 0, thread_function, &nameE);
    
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    pthread_join(c, NULL);
    pthread_join(d, NULL);
    pthread_join(e, NULL);
    
    exit(EXIT_SUCCESS);
}

void OUR_DOWN(){
    sem_wait(&S.mutex);
    S.value -= 1;
    if(S.value < 0){
        sem_post(&S.mutex);
        sem_wait(&S.delay);
        sem_wait(&S.mutex);
        S.wake -= 1;
        if(S.wake > 0)
            sem_post(&S.delay);
    }
    sem_post(&S.mutex);
}

void OUR_UP(){
    sem_wait(&S.mutex);
    S.value += 1;
    if(S.value <= 0){
        S.wake += 1;
        if(S.wake == 1)
            sem_post(&S.delay);
    }
    sem_post(&S.mutex);
}

void *thread_function(void *args){
    char name = *(char *)args;
    printf("entry %c\n", name);
    OUR_DOWN();
    printf("critical section %c\n", name);
    sleep(5);
    printf("exit %c\n", name);
    OUR_UP();
    pthread_exit(NULL);
}