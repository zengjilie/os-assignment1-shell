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
        char err[100];
        if (id == 0)
        {
            for (int j = 0; j < sizeof args / sizeof args[0]; j++)
            {
                if (args[j] == NULL) // stop
                {
                    break;
                }
                else if (strcmp(args[j], "ls") == 0) // ls
                {
                    // hasLs = 1;
                    listFiles();
                }
                else if (strcmp(args[j], "cat") == 0) // cat
                {
                    char buffer[200];
                    int file;
                    if (strcmp(args[j + 1], "<") == 0) // cat < __
                    {
                        file = open(args[j + 2], O_RDONLY);
                        j++;
                    }
                    else if (args[j + 1] == NULL) // cat
                    {
                        file = -1;
                    }
                    else // cat __
                    {
                        file = open(args[j + 1], O_RDONLY);
                    }

                    if (file == -1) // open file fail
                    {
                        // printf("");
                        strcpy(err,"No such file in current directory");
                    }
                    else // open successfully
                    {
                        dup2(file, STDIN_FILENO);
                        while (fgets(buffer, sizeof(buffer), stdin)) // print stdin
                        {
                            printf("%s", buffer);
                        }
                        close(file);
                    }
                }

                else if (strcmp(args[j], "<") == 0)// <
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

                else if (strcmp(args[j], ">") == 0)// >
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
                        close(file);
                    }
                }

                else if (strcmp(args[j], "2>") == 0) // 2>
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
                        fprintf(stderr,"%s",err);
                        close(file);
                    }
                }
                else
                {
                    printf("");
                }

                if (strcmp(args[j], "|") == 0)
                {
                    int fd[2];
                    if (pipe(fd) == -1)
                    {
                        break;
                    }
                    if (id == 0)
                    {
                    }
                }
            }
            // printf("\n");
            break;
        }
        else
        {
            wait(NULL);
            printf("\n");
        }
    }

    return 0;
}
