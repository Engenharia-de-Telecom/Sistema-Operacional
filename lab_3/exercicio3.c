// ex3: fork/wait/exec

// Implemente um terminal que leia caminhos completos de programas e execute-os usando fork() e
// execve(). Utilize wait() se o comando não terminar com &, caso contrário, passagem livre. O laço deve continuar
// até que o usuário digite sair.
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char** argv){
    char caminho[256];

}