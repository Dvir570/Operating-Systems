#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

void join_barrier();

void *statements(void *args);

sem_t mutex, barrier;
int counter = 0;

int main(){
    sem_init(&mutex, 1, 1);
    sem_init(&barrier, 1, 0);
    
    pthread_t a, b, c, d;
    char nameA = 'A', nameB = 'B', nameC = 'C', nameD = 'D';
    if(pthread_create(&a, 0, statements, &nameA) == -1 ||
            pthread_create(&b, 0, statements, &nameB) == -1 ||
            pthread_create(&c, 0, statements, &nameC) == -1 ||
            pthread_create(&d, 0, statements, &nameD) == -1){
        perror("pthread_create error\n");
        exit(EXIT_FAILURE);
    }
    
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    pthread_join(c, NULL);
    pthread_join(d, NULL);
    
    //Reuse barrier
    if(pthread_create(&a, 0, statements, &nameA) == -1 ||
            pthread_create(&b, 0, statements, &nameB) == -1 ||
            pthread_create(&c, 0, statements, &nameC) == -1 ||
            pthread_create(&d, 0, statements, &nameD) == -1){
        perror("pthread_create error\n");
        exit(EXIT_FAILURE);
    }
    
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    pthread_join(c, NULL);
    pthread_join(d, NULL);
    
    //Reuse barrier
    if(pthread_create(&a, 0, statements, &nameA) == -1 ||
            pthread_create(&b, 0, statements, &nameB) == -1 ||
            pthread_create(&c, 0, statements, &nameC) == -1 ||
            pthread_create(&d, 0, statements, &nameD) == -1){
        perror("pthread_create error\n");
        exit(EXIT_FAILURE);
    }
    
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    pthread_join(c, NULL);
    pthread_join(d, NULL);
    
    exit(EXIT_SUCCESS);
}

void *statements(void *args){
    char name = *(char *)args;
    printf("Statement 1 %c\n", name);
    join_barrier();
    printf("Statement 2 %c\n", name);
    pthread_exit(NULL);
}

void join_barrier(){
    sem_wait(&mutex);
    counter ++;
    sem_post(&mutex);
    if(counter == 4){
        sem_post(&barrier);
    }
    sem_wait(&barrier);
    sem_wait(&mutex);
    if(counter > 1)
        sem_post(&barrier);
    counter --;
    sem_post(&mutex);
    
}