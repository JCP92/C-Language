#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUF_SIZE 4096
int CD(char *pth){

int main(int agv, char* agvc[]){
    int err;
    
    if(agv == 4){
        if(agvc[1][0] == '-' && agvc[1][1] == 'r'){
            err = rename(agvc[2], agvc[3]);
            if(err == -1){
                printf("Unable to correct");
            }
        }
    }
    else if(agv == 3){
        if(agvc[1][0] == '-' && agvc[1][1] == 'd'){
            err = rmdir(agvc[2]);
            if (err == -1){
                perror("ERROR: ");
            }
            else
                printf("Deleted");
        }
        else if(agvc[1][0] == '-' && agvc[1][1] == 'c'){
            err = mkdir(agvc[2], 0744);
            if (err == -1)
                printf("Unable to make dir");
            else
                printf("Made dir");
        }
        
    }
    else
        printf("dirp OPTION FILE [FILE]");

    return 0;
    

}
int CD(char *pth){
    char path[BUFFERSIZE];
    strcpy(path,pth);
    
    char cwd[BUFFERSIZE];
    if(pth[0] != '/')
    {// true for the dir in cwd
        getcwd(cwd,sizeof(cwd));
        strcat(cwd,"/");
        strcat(cwd,path);
        chdir(cwd);
    }else{//true for dir w.r.t. /
        chdir(pth);
    }
    
    return 0;
}
