#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

#define UP 0
#define DOWM 1
#define RIGHT 2
#define LEFT 3


int main(){
    int shmid = shmget(1234, sizeof(Map), 0777 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed\n");
        exit(EXIT_FAILURE);
    }
    Map *shmadd = (Map *)shmat(shmid, 0, 0);
    shmadd->k = 0;
    sem_init(&(shmadd->k_sem), 1, 1);
    
    int i, j;
    for(i = 0; i < 100; i++){
        for(j = 0; j < 100; j++){
            if((i+j) % 7 == 0){
                shmadd->cells[i][j].bit = 1;
                shmadd->k++;
            }else{
                shmadd->cells[i][j].bit = 0;
            }
            sem_init(&(shmadd->cells[i][j].bit_sem), 1, 1);
            if(i < 99 && j < 99){
                sem_init(&(shmadd->row_edjes_sems[i][j]), 1, 1);
                shmadd->row_edjes_flags[i][j] = true;
                sem_init(&(shmadd->column_edjes_sems[i][j]), 1, 1);
                shmadd->column_edjes_flags[i][j] = true;
            }
        }
    }
    printf("Count of ones: %d\n", shmadd->k);
    printf("And now we can start....\n");
    
    for(i = 0; i < 4; i++){
        int pid = fork();
        if(!pid){
            char *argv[3];
            if(i==0){
                argv[0] = "0";
                argv[1] = "0";
                argv[2] = NULL;
            } else if(i==1){
                argv[0] = "0";
                argv[1] = "99";
                argv[2] = NULL;
            } else if(i==2){
                argv[0] = "99";
                argv[1] = "0";
                argv[2] = NULL;
            } else if(i==3){
                argv[0] = "99";
                argv[1] = "99";
                argv[2] = NULL;
            }
            
            if(execvp("/home/ubuntu/workspace/Assignment9 - Matrix/runner.out", argv) == -1){
                perror("execvp error\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    for(i = 0; i < 4; i++){
        wait(0);
        printf("done %d\n", i);
    }
    printf("Count of ones: %d\n", shmadd->k);
    shmdt(shmadd);
    exit(EXIT_SUCCESS);
}