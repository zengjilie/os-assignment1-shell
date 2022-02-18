#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

int checker = 0;
void handler(int sig)
{
    int child_pid = waitpid(-1, NULL, WUNTRACED);
    printf("finished child %d\n", child_pid);
    return;
}

int sig = 0;
void handler2(int sig)
{
    int child_pid = waitpid(-1, NULL, WUNTRACED);
    printf("%d",child_pid);
    kill(child_pid,SIGTSTP);
    return;
}

int main()
{
    signal(SIGCHLD, handler);
    signal(SIGTSTP, handler2);

    int id = fork();
    if (id == 0)
    {
        while (1)
        {
            sleep(1);
            printf("child1%d\n", getpid());
        }
        exit(0);
    }
    else
    {
        waitpid(id, NULL, WUNTRACED);
        // while (1)
        // {
        //     sleep(1);
        //     printf("parent sleep\n");
        // }
    }

    // if (id2 == 0)
    // {
    //     printf("child2%d\n", getpid());
    // }

    // if (id != 0 || id2 != 0)
    // {
    //     while (1)
    //     {
    //     }
    // }

    // if (id == 0)
    // {
    //     sleep(2);
    //     printf("child finished %d\n", getpid());
    //     exit(0);
    // }
    // else
    // {
    //     pid_t pid;
    //     int status;
    //     waitpid(-1, NULL, WNOHANG);
    //     while (1)
    //     {
    //         sleep(1);
    //         printf("parent run\n");
    //     }
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
    // }

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