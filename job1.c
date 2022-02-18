#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void handler(int sig)
{
    int child_pid = waitpid(-1, NULL, WUNTRACED | WNOHANG);
    printf("finished child %d\n",child_pid);
    return;
}
int main()
{
    signal(SIGCHLD, handler);

    int id = fork();
    if (id == 0)
    {
        sleep(2);
        printf("child finished %d",getpid());
        exit(0);
    }
    else
    {
        pid_t pid;
        int status;
        waitpid(-1, NULL, WNOHANG);
        while (1)
        {
            sleep(1);
            printf("parent run\n");
        }
        // while (1)
        // {
        //     sleep(1);
        //     printf("status: %d",pid);
        // }
        // while (pid > 0)
        // {
        //     sleep(4);
        //     if (id == 0)
        //     {
        //         sleep(1);
        //         printf("status: %d", pid);
        //     }
        //     else if (id > 0)
        //     {
        //         sleep(1);
        //         printf("child finished");
        //     }
        // }
        // while (waitpid(id, NULL, WNOHANG) > 0)
        // {
        //     printf("finished child\n");
        // }
        // while (1)
        // {
        //     sleep(2);
        //     printf("sleep\n");
        // }
    }
    // char *argv[8];
    // argv[0] = "ls";
    // argv[1] = "-l";
    // argv[2] = NULL;
    // execvp(argv[0],argv);
    // char *input;
    // input = NULL;
    // if(input == NULL){
    //     printf("good");
    // }
    // input = readline("# ");

    // char *args[100]; //"string array"
    // char *piece = strtok(input, " ");
    // int argc = 0;
    // while (piece != NULL)
    // {
    //     args[argc] = piece;
    //     piece = strtok(NULL, " ");
    //     argc++;
    // }

    // char output[10];
    // strcpy(output,input);
    // printf("%s", output);
}