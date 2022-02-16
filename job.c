#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

int main(){
    execlp("jobs","jobs",NULL);
    return 0;
}