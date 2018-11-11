#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    if(fork()){
        int i;
        for(i = 0; i < 5; i++)
            printf("Parent: You are the best!!\n");
        sleep(1);
        printf("Parent: You are the best!!\n");
        exit(0);
    } else{
        char *argv[2];
        argv[0] = "Child: No, you are the best!!\n";
        argv[1] = NULL;
        if(execvp("/home/ubuntu/workspace/child.out", argv) == -1){
            perror("Error: ");
            exit(1);
        }
    }
    
    printf("No one will print it\n");
}