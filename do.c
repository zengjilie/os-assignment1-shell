#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
int main(int argc, char *argv[])
{

    // for (int i = 0; i < 4; i++)
    // {
    //     printf("%d\n",i);
    //     if(i == 2){
    //         int id1 = fork();
    //         if(id1 == 0){
    //             printf("hello from child1\n");
    //         }else{
    //             wait(NULL);
    //         }
    //     }
    // }
    // int i = 0;
    // for (i = 0; i < 4; i++)
    // {
    //     printf("%d", i);
    //     // if(i == 2){
    //     //     int id1 = fork();
    //     //     if(id1 == 0){
    //     //         printf("hello from child1\n");
    //     //     }else{
    //     //         wait(NULL);
    //     //     }
    //     // }
    // }

    int fd[2];
    pipe(fd);

    int id = fork();
    if (id == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        execlp("cat","cat",NULL);
        exit(0);
    }
    else
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        execlp("ls","ls",NULL);
        wait(NULL);
    }

    // if (pid1 == 0)
    // {
    //     dup2(fd[1], STDOUT_FILENO);
    //     // execlp("ls","ls",NULL);
    //     printf("child text");
    // }
    // waitpid(pid1, NULL, 0);
    // int id = -1;
    // if (id != 0)
    // {
    //     printf("# ");
    // }

    // id = fork();
    // if (id == 0)
    // {
    //     printf("child");
    // }
    // else
    // {
    //     // wait(NULL);
    //     printf("parent");
    // }
    // char input[100];
    // fgets(input, 100, stdin);
    // int id = fork();
    // if(id == 0){
    //     printf("%s",input);
    // }else{
    //     wait(NULL);
    //     printf("gege%s",input);
    // }
    // DIR *dir = opendir(".");
    // if (dir == NULL)
    // {
    //     return 1;
    // }

    // struct dirent *entity;
    // entity = readdir(dir);
    // while (entity != NULL)
    // {
    //     printf("%s\t", entity->d_name);
    //     entity = readdir(dir);
    // }

    // int file = open("text.txt", O_WRONLY);
    // dup2(file, STDOUT_FILENO);
    // // printf("\n");
    // closedir(dir);
    // int file = open(input, O_CREAT | O_WRONLY);

    // dup2 (file, STDOUT_FILENO);
    // printf("this is good");
    // // printf("%d",isSame);
    return 0;
}