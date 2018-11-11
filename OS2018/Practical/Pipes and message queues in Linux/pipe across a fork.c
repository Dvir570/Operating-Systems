#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
    int pipe_fd[2];
    char buffer[BUFSIZ + 1];
    char *some_data = "So hello from the other side...";
    int data_processed;
    memset(buffer, '\0', sizeof(buffer));
    
    if(pipe(pipe_fd) == 0){
        pid_t fork_res = fork();
        if(fork_res == 0){
            data_processed = read(pipe_fd[0], buffer, BUFSIZ);
            printf("Read %d bites:\n%s\n", data_processed, buffer);
            exit(EXIT_SUCCESS);
        }else{
            data_processed = write(pipe_fd[1], some_data, strlen(some_data));
            printf("Wrote %d bytes\n", data_processed);
        }
        exit(EXIT_SUCCESS);
    }
}