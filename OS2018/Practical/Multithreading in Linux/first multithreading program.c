#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void *thread_task(void *args);

char message[] = "Hello form the other side";

int main(){
    pthread_t a_thread;
    void *thread_res = NULL;
    if(pthread_create(&a_thread, NULL, thread_task, (void *)message) != 0){
        printf("pthread_create error\n");
        exit(EXIT_FAILURE);
    }
    printf("Wating for thread to finish...\n");
    if(pthread_join(a_thread, &thread_res) != 0){
        printf("pthread_join error\n");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined, it returned: %s\n", (char *)thread_res);
    printf("Message is now: %s\n", message);
    exit(EXIT_SUCCESS);
}

void *thread_task(void *args){
    printf("Thread start execution...\n");
    printf("Argument is: %s\n", (char *)args);
    sleep(3);
    
    strncpy(message, "Have a nice day!", strlen(message));
    pthread_exit("Thank for CPU time :)");
}