#include <stdio.h>

int main(){
    FILE *input;
    FILE *output;
    int num, success;
    input = fopen("/dev/tty", "r");
    output = fopen("/dev/tty", "w");
    fprintf(output, "Enter a number: ");
    success = fscanf(input, "%d", &num);
    if(success)
        fprintf(output, "\nYour number is %d", num);
    else
        fprintf(stderr, "It isn't a number\n");
}