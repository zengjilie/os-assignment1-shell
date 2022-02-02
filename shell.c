#include<stdio.h>
#include<stdlib.h>
// use execvp in your project
//build a file system 
//CRUD on files, file descriptor table
//input output redirection
int main (int argc, char **argv){
    pid_t cpid;
    int ofd;
    char *cmd, *output;

    cmd = argv[1]; output = argv[2];
    cpid = fork();
    if(cpid == 0){
        printf("Running like: %s > %s\n", cmd, output);
        ofd = creat(ouput, 0644);
        dup2(ofd, 1);
        execlp(cmd, cmd, (char*)NULL);
    }
    wait((int *)NULL);
}

//pipe
