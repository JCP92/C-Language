

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <string.h>

#define BUFF 100


void Ctrl_C(int);
int get_id, id=0;
char* shmptr = NULL;

int main(){
    
    signal(SIGINT, Ctrl_C);
    get_id = shmget(100, BUFF, IPC_CREAT | IPC_EXCL | 0777);
    shmptr = shmat(get_id, NULL, 0);
    
    while(1)
    {
        if(strcmp(shmptr, "HI") == 0 || strcmp(shmptr, "hi") == 0){
            printf("Greetings!\n");
            fflush(stdout);
            shmptr[0] = '\0';
            
        }
        else if(strcmp(shmptr, "PID") == 0 || strcmp(shmptr, "pid") == 0){
            id = getpid();
            printf("Server pid: %i\n", id);
            fflush(stdout);
            shmptr[0] = '\0';
            
        }
        else if(strcmp(shmptr, "QUIT") == 0 || strcmp(shmptr, "quit") == 0){
            shmctl(get_id, IPC_RMID, NULL);
            shmdt(shmptr);
            printf("GOODBYE!\n");
            exit(0);
        }
    }
}

void Ctrl_C(int handle)
{
    shmctl(get_id, IPC_RMID, NULL);
    shmdt(shmptr);
    printf("GOODBYE!\n");
    exit(0);
}
