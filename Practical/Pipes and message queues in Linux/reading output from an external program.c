#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *read_fp;
    char buffer[BUFSIZ];
    int chars_count;
    memset(buffer, '\0', sizeof(buffer));
    read_fp = popen("uname -a", "r");
    if(read_fp != NULL){
        chars_count = fread(buffer, sizeof(char), sizeof(buffer), read_fp);
        if(chars_count > 0){
            printf("The output is:\n%s", buffer);
        }
        pclose(read_fp);
        exit(EXIT_SUCCESS);
    }else
        exit(EXIT_FAILURE);
}