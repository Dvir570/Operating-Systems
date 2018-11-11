#include <fcntl.h>
#include <stdlib.h>

#define BUFSIZE 256

int main(int argc, char *argv[]){
    int src_fd, dst_fd, rd_count, wt_count;
    char buffer[BUFSIZE];
    
    if(argc != 3) exit(1);
    
    src_fd = open(argv[1], O_RDONLY);
    if(src_fd < 0) exit(1);
    
    dst_fd = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if(dst_fd < 0) exit(1);
    
    while(1){
        rd_count = read(src_fd, buffer, BUFSIZE);
        if(rd_count <= 0) break;
        wt_count = write(dst_fd, buffer, rd_count);
        if(wt_count <= 0) exit(1);
    }
    if(close(src_fd) == -1) exit(1);
    if(close(dst_fd) == -1) exit(1);
    
    if(rd_count != 0) 
        exit(1);
    else 
        exit(0);
}