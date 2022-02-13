#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    int file = open("text4.txt", O_WRONLY);
    dup2(file, STDERR_FILENO);
    fprintf(stderr,"err");
    // int fd[2];
    // int p = pipe(fd);

    // int pid1 = fork();
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