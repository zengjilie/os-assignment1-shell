#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

int main()
{
    // void delete_zombies(void)
    // {
    //     pid_t kidpid;
    //     int status;

    //     printf("Inside zombie deleter:  ");
    //     while ((kidpid = waitpid(-1, &status, WNOHANG)) > 0)
    //     {
    //         printf("Child %ld terminated\n", kidpid);
    //     }
    //     siglongjmp(env, 1);
    // }

    int id = fork();
    if (id == 0)
    {
        sleep(4);
        exit(2);
    }
    else
    {
        pid_t pid;
        int status;
        pid = (waitpid(id, &status, WNOHANG));
        while (pid > 0)
        {
            sleep(4);
            if (id == 0)
            {
                sleep(1);
                printf("child running");
            }
            else if (id > 0)
            {
                sleep(1);
                printf("child finished");
            }
        }
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