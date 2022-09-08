#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int pipe1[2]; // 用于父->子
    int pipe2[2]; // 用于子->父
    pipe(pipe1);
    pipe(pipe2);    

    if(fork() == 0) {
        char ch [2] = {'2'};

        // 接受父进程发来的
        close(0);
        dup(pipe1[0]);
        close(pipe1[0]);
        close(pipe1[1]);
        read(0, ch, 1);
        printf("<%d>: received ping: %s\n", getpid(), ch);

        ch[0] = 'c';
        // 给父进程发
        close(1);
        dup(pipe2[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        write(1, ch, 1);

        exit(0);
    }
    else {
        char ch [2] = {'f'};
        // 给子进程发
        write(pipe1[1], ch, 1);
        close(pipe1[0]);
        close(pipe1[1]);

        // 接受子进程发来的
        read(pipe2[0], ch, 1);
        fprintf(1, "<%d>: received pong: %s\n", getpid(), ch);
        close(pipe2[0]);
        close(pipe2[1]);

        wait(0);
        exit(0);
    }
}