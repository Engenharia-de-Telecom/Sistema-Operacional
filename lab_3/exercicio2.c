// ex2: status/wait
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int pid, status;
    int resp = 1;
    int i = 5;

    // Cada laço do while, tem a criação de um filho
    // Cada filho fica responsável por uma multiplicação 
    while(i>0) {
        pid = fork(); // cria um filho
        if(pid == -1){ // verifica um possível erro
            perror("Fork falhou!\n");
        } else if (pid == 0){ // filho
            resp *= i; // o filho faz a multiplicação
            return resp; // retorna o valor
        } else { // pai
            wait(&status); // espera o filho terminar a multiplicação
            if(WIFEXITED(status)) { 
                i--; // decrementa o i
                resp = WEXITSTATUS(status); // armazena o valor
            }
        }
    }
    printf("%d! = %d\n", 5, resp);
    exit(0);
}