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
    signal(SIGCHLD, sigchildHandler);
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

        int pipeIndex = 0;
        int hasBackground = 0;
        while (piece != NULL)
        {
            args[argc] = piece;

            if (strcmp(piece, "|") == 0) // check if there is a pipe
            {
                pipeIndex = argc;
            }

            if (strcmp(piece, "&") == 0) // check if there is a background
            {
                hasBackground = 1;
            }

            piece = strtok(NULL, " ");
            argc++;
        }

        // Building commands
        char *commandsL[50]; // Left commands
        char *commandsR[50]; // Right commands
        if (pipeIndex == 0)
        { // No pipe
            int findPartition = 0;
            for (int i = 0; i < argc; i++)
            {
                if (strcmp(args[i], ">") != 0 && strcmp(args[i], "<") != 0 && strcmp(args[i], "2>") != 0)
                {
                    if (findPartition == 0)
                    {
                        commandsL[i] = args[i];
                    }
                }
                else
                {
                    findPartition = 1;
                    commandsL[i] = NULL;
                }
            }
            if (findPartition == 0)
            {
                commandsL[argc] = NULL;
            }
        }
        else
        { // Has pipe
            int findPartitionLeft = 0;
            for (int i = 0; i < pipeIndex; i++)
            {
                if (strcmp(args[i], ">") != 0 && strcmp(args[i], "<") != 0 && strcmp(args[i], "2>") != 0)
                {
                    if (findPartitionLeft == 0)
                    {
                        commandsL[i] = args[i];
                    }
                }
                else
                {
                    findPartitionLeft = 1;
                    commandsL[i] = NULL;
                }
            }
            if (findPartitionLeft == 0)
            {
                commandsL[pipeIndex] = NULL;
            }

            int findPartitionRight = 0;
            for (int i = pipeIndex + 1; i < argc; i++)
            {
                if (strcmp(args[i], ">") != 0 && strcmp(args[i], "<") != 0 && strcmp(args[i], "2>") != 0)
                {
                    if (findPartitionRight == 0)
                    {
                        commandsR[i - pipeIndex - 1] = args[i];
                    }
                }
                else
                {
                    findPartitionRight = 1;
                    commandsR[i - pipeIndex - 1] = NULL;
                }
            }
            if (findPartitionRight == 0)
            {
                commandsR[argc - pipeIndex - 1] = NULL;
            }
        }

        // pipe test
        //  ls | cat
        // cat < t.txt | cat < t.txt
        // printf("%d\n", pipeIndex);    //->3
        // printf("%d\n", argc);         //->5
        // printf("%s\n", commandsL[0]); //->sleep
        // printf("%s\n", commandsL[1]); //-> 10
        // printf("%s\n", commandsR[0]); //-> cat
        // printf("%s\n", commandsR[1]); // -> null

        //== Start Process ==

        int id = fork();
        if (id == 0)
        {
            // If there is no pipe, then only one process will be executed -> commandL
            if (pipeIndex == 0)
            {
                for (int i = 0; i < argc; i++)
                {
                    //== File direction ==

                    if (strcmp(args[i], ">") == 0) // >
                    {
                        int file = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC);
                        dup2(file, STDOUT_FILENO);
                    }
                    else if (strcmp(args[i], "<") == 0) // <
                    {
                        int file = open(args[i + 1], O_RDONLY);
                        dup2(STDOUT_FILENO, STDERR_FILENO);
                        dup2(file, STDIN_FILENO);
                    }
                    else if (strcmp(args[i], "2>") == 0) // 2>
                    {
                        int file = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC);
                        dup2(file, STDERR_FILENO);
                    }
                }

                if (strcmp(commandsL[0], "jobs") != 0 && strcmp(commandsL[0], "bg") != 0 && strcmp(commandsL[0], "fg") != 0)
                {
                    if (strcmp(commandsL[0], "sleep") == 0)
                    {
                        execlp(commandsL[0], commandsL[0], commandsL[1], NULL);
                    }
                    else
                    {
                        execvp(commandsL[0], commandsL);
                    }
                    exit(0);
                }
            }

            // == Pipe ==

            else
            {
                // commandsL
                // commandsR
                // pipeIndex
                //  pipe

                int fd[2];
                pipe(fd);

                // Right Pipe
                int id2 = fork();
                if (id2 == 0)
                {
                    // == Right Commands ==
                    dup2(fd[0], STDIN_FILENO);
                    close(fd[1]);
                    for (int i = pipeIndex + 1; i < argc; i++)
                    {
                        //== File direction ==
                        if (strcmp(args[i], ">") == 0) // >
                        {
                            int file = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC);
                            dup2(file, STDOUT_FILENO);
                        }
                        else if (strcmp(args[i], "<") == 0) // <
                        {
                            int file = open(args[i + 1], O_RDONLY);
                            dup2(STDOUT_FILENO, STDERR_FILENO);
                            dup2(file, STDIN_FILENO);
                        }
                        else if (strcmp(args[i], "2>") == 0) // 2>
                        {
                            int file = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC);
                            dup2(file, STDERR_FILENO);
                        }
                    }

                    if (strcmp(commandsR[pipeIndex + 1], "sleep") == 0)
                    {
                        execlp(commandsR[pipeIndex + 1], commandsR[pipeIndex + 2], commandsR[pipeIndex + 2], NULL);
                    }
                    else
                    {
                        execvp(commandsR[0], commandsR);
                    }
                    exit(0);
                }
                else // Parent
                {
                    //== Left Commands ==
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[0]);
                    for (int i = 0; i < pipeIndex; i++)
                    {
                        //== File direction ==
                        if (strcmp(args[i], ">") == 0) // >
                        {
                            int file = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC);
                            dup2(file, STDOUT_FILENO);
                        }
                        else if (strcmp(args[i], "<") == 0) // <
                        {
                            int file = open(args[i + 1], O_RDONLY);
                            dup2(STDOUT_FILENO, STDERR_FILENO);
                            dup2(file, STDIN_FILENO);
                        }
                        else if (strcmp(args[i], "2>") == 0) // 2>
                        {
                            int file = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC);
                            dup2(file, STDERR_FILENO);
                        }
                    }
                    execvp(commandsL[0], commandsL);
                    // wait(NULL);
                }
            }
        }

        // == Parent Process ==
        else
        {
            //== Job Control==
            if (strcmp(commandsL[0], "jobs") == 0) // jobs -> shell command
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
            else if (strcmp(commandsL[0], "fg") == 0) // fg -> send SIGCONT to the most recent job
            {
                // 1. get the most recent job's pid
                // 2. send a SIGCONT to it
                // 3. print the name of the process
                struct job *head = rootJob;
                while (head->next != NULL)
                {
                    head = head->next;
                }
                int recentPid = head->pid;
                kill(recentPid, SIGCONT);
                // waitpid(recentPid,WCONTINUED);
                printf("%s\n", head->command);
            }
            else if (strcmp(commandsL[0], "bg") == 0) // bg ->
            {
                // 1. get the most recent stopped job's pid
                // 2. send a SIGCONT to it
                // 3. print the name of the process

                struct job *head2 = rootJob;
                struct job *recentStoppedJob;
                while (head2 != NULL)
                {
                    if (strcmp(head2->state, "Stopped") == 0)
                    {
                        recentStoppedJob = head2;
                    }
                    head2 = head2->next;
                }

                printf("%s\n", recentStoppedJob->command);
                kill(head2->pid, SIGCONT);
            }
            // == Sigint ==
            if (isSigint == 1)
            {
                kill(id, SIGKILL);
            }

            if (isSigtstp == 1)
            {
                // 1. Stop a process
                // 2. Add to jobs, with state "Stopped"
                kill(id, SIGTSTP);
            }

            // == Record Jobs ==
            // 1. run in background
            // 2. stopped

            if (hasBackground == 1)
            {
                // == Create New Job ==

                struct job *NewJob = (struct job *)malloc(sizeof(struct job));

                if (jobCount == 0) // If threre is not job
                {
                    rootJob = NewJob;
                }

                else // If there already are jobs
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

                waitpid(-1, NULL, WNOHANG);
                // printf("%s\n", allJobs->command);
            }
            else
            {
                waitpid(-1, NULL, WUNTRACED);
            }

            if (isSigint == 1)
            {
                printf("\n");
            }

            if (isSigtstp == 1)
            {
                printf("\n");

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
                strcpy(NewJob->state, "Stopped"); // state
                strcpy(NewJob->command, command); // command
                NewJob->next = NULL;
            }
            isSigtstp = 0;
            isSigint = 0;
        }
    }

    return 0;
}
