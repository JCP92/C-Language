#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/dir.h"

int main(int agv, char* agvc[]){
    if(agv != 2)
        exit(1);
    char* pnt = agvc[0];
    FILE* file_open = NULL;
    file_open = fopen(pnt, "r");
    ssize_t = rin, rout;
    
    if(!file_open){
        int err = errno;
        if(err == ENOENT)
            printf("No such file or directory");
        else if(err == EPERM)
            printf("Operation not permitted");
        return(0);
    }
    
    long int ol;
    
    fseek(file_open, ol, SEEK_END);
    int length;
    length = ftell(file_open);
    fseek(file_open, 0, SEEK_SET);
    

    char buf[++length];
    read(file_open, buf, length);
    write(1, buf, length);
    
    return 0;
    

}
