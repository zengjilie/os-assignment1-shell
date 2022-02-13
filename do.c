#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    FILE *fPointer;
    fPointer = fopen("text.txt", "r");
    char singleLine[150];
    if (fPointer == NULL) // error handling
    {
        printf("No such file in current directory");
    }
    else
    {
        while (!feof(fPointer))
        {
            fgets(singleLine, 150, fPointer);
            printf("%s", singleLine);
        }
        fclose(fPointer);
    }
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