#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#define oops( m, x ) { perror(m); exit(x); }
#define BUFF 128

static void parse(int* i, char* input, char* args[] );

int main(int ac, char* arg[])
{
    char str[BUFF];
    int startWait, endWait;
    
    printf("$$ ");
    while (fgets (str, BUFF, stdin) != 0 && strcmp(str, "exit\n") != 0){
        int pid, goal, pipe_num;
        int fd1[2] = {-1, -1};
        int fd2[2] = {-1, -1 };
        int pipe_loc[16];
        int *i = &ac;
        
        parse(i, str, arg);
        
        pipe_loc[0] = pipe_num = 0;

        if(strcmp(arg[0], "cd") == 0){
            if(chdir(arg[1]) != 0)
                perror("");
            printf("\n$$ ");
        }
        else{
            for (int i = 0; i < ac; i++){ // locates | for amount of splits
                if (strcmp(arg[i], "|") == 0){
                    arg[i] = NULL; /* set equal to null to avoid it during processing and to pass into the pipe/fork */
                    pipe_loc[++pipe_num] = i+1;
                }
            }
        
            for (int i = 0; i < pipe_num+1; i++){ // run through all sections of the command
                if (i != pipe_num){
                    if (pipe_num > 0){
                        if (pipe(fd2) != 0) // start pipe
                            oops("failed pipe", 1);
                    }
                }
            
                if ((pid = fork()) < 0)
                    oops("fork failed", 2);
                if (pid == 0){
                    if (i != pipe_num){ // decides whether its a child, parent or both
                        dup2(fd2[1], 1); // duplicates write so its still writible
                        close(fd2[0]); // closes original read
                        close(fd2[1]); // closes original write
                    }
                    if (i != 0){ // decides whether its a child, parent or both
                        dup2(fd1[0], 0); //duplicates read
                        close(fd1[0]); // closes original read
                        close(fd1[1]); // closes original write
                    }
                    
                    goal = pipe_loc[i];
                    
                    if(!execvp(arg[goal], &arg[goal])) // executes system command
                        oops("Execvp Fail:", 0);
                }
            
                if (i != 0){
                    close(fd1[0]); // closes both of fd1
                    close(fd1[1]);
                }
            
                fd1[0] = fd2[0]; // set fd2 to fd1  to continue the multi piping process
                fd1[1] = fd2[1];
            }
        
            close(fd1[0]); // closes last pipes
            close(fd1[1]);
        

            while ((startWait = waitpid(0, &endWait, 0)) > 0){} // pause
            printf("end while %i\n", startWait);
        
            printf("\n$$ ");
        }
    }
}



static void parse(int *i, char* input, char* args[]){
    (*i) = 0;
    
    // fgets reads the \n, so overwrite it
    input[strlen(input)-1] = '\0';
    
    // get the first token
    args[(*i)] = strtok( input, " " );
    
    // get the rest of them
    while( ( args[++(*i)] = strtok(NULL, " ") ) );
}
