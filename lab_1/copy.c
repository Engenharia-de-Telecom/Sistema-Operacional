#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 128

int myopen(const char *filename, int flags, size_t buffersize) {
    return open(filename, flags);
}

int myread(int fd, void *buf, size_t count) {
    return read(fd, buf, count);
}

int mywrite(int fd, void *buf, size_t count) {
    return write(fd, buf, count);
}

int myclose(int fd) {
    return close(fd);
}

int main(int argc, char **argv){
    
    int fd;
    char buf[SIZE];
    size_t readCount;


    if(argc != 2) {
        fprintf(stderr, "Uso correto: %s <nome_do_arquivo>\n", argv[0]);
        return 1;
    }

    // argv[0] é o nome do arquivo.
    // O_RONLY é a flag que indica que apenas vou ler o arquivo.

    fd = myopen(argv[1], O_RDONLY, SIZE);
    if(fd < 0){
        perror("file open");
        return 1;
    }


    while((readCount = myread(fd, buf, SIZE)) > 0) {
        if((mywrite(STDOUT_FILENO, buf, readCount)) != readCount) {
            perror("write");
            return 1;
        }
    }

    myclose(fd);
    return 0;
}