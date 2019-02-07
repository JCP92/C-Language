#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>

#define BUFF 100

int main(){
    int get_id;
    char input[BUFF];
    char* shmptr = NULL;
    
    get_id = shmget(100, BUFF, 0777);
    shmptr = shmat(get_id, NULL, 0);
    
    while( 1 ){
        printf("$ ");
        
        fgets(input, BUFF, stdin);
        input[strlen(input)-1] = '\0';
        strcpy(shmptr, input);
        
        if(strcmp(input, "QUIT")==0 || strcmp(input, "quit") == 0){
            break;
        }
    }
}

