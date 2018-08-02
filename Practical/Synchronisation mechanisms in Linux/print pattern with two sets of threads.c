#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct syncResources{
    sem_t a_sems[3];
    sem_t b_sems[3];
    bool up;
} syncResources;

syncResources sr;

void *set_a(void *args);

void *set_b(void *args);

int main(){
    
    sem_init(sr.a_sems, 1, 1);
    sem_init(sr.b_sems, 1, 0);
    int i;
    for(i = 1; i < 3; i++){
        sem_init(sr.a_sems + i, 1, 0);
        sem_init(sr.b_sems + i, 1, 0);
    }
    sr.up = true;
    pthread_t a,b,c,x,y,z;
    char na = 'a';
    char nb = 'b';
    char nc = 'c';
    char nx = 'x';
    char ny = 'y';
    char nz = 'z';
    pthread_create(&a, NULL, set_a, (void *)&na);
    pthread_create(&b, NULL, set_a, (void *)&nb);
    pthread_create(&c, NULL, set_a, (void *)&nc);
    pthread_create(&x, NULL, set_b, (void *)&nx);
    pthread_create(&y, NULL, set_b, (void *)&ny);
    pthread_create(&z, NULL, set_b, (void *)&nz);
    
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    pthread_join(c, NULL);
    pthread_join(x, NULL);
    pthread_join(y, NULL);
    pthread_join(z, NULL);
}

void *set_a(void *args){
    char name = *(char *)args;
    int index;
    switch (name){
        case 'a':
            index = 0;
            break;
        case 'b':
            index = 1;
            break;
        case 'c':
            index = 2;
            break;
    }
    
    while(1){
        sem_wait(&sr.a_sems[index]);
        printf("Thread %c\n", name);
        if(sr.up){
            if(index == 2)
                sem_post(&sr.b_sems[0]);
            else
                sem_post(&sr.a_sems[index+1]);
        }else{
            if(index == 0)
                sem_post(&sr.b_sems[2]);
            else
                sem_post(&sr.a_sems[index-1]);
        }
    }
    pthread_exit(NULL);
}

void *set_b(void *args){
    char name = *(char *)args;
    int index;
    switch (name){
        case 'x':
            index = 0;
            break;
        case 'y':
            index = 1;
            break;
        case 'z':
            index = 2;
            break;
    }
    
    while(1){
        sem_wait(&sr.b_sems[index]);
        printf("Thread %c\n", name);
        if(sr.up){
            if(index == 2){
                sr.up = false;
                sem_post(&sr.a_sems[2]);
            }else
                sem_post(&sr.b_sems[index+1]);
        }else{
            if(index == 0){
                sr.up = true;
                sem_post(&sr.a_sems[0]);
            }else
                sem_post(&sr.a_sems[index-1]);
        }
    }
    pthread_exit(NULL);
}