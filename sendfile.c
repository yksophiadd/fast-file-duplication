#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return -1;
    }

    int fd_in = open(argv[1], O_RDWR);
    if(fd_in == -1){
        perror("readwrite: open_in");
        return -1;
    }

    int fd_out = open(argv[2], O_CREAT|O_RDWR|O_TRUNC, 0777);
    if(fd_out == -1){
        perror("readwrite: open_out");
        return -1;
    }

    //for the use of size
    struct stat statbuf;  
    int err = fstat(fd_in, &statbuf);
    if (err == -1){
        perror("filestat wrong");
        return -1;
    }

    off_t offset = 0;

    ssize_t write = sendfile(fd_out, fd_in, &offset, statbuf.st_size);
    if (write == -1){
        perror("sendfile wrong");
        return -1;
    }

    close(fd_in);
    close(fd_out);
    return 0;
}
