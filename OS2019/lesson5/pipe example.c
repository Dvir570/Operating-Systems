#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int pipe_fd[2];
    char buffer[BUFSIZ];
    
    if(pipe(pipe_fd) == 0){
        pid_t pid = fork();
        if(pid < 0){
            perror("Error: ");
            exit(EXIT_FAILURE);
        }else if(pid){ //parent
            char *data = "So hello from the other side...";
            if(close(pipe_fd[0]) == -1) exit(EXIT_FAILURE);
            int count_w = write(pipe_fd[1], data, strlen(data));
            printf("Wrote %d bytes\n", count_w);
            if(close(pipe_fd[1]) == -1) exit(EXIT_FAILURE);
            exit(EXIT_SUCCESS);
        }else{ //child
           if(close(pipe_fd[1]) == -1) exit(EXIT_FAILURE);
           int count_r = read(pipe_fd[0], buffer, BUFSIZ);
           printf("Read %d bytes:\n %s\n", count_r, buffer);
           if(close(pipe_fd[0]) == -1) exit(EXIT_FAILURE);
           exit(EXIT_SUCCESS);
        }
        
    }
    perror("Error: ");
    exit(EXIT_FAILURE);
}