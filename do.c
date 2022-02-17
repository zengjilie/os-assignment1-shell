#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

int isSigint = 0;
int isSigtstp = 0;
void sigintHandler(int sig)
{
    isSigint = 1;
}

void sigtstpHandler(int sig)
{
    isSigtstp = 1;
}

typedef struct
{
    char name[5];
} animal;

int jobsCount = 2;

struct jobs
{
    char name;
    struct jobs *next;
};

int main(int argc, char *argv[])
{
    // struct jobs *head;

    // struct jobs job1;
    // job1.name = 'A';
    // struct jobs job2;
    // job2.name = 'B';
    // struct jobs job3;
    // job3.name = 'C';

    // job1.next = &job2;
    // job2.next = &job3;
    // job3.next = NULL;

    // head = &job1;
    // while (head != NULL){
    //     printf("%c\n",head->name);
    //     head = head->next;
    // }

    // execlp("sleep", "sleep", "100", NULL);

    // int id = fork();
    // if (id == 0)
    // {
    //     execlp("sleep", "sleep", "100", NULL);
    //     // sleep(100);
    // }
    // else
    // {
    //     // wait(NULL);
    //     // int isFinished = waitpid(id, NULL, WNOHANG);
    //     // int isFinished = waitpid(id, NULL,WIFEXITED(status));
    //     // if (isFinished == 0)
    //     // {
    //     //     printf("child is finished");
    //     // }else{
    //     //     printf("still waiting");
    //     // }
    // }

    // animal ani[100];
    // animal cat1 = {"black"};
    // animal cat2 = {"green"};
    // ani[0] = cat1;
    // ani[1] = cat2;
    // printf("%lu", sizeof ani[3].name);

    // for (int i = 0; i < jobsCount; i++)
    // {
    //     printf("cat1 name is: %s\n", set[i].name);
    // }
    // int jobCount = 0;
    // char index[3] = '[' + jobCount + 1 + '0' + ']';
    // printf("%c", index);

    // while (1)
    // {
    //     sleep(2);
    //     printf("wait\n");
    // }

    // int *pointer = NULL;
    // if (pointer == NULL)
    // {
    //     printf("%p\n", pointer);
    // }

    // int id = fork();
    // if (id == 0) // child
    // {
    //     // while (1)
    //     // {
    //     //     sleep(2);
    //     //     printf("wait\n");
    //     // }
    //     sleep(5);
    //     exit(0);
    // }
    // else // parent
    // {
    //     // signal(SIGINT, sigintHandler);
    //     // if (isSigint == 1)
    //     // {
    //     //     kill(id, SIGINT);
    //     // }
    //     signal(SIGTSTP, sigtstpHandler);
    //     if (isSigtstp == 1)
    //     {
    //         kill(id, SIGTSTP);
    //     }
    //     // waitpid(id, NULL, WUNTRACED);
    //     int parm;
    //     int isFinished = waitpid(id,&parm, WNOHANG);


    //     printf("finished is %d\n", isFinished);
    //     printf("finished is %d\n",parm);

        while (1)
        {
            sleep(2);
            printf("parent sleep\n");
        }
    // }

    // int fd[2];
    // pipe(fd);

    // int id = fork();
    // if (id == 0)
    // {
    //     dup2(fd[0], STDIN_FILENO);
    //     close(fd[1]);
    //     execlp("cat","cat",NULL);
    //     exit(0);
    // }
    // else
    // {
    //     dup2(fd[1], STDOUT_FILENO);
    //     close(fd[0]);
    //     execlp("ls","ls",NULL);
    //     wait(NULL);
    // }

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