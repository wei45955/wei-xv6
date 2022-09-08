#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char ** argv) {    
    if(argc != 2 ) {
        fprintf(2, "The parameter should be an positive integer\n");
        exit(-1);
    }
    int sec = atoi(argv[1]);
    printf("%d", sec);
    if(sec < 0) {
        fprintf(2, "The parameter should be an positive integer\n");
        exit(-1);
    }

    sleep(sec);
    
    exit(0);
}