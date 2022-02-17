#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

// == Global variables ==
// Sigint
int isSigint = 0;
void sigintHandler(int sig)
{
    isSigint = 1;
}

// Sigtstp
int isSigtstp = 0;
void sigtstpHandler(int sig)
{
    isSigtstp = 1;
}

// Jobs data type
struct job
{
    // index -> [1]
    // current job -> -/+
    // state -> Running/Stopped
    // name of command -> sleep 5 &
    // pointing to next job
    int pid;
    char index[4];
    char nextFg;
    char state[10];
    char command[2000];
    struct job *next;
};

int jobCount = 0;
// root Jobs
struct job *rootJob = NULL;

int main()
{
    // signal handling
    signal(SIGINT, sigintHandler);
    signal(SIGTSTP, sigtstpHandler);

    // Jobs recorder

    while (1)
    {
        // == Input Parsing ==

        char *input;
        input = readline("# ");

        char command[2000];
        strcpy(command, input);

        //[Warning, strtok will change the input string]
        char *args[100];
        char *piece = strtok(input, " ");
        int argc = 0;
        while (piece != NULL)
        {
            args[argc] = piece;
            piece = strtok(NULL, " ");
            argc++;
        }

        // Checkers
        int hasPipe = 0;       // Pipe checker
        int hasBackground = 0; // Background checker

        for (int i = 0; i < argc; i++)
        {
            if (args[i] == NULL) // stop
            {
                break;
            }
            if (strcmp(args[i], "|") == 0)
            {
                hasPipe = 1;
            }
            if (strcmp(args[i], "&") == 0)
            {
                hasBackground = 1;
            }
        }

        //== Start Process ==

        int id = fork();
        if (id == 0)
        {
            // if there is no pipe, then only one process will be executed
            if (hasPipe == 0)
            {
                for (int i = 1; i < argc; i++)
                {
                    // end of args
                    if (args[i] == NULL)
                    {
                        break;
                    }

                    //== File direction ==

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
                        int file = open(args[i], O_RDONLY); // cat + file
                        if (file == -1)
                        {
                        }
                        dup2(file, STDIN_FILENO);
                    }
                }

                // == Execute ==

                if (strcmp(args[0], "jobs") == 0) // jobs -> shell command
                {
                    struct job *head = rootJob;
                    while (head != NULL)
                    {
                        printf("%s\t", head->index);
                        printf("%c\t", head->nextFg);
                        printf("%s\t\t\t", head->state);
                        printf("%s\n", head->command);
                        head = head->next;
                    }
                }
                else if (strcmp(args[0], "fg") == 0) // fg -> send SIGCONT to the most recent job
                {
                    // kill(allJobs[jobCount].pid, SIGCONT);
                }
                else if (strcmp(args[0], "sleep") == 0) // sleep -> sleep
                {
                    execlp(args[0], args[0], args[1], NULL);
                }
                else
                {
                    execlp(args[0], args[0], NULL);
                }
                exit(0);
            }

            // == Pipe ==

            else if (hasPipe == 1)
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
                        leftArgs[lp] = NULL; // important
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

                // pipe
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

            // == Sigint ==
            if (isSigint == 1)
            {
                kill(id, SIGKILL);
            }

            if (isSigtstp == 1)
            {
                kill(id, SIGTSTP);
            }

            // == Record Jobs ==
            // 1. run in background
            // 2. stopped
            if (hasBackground == 1)
            {
                // == Create New Job ==

                struct job *NewJob = (struct job *)malloc(sizeof(struct job));

                // If threre is not job
                if (jobCount == 0)
                {
                    rootJob = NewJob;
                }
                // If there already are jobs
                else
                {
                    struct job *head = rootJob;

                    while (head->next != NULL)
                    {
                        head->nextFg = '-';
                        head = head->next;
                    }
                    head->nextFg = '-';

                    head->next = NewJob;
                }

                // Add new job content
                jobCount++;
                char index[4];
                index[0] = '[';
                index[1] = jobCount + '0';
                index[2] = ']';
                index[3] = '\0';
                strcpy(NewJob->index, index);
                NewJob->nextFg = '+';             // nextFg
                strcpy(NewJob->state, "Running"); // state
                strcpy(NewJob->command, command); // command
                NewJob->next = NULL;

                // printf("%s\n", allJobs->command);
            }
            else
            {
                waitpid(id, NULL, WUNTRACED);
            }

            if (isSigint == 1)
            {
                printf("\n");
            }

            if (isSigtstp == 1)
            {
                printf("\n");
            }
            isSigtstp = 0;
            isSigint = 0;
        }
    }

    return 0;
}
