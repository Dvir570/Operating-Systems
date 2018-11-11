#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc != 1){
        perror("Error: ");
        exit(1);
    }
    
    int i;
    for(i = 0; i < 5; i++)
        printf("%s", argv[0]);
    sleep(1);
    printf("Child: Thank you!!!\n");
    exit(0);
}