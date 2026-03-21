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
    char entrada[256];
    int pid, status;
    while(true){
        printf("> ");

        fgets(entrada, 256, stdin);
        entrada[strcspn(entrada, "\n")] = '\0'; // strcspn retorna o índice

        bool ecomercial = false;
        if(entrada[strlen(entrada) - 1] == '&'){ // verifica se '&' esta na entrada
            ecomercial = true;
            entrada[strlen(entrada) - 1] = '\0';
        }

        while(strlen(entrada) > 0 && entrada[strlen(entrada) - 1]  == ' '){
            entrada[strlen(entrada) - 1] = '\0';
        }


        if(strcmp(entrada, "sair") == 0){
            exit(0);
        }
        
        pid = fork();
        if(pid == -1){ // erro
            perror("Fork falhou!");

        } else if(pid == 0){ // filho
            char *args[] = {entrada, NULL};
            printf("Executando: [%s]\n", entrada);
            execve(entrada, args, NULL);
            perror("Erro");
            exit(1);

        } else{
            printf("%d\n", ecomercial);
            if(!ecomercial){
                printf("Entrando no wait\n");
                wait(&status);
        }
        }
    }
}