#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct resources{
    pthread_mutex_t even_mutex;
    pthread_mutex_t odd_mutex;
    int counter;
}resources;

void *even_printer(void *args);

void *odd_printer(void *args);

int main(){
    pthread_t e_thread, o_thread;
    resources r;
    r.counter = 0;
    pthread_mutex_init(&r.even_mutex, NULL);
    pthread_mutex_init(&r.odd_mutex, NULL);
    
    pthread_mutex_lock(&r.odd_mutex);
    
    if(pthread_create(&e_thread, NULL, even_printer, (void *)&r) != 0
        || pthread_create(&o_thread, NULL, odd_printer, (void *)&r) != 0){
        perror("pthread_create error\n");
        exit(EXIT_FAILURE);
    }
    
    pthread_join(e_thread, NULL);
    pthread_join(o_thread, NULL);
    printf("\n");
    exit(EXIT_SUCCESS);
}

void *even_printer(void *args){
    resources *r = (resources *)args;
    int i;
    
    for(i = 0; i < 20; i++){
        pthread_mutex_lock(&r->even_mutex);
        printf("E%d ", r->counter);
        r->counter++;
        pthread_mutex_unlock(&r->odd_mutex);
    }
    pthread_exit(NULL);
}

void *odd_printer(void *args){
    resources *r = (resources *)args;
    int i;
    
    for(i = 0; i < 20; i++){
        pthread_mutex_lock(&r->odd_mutex);
        printf("O%d ", r->counter);
        r->counter++;
        pthread_mutex_unlock(&r->even_mutex);
    }
    pthread_exit(NULL);
}








