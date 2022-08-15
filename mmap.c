#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return -1;
    }

    int fd_in = open(argv[1], O_RDWR);
    if(fd_in == -1){
        perror("readwrite: open");
        return -1;
    }

    int fd_out = open(argv[2], O_CREAT|O_RDWR|O_TRUNC, 0777);
    if(fd_out == -1){
        perror("readwrite: creat");
        return -1;
    }

    struct stat statbuf;  //for the use of size
    int err = fstat(fd_in, &statbuf);
    if (err == -1){
        perror("filestat wrong");
        return -1;
    }

    char *mapptr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd_in, 0);
    if (mapptr == MAP_FAILED){
        perror("mapfailed");
        close(fd_in);
        return -1;
    }
    close(fd_in);

    ssize_t written = write(fd_out, mapptr, statbuf.st_size);
    if (written == -1){
        perror("write failed");
        return -1;
    }

    int unmap = munmap(mapptr, statbuf.st_size);
    if (unmap == -1){
        perror("unmap failed");
        return -1;
    }
    //close(fd_in);
    close(fd_out);
    return 0;
}
