#include <stdio.h>
#include <sys/types.h>

int main(){
    int i;
    for(i = 0; i < 10; i++){
        printf("hello\n");
        fork();
    }
    return 0;
}

/*
How many lines of "hello" will be printed?

ANSWER:
1 + 2 + 4 + 8 + 16 + 32 + 64 + 128 + 256 + 512
*/