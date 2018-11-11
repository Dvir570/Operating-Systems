#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *a_statement(void *args);
void *b_statement(void *args);

int main(){
    pthread_t a_thread, b_thread;
    pthread_mutex_t mutexes[2];
    pthread_mutex_init(mutexes, NULL);
    pthread_mutex_init(mutexes + 1, NULL);
    pthread_mutex_lock(mutexes);
    pthread_mutex_lock(mutexes + 1);
    
    if(pthread_create(&a_thread, NULL, a_statement, mutexes) != 0){
        perror("pthread_create error");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&b_thread, NULL, b_statement, mutexes) != 0){
        perror("pthread_create error");
        exit(EXIT_FAILURE);
    }
    pthread_join(a_thread, NULL);
    pthread_join(b_thread, NULL);
    exit(EXIT_SUCCESS);
}

void *a_statement(void *args){
    pthread_mutex_t *mutexes = (pthread_mutex_t *)args;
    printf("STATEMENT A1\n");
    pthread_mutex_unlock(mutexes + 1);
    pthread_mutex_lock(mutexes);
    printf("STATEMENT A2\n");
}

void *b_statement(void *args){
    pthread_mutex_t *mutexes = (pthread_mutex_t *)args;
    printf("STATEMENT B1\n");
    pthread_mutex_unlock(mutexes);
    pthread_mutex_lock(mutexes + 1);
    printf("STATEMENT B2\n");
}