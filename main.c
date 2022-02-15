#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    while (1)
    {
        // Start
        // User input
        char *input;
        input = readline("# ");

        // seperate args by space
        char *args[100]; //"string array"
        char *piece = strtok(input, " ");
        int p = 0;
        while (piece != NULL)
        {
            args[p] = piece;
            piece = strtok(NULL, " ");
            p++;
        }
        args[p] = NULL; // manually add null

        int hasPipe = 0; // check if has pipe
        for (int i = 0; i < sizeof args / sizeof args[0]; i++)
        {
            if (args[i] == NULL) // stop
            {
                break;
            }
            if (strcmp(args[i], "|") == 0)
            {
                hasPipe = 1;
            }
        }

        int id = fork(); // start process
        if (id == 0)
        {
            // if there is no pipe, then only one process will be executed
            if (hasPipe == 0)
            {
                for (int i = 1; i < sizeof args / sizeof args[0]; i++)
                {
                    // end of args
                    if (args[i] == NULL)
                    {
                        break;
                    }

                    // file direction
                    if (strcmp(args[i], ">") == 0) // >
                    {
                        int file = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC);
                        if (file == -1)
                        {
                        }
                        dup2(file, STDOUT_FILENO);
                    }
                    else if (strcmp(args[i], "<") == 0) // <
                    {
                        int file = open(args[i + 1], O_RDONLY);
                        if (file == -1)
                        {
                        }
                        dup2(file, STDIN_FILENO);
                    }
                    else if (strcmp(args[i - 1], "cat") == 0)
                    {
                        int file = open(args[i], O_RDONLY); // cat file
                        if (file == -1)
                        {
                        }
                        dup2(file, STDIN_FILENO);
                    }
                }
                execlp(args[0], args[0], NULL);
                exit(0);
            }
            else if (hasPipe == 1) // has pipe
            {
                // seperate args between left | right
                char *leftArgs[100];
                char *rightArgs[100];
                int lp = 0;
                int rp = 0;
                int partition = 0;
                for (int i = 0; i < sizeof args / sizeof args[0]; i++)
                {
                    if (args[i] == NULL)
                    {
                        rightArgs[rp] = NULL;
                        break;
                    }

                    if (strcmp(args[i], "|") == 0)
                    { // reached |
                        partition = 1;
                        leftArgs[lp] = NULL;//important
                        continue;
                    }

                    if (partition == 0) // haven't reach |
                    {
                        leftArgs[lp] = args[i];
                        lp++;
                    }
                    else if (partition == 1)
                    { // reached |
                        rightArgs[rp] = args[i];
                        rp++;
                    }
                }

                //pipe
                int fd[2];
                // error handling
                //  if(pipe(fd) );
                pipe(fd);
                int id2 = fork();
                if (id2 == 0) // child
                {
                    dup2(fd[0], STDIN_FILENO);
                    close(fd[1]);
                    // execute all right args
                    for (int i = 1; i < sizeof rightArgs / sizeof rightArgs[0]; i++)
                    {
                        // end of args
                        if (rightArgs[i] == NULL)
                        {
                            break;
                        }

                        // file direction
                        if (strcmp(rightArgs[i], ">") == 0) // >
                        {
                            int file = open(rightArgs[i + 1], O_WRONLY | O_CREAT | O_TRUNC);
                            if (file == -1)
                            {
                            }
                            dup2(file, STDOUT_FILENO);
                        }
                        else if (strcmp(rightArgs[i], "<") == 0) // <
                        {
                            int file = open(rightArgs[i + 1], O_RDONLY);
                            if (file == -1)
                            {
                            }
                            dup2(file, STDIN_FILENO);
                        }
                        else if (strcmp(rightArgs[i - 1], "cat") == 0)
                        {
                            int file = open(rightArgs[i], O_RDONLY); // cat file
                            if (file == -1)
                            {
                            }
                            dup2(file, STDIN_FILENO);
                        }
                    }
                    execlp(rightArgs[0], rightArgs[0], NULL);
                    exit(0);
                }
                else // parent
                {
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[0]);
                    // execue all left args
                    for (int i = 1; i < sizeof leftArgs / sizeof leftArgs[0]; i++)
                    {
                        // end of args
                        if (leftArgs[i] == NULL)
                        {
                            break;
                        }

                        // file direction
                        if (strcmp(leftArgs[i], ">") == 0) // >
                        {
                            int file = open(leftArgs[i + 1], O_WRONLY | O_CREAT | O_TRUNC);
                            if (file == -1)
                            {
                            }
                            dup2(file, STDOUT_FILENO);
                        }
                        else if (strcmp(leftArgs[i], "<") == 0) // <
                        {
                            int file = open(leftArgs[i + 1], O_RDONLY);
                            if (file == -1)
                            {
                            }
                            dup2(file, STDIN_FILENO);
                        }
                        else if (strcmp(leftArgs[i - 1], "cat") == 0)
                        {
                            int file = open(leftArgs[i], O_RDONLY); // cat file
                            if (file == -1)
                            {
                            }
                            dup2(file, STDIN_FILENO);
                        }
                    }
                    execlp(leftArgs[0], leftArgs[0], NULL);
                    wait(NULL);
                }
            }
        }
        else
        {
            // parent wait for child
            wait(NULL);
        }
       
    }

    return 0;
}
