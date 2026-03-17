// ex1: fork/wait básico
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pid, pid2, status;

    pid = fork();
    printf("valor inteiro do pid(filho): %d\n", pid);


    if (pid == -1){ // pid == -1 (erro)
        perror("Fork falhou\n");
        exit(-1);
    } else if (pid == 0){ // pid == 0 (filho)

        pid2 = fork();
        if (pid2 == -1) {
            perror("Fork falhou\n");
        exit(-1);
        } else if (pid2 == 0){
            printf("processo neto\t pid: %d\t pid filho: %d\n", getpid(), getppid());
            exit(0);
        } else { 
        wait(&status);
        printf("processos filho\t pid: %d\t pid pai: %d\n", getpid(), getppid());
        exit(0);
        }

        wait(&status);
        printf("processo filho\t pid: %d\t pid pai: %d\n", getpid(), getppid());
        exit(0);
    } else { // pid == 1 (pai)
        wait(&status);
        printf("processos pai\t pid: %d\t pid avô: %d\n", getpid(), getppid());
        exit(0);
    }
}
