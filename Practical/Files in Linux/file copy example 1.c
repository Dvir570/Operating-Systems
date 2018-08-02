#include <fcntl.h>
#include <stdlib.h>

#define BUFSIZE 256

int main(int argc, char *argv[]){
    int fd_in, fd_out, rd_count, wt_count;
    char buffer[BUFSIZE];
    if(argc != 3) exit(1);
    fd_in = open(argv[1], O_RDONLY);
    if(fd_in < 0) exit(2);
    fd_out = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if(fd_out < 0) exit(3);
    while(1){
        rd_count = read(fd_in, buffer, BUFSIZE);
        if(rd_count <= 0) break;
        wt_count = write(fd_out, buffer, rd_count);
        if(wt_count <= 0) exit(4);
    }
    close(fd_in);
    close(fd_out);
    if(rd_count != 0) 
        exit(5);
    else 
        exit(0);
}