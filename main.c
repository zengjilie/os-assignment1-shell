#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>

// ls
int listFiles()
{
    DIR *dir = opendir(".");
    if (dir == NULL)
    {
        return 1;
    }

    struct dirent *entity;
    entity = readdir(dir);
    while (entity != NULL)
    {
        printf("%s\t", entity->d_name);
        entity = readdir(dir);
    }

    // printf("\n");
    closedir(dir);
    return 0;
}

// cat

// fileDirection module
// int redirect(char *args[])
// {
//     // looping through the args
//     for (int j = 0; j < sizeof args / sizeof args[0]; j++)
//     {
//         if (args[j] == NULL)
//         {
//             break;
//         }
//         // printf("%s\n", args[j]);
//         // check operator
//         int isGreater = strcmp(args[j], ">");
//         int isSmaller = strcmp(args[j], "<");
//         int isTwoGreater = strcmp(args[j], "2>");

//         if (isGreater == 0)
//         {
//             if (args[j - 1] != NULL && args[j + 1] != NULL) //_ > _
//             {
//                 int file = open(args[j], O_CREAT | O_WRONLY | O_TRUNC);
//             }
//             else
//             {
//                 break;
//             }
//         }
//         else if (isSmaller == 0)
//         {
//             if (args[j - 1] != NULL && args[j + 1] != NULL)
//             {
//             }
//             else
//             {
//                 break;
//             }
//         }
//         else if (isTwoGreater == 0)
//         {
//             if (args[j - 1] != NULL && args[j + 1] != NULL)
//             {
//             }
//             else
//             {
//                 break;
//             }
//         }
//     }

//     return 0;
// }

// pipe
// int pipe()
// {
// }

int main()
{
    while (1)
    {
        // Start
        printf("# ");
        // User input
        char input[100];
        fgets(input, 100, stdin);
        input[strlen(input) - 1] = '\0';

        // Parsing input args
        char *args[100]; //"string array"
        char *piece = strtok(input, " ");
        int i = 0;
        while (piece != NULL)
        {
            args[i] = piece;
            piece = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL; // manually add null

        // checking all args

        int id = fork();
        if (id == 0)
        {
            for (int j = 0; j < sizeof args / sizeof args[0]; j++)
            {
                if (args[j] == NULL) // stop
                {
                    break;
                }
                else if (strcmp(args[j], "ls") == 0) // list files
                {
                    // hasLs = 1;
                    listFiles();
                }
                else if (strcmp(args[j], "cat") == 0)// jump over <
                {
                    FILE *fPointer;
                    if (strcmp(args[j + 1], "<") == 0)
                    {
                        fPointer = fopen(args[j + 2], "r");
                        j++;
                    }else{
                        fPointer = fopen(args[j + 1], "r");
                    }
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
                    }
                }
                else if (strcmp(args[j], "<") == 0)
                {
                    // hasRedir = 1;
                    if (args[j + 1] == NULL || strcmp(args[j + 1], "ls") == 0 || strcmp(args[j + 1], "cat") == 0)
                    {
                        break;
                    }
                    else
                    {
                        int file = open(args[j + 1], O_RDONLY);
                        if (file == -1)
                        {
                            printf("File doesn't exist in current directory");
                            break;
                        }
                        dup2(file, STDIN_FILENO);
                        close(file);
                    }
                }

                else if (strcmp(args[j], ">") == 0)
                {
                    // hasRedir = 1;
                    if (args[j + 1] == NULL || strcmp(args[j + 1], "ls") == 0 || strcmp(args[j + 1], "cat") == 0)
                    {
                        break;
                    }
                    else
                    {
                        int file = open(args[j + 1], O_CREAT | O_TRUNC | O_WRONLY);
                        if (file == -1)
                        {
                            break;
                        }
                        dup2(file, STDOUT_FILENO);
                        close(file);
                    }
                }

                else if (strcmp(args[j], "2>") == 0)
                {
                    // hasRedir = 1;
                    if (args[j + 1] == NULL || strcmp(args[j + 1], "ls") == 0 || strcmp(args[j + 1], "cat") == 0)
                    {
                        break;
                    }
                    else
                    {
                        int file = open(args[j + 1], O_CREAT | O_TRUNC | O_WRONLY);
                        if (file == -1)
                        {
                            break;
                        }
                        dup2(file, STDERR_FILENO);
                    }
                }
                else
                {
                    printf("");
                }

                if (strcmp(args[j], "|") == 0)
                {
                    int fd[2];
                    if(pipe(fd) == -1){

                    }

                }
                printf("%d",j);
            }
            // printf("\n");
            break;
        }
        else
        {
            wait(NULL);
            printf("\n");
        }

        // list
        // if (hasLs== 1 && hasRedir== 0)
        // {
        //     listFiles();
        // }

        // // Redirection
        // if (hasLs== 1 && hasRedir== 1)
        // {
        //     redirect(args);
        // }

        // // Pipe
        // if(hasPipe){
        //     doPipe(args);
        // }
    }

    return 0;
}
