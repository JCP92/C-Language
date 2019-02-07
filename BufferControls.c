#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <utime.h>
#include <string.h>
#include <termios.h>


int main( int argc, char* args[] )
{
    struct termios adjSet;
        tcgetattr(0, &adjSet);
        adjSet.c_lflag &= ~ICANON;		// turn buffering off
        adjSet.c_cc[VMIN] = 1;
        adjSet.c_lflag &= ~ECHO;
        tcsetattr(0, TCSANOW, &adjSet);
    
    int s = fcntl(0, F_GETFL);
    s |= O_SYNC;
    int result = fcntl(0, F_SETFL,s);
    if(result == -1)
        perror("");
    
    
    char x;
    while( (x = getchar()) != 'q'){
        switch (x) {
            case 'a':
                puts("LEFT");
                break;
            case 'd':
                puts("RIGHT");
                break;
            case 's':
                puts("DOWN");
                break;
            case 'w':
                puts("UP");
                break;
            default:
                break;
        }
    }
    adjSet.c_lflag |= ECHO;
    tcsetattr(0, TCSANOW, &adjSet);
    return 0;
    
}
