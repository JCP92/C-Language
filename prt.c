#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUF_SIZE 4096

int main(int agv, char* agvc[]){
    if(agv != 2){
        perror("prt [FILENAME]");
        return(0);
    }
    
    char buf[BUF_SIZE];
    ssize_t read_in, write_out;
    
    int input_file = open(agvc[1], O_RDONLY);
    if(input_file == -1){
        int err = errno;
        if(err == ENOENT)
            perror("");
        else if(err == EPERM)
            perror("");
        return(0);
    }

    while( read(input_file, &buf, BUF_SIZE) > 0){
        write(1, &buf, BUF_SIZE);
    }

    close(input_file);

    return 0;
    

}
