// gcc -Wall tcm.c -o tcm
// -Wall = Warning All (Mostra todos os erros quando compilado o arquivo)
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <linux/limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>


// man 3 cwd
int mycwd(){
    char cwd[PATH_MAX];
    if(getcwd(cwd, sizeof(cwd)) != 0) {
        printf("%s\n", cwd);
    } else{
        perror("getcwd() error\n");
        return 1;
    }
    return 0;
}

// man 2 mkdir
int mymkdir(){
    char in[256];
    scanf("%s", in);

    if(mkdir(in, 0700) != 0){
        perror("mkdir( error\n)");
        return 1;
    }
    
    return 0;
}


int myrmdir(){

    char in[256];
    scanf("%s", in);

    if(rmdir(in) != 0){
        perror("rmdir( error\n)");
        return 1;
    }
    
    return 0;
}


int mycd(){
    char in[256];
    scanf("%s", in);
    chdir(in);

    return 0;
}


int mystat(){
    return 0;
}

// opendir // closedir // readdir
int myls(){
    char in[256];
    struct dirent *dir;
    DIR *d;
    //scanf("%s", in);

    d = opendir(".");

    if(d != NULL){

        while((dir = readdir(d)) != NULL){
            printf("%s/", dir->d_name); 
        }
        closedir(d);
    } else{
        printf("Diretório %s não encontrado!\n", in);
        return 1;
    }

    return 0;
}



int main(int argc, char** argv){

    char in[256]; // Limitação de caracteres

    
    bool flag = true;
    while(flag){

        printf("tcm:~");
        scanf("%s", in);
        
        // Comparar a entrada com "exit"
        if(strcmp(in, "exit") == 0){
            flag = false;
        } else if(strcmp(in, "mycwd") == 0){
            mycwd();

        } else if(strcmp(in, "mymkdir") == 0){
            mymkdir();
            
        } else if(strcmp(in, "myrmdir") == 0){
            myrmdir();

        } else if(strcmp(in, "mycd") == 0){
            mycd();

        } else if(strcmp(in, "mystat") == 0){
            printf("Ainda não implementado!\n");

        } else if(strcmp(in, "myls") == 0){
            myls();

        } else if(strcmp(in, "help") == 0){
            printf("-----COMANDOS-DISPONÍVEIS----- \n");
            printf("mycwd\nmymkdir\nmycd\nmystat\nmyls\n");
            printf("------------------------------\n");

        } else{
            printf("Comando inválido!\n");
            printf("Help para listar os comandos disponíveis!\n");
        }
    }

    return 0;
}