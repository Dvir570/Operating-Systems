#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int fd_in, fd_out;
    char c;
    if(argc != 3)
        exit(1);
    fd_in = open(argv[1], O_RDONLY);
    fd_out = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    while(read(fd_in, &c, 1) == 1)
        write(fd_out, &c, 1);
    exit(0);
}