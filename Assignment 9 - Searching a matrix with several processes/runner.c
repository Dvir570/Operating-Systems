#include <sys/shm.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "headers.h"

void lets_go(Map *shmadd, int i, int j);

int main(int argc, char *argv[]){
    if(argc != 2){
        perror("argc error\n");
        exit(EXIT_FAILURE);
    }
    int i = atoi(argv[0]), j = atoi(argv[1]);
    int shmid = shmget(1234, sizeof(Map), 0777);
    if(shmid == -1){
        perror("shmget error\n");
        exit(EXIT_FAILURE);
    }
    Map *shmadd = (Map *)shmat(shmid, 0, SHM_RND);
    while(1)
        lets_go(shmadd, i, j);
    
    exit(EXIT_SUCCESS);
}

void lets_go(Map *shmadd, int i, int j){
    Cell current = shmadd->cells[i][j];
    sem_wait(&(current.bit_sem));
        if(current.bit == 1){
            sem_wait(&(shmadd->k_sem));
                shmadd->k--;
            sem_post(&(shmadd->k_sem));
            current.bit = 0;
        }
    sem_post(&(current.bit_sem));
    
    
    //Terminate travel cheking
    sem_wait(&(shmadd->k_sem));
        if(shmadd->k <= 0){
            sem_post(&(shmadd->k_sem));
            printf("DONE!\n");
            shmdt(shmadd);
            exit(EXIT_SUCCESS);
        }
    sem_post(&(shmadd->k_sem));
    //TRAVEL UP
    if(i != 0){
        sem_wait(&(shmadd->row_edjes_sems[i-1][j]));
        if(shmadd->row_edjes_flags[i-1][j] == true){
            shmadd->row_edjes_flags[i-1][j] = false;
            sem_post(&(shmadd->row_edjes_sems[i-1][j]));
            //printf("UP");
            lets_go(shmadd, i-1, j);
        }else
            sem_post(&(shmadd->row_edjes_sems[i-1][j]));
    }
    //TRAVEL DOWN
    if(i != 99){
        sem_wait(&(shmadd->row_edjes_sems[i+1][j]));
        if(shmadd->row_edjes_flags[i+1][j] == true){
            shmadd->row_edjes_flags[i+1][j] = false;
            sem_post(&(shmadd->row_edjes_sems[i+1][j]));
            //printf("DOWN");
            lets_go(shmadd, i+1, j);
        }else
            sem_post(&(shmadd->row_edjes_sems[i+1][j]));
    }
    //TRAVEL RIGHT
    if(j != 99){
        sem_wait(&(shmadd->column_edjes_sems[i][j+1]));
        if(shmadd->column_edjes_flags[i][j+1] == true){
            shmadd->column_edjes_flags[i][j+1] = false;
            sem_post(&(shmadd->column_edjes_sems[i][j+1]));
            //printf("RIGHT");
            lets_go(shmadd, i, j+1);
        }else
            sem_post(&(shmadd->column_edjes_sems[i][j+1]));
    }
    //TRAVEL LEFT
    if(j != 0){
        sem_wait(&(shmadd->column_edjes_sems[i][j-1]));
        if(shmadd->column_edjes_flags[i][j-1] == true){
            shmadd->column_edjes_flags[i][j-1] = false;
            sem_post(&(shmadd->column_edjes_sems[i][j-1]));
            //printf("LEFT");
            lets_go(shmadd, i, j-1);
        }else
            sem_post(&(shmadd->column_edjes_sems[i][j-1]));
    }
}