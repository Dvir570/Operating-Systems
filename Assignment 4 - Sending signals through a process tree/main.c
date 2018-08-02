#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

#define SIGOK 10

pid_t pid_child;

void forever(){
    while(1);
}

void createProcess (void (*F) (void)){
    pid_t pid_child = fork();
    if(pid_child){
        return;
    }else{
        F();
    }
}

int sendSignal(int sig){
    if(pid_child)
        kill(pid_child, SIGINT);
    else kill(getpid(), SIGOK);
}

int sigok_handler(int sig){
    kill(getppid(), SIGOK);
    printf("exit %d\n", getpid());
    exit(0);
}

int main(){
    signal(SIGINT, sendSignal);
    signal(SIGOK, sigok_handler);
    
    return 0;
}