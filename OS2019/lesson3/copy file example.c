#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int src_fd, dst_fd;
    char buf;
    
    if(argc != 3){
        printf("argc error\n");
        exit(1);
    }
    
    printf("%s\n", argv[0]);
    
    src_fd = open(argv[1], O_RDONLY);
    if(src_fd < 1){
        printf("open error\n");
        exit(1);
    }
    
    dst_fd = open(argv[2], O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
    if(dst_fd < 1){
        printf("open error\n");
        exit(1);
    }
    
    int rd_count;
    while((rd_count = read(src_fd, &buf, 1)) == 1){
        if(write(dst_fd, &buf, 1) != 1){
            printf("write error\n");
            exit(1);
        }
    }
    
    if(close(src_fd) == -1) exit(1);
    if(close(dst_fd) == -1) exit(1);
    
    if(rd_count == -1){
        printf("read error\n");
        exit(1);
    }else { // rd_count == 0
        EXIT_SUCCESS; // exit(0);
    }
}