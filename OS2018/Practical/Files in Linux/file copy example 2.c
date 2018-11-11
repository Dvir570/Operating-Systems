#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int fd_in, fd_out;
    char c;
    if(argc != 3)
        EXIT_FAILURE;
    if(fd_in = open(argv[1], O_RDONLY) < 0)
        EXIT_FAILURE;
    if(fd_out = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR) < 0)
        EXIT_FAILURE;
    while(read(fd_in, &c, 1) == 1)
        write(fd_out, &c, 1);
    close(fd_in);
    close(fd_out);
    EXIT_SUCCESS;
}