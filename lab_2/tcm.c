// gcc -Wall tcm.c -o tcm
// -Wall = Warning All (Mostra todos os erros quando compilado o arquivo)
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <linux/limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>


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
        perror("mkdir() error\n)");
        return 1;
    }
    
    return 0;
}


int myrmdir(){

    char in[256];
    scanf("%s", in);

    if(rmdir(in) != 0){
        perror("rmdir() error\n)");
        return 1;
    }
    
    return 0;
}


int mycd(){
    char in[256];
    scanf("%s", in);

    if(chdir(in) != 0){
        perror("cd() error\n");
        return 1;
    }

    return 0;
}


int mystat(){
    char in[256];
    struct stat info;
    
    scanf("%s", in);
    if(stat(in, &info) != 0){
        perror("stat() error\n");
        return 1;
    }

    printf("Arquivo: %s\n", in);
    printf("Tamanho: %ld bytes\n", info.st_size);
    printf("Acesso: %s", ctime(&info.st_atime));
    printf("Ultima modificação: %s", ctime(&info.st_mtime));



    
    return 0;
}

// opendir // closedir // readdir
int myls(){
    char in[256];
    struct dirent *dir;
    DIR *d;
    //scanf("%s", in);

    d = opendir("."); // Usando ponto para sempre passar o diretório atual ficando mais parecido com o shell covencional

    if(d != NULL){

        while((dir = readdir(d)) != NULL){
            printf("%s/", dir->d_name); 
        }
        printf("\n");
        closedir(d);
    } else{
        printf("Diretório %s não encontrado!\n", in);
        return 1;
    }

    return 0;
}



int main(int argc, char** argv){

    char in[256]; // Limitação de caracteres
    char cwd[PATH_MAX];
    

    bool flag = true;
    while(flag){

        getcwd(cwd, sizeof(cwd)); // Obtem todo o diretório
        char *dir = strrchr(cwd, '/'); // Caminha pelo diretório até encontrar o ultimo '/' e aponta para ele

        if(dir != NULL){
            printf("\033[32mtcm:~%s>\033[0m ", dir + 1); // Quando ele apontar para a ultima barra, somamos 1 para o ponteiro apontar para a posição do diretório
        } else {
            printf("\033[32mtcm:~%s>\033[0m ", cwd); // Quando não tem barra, CWD armazena apenas o nome do único diretório
        }
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
            mystat();

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