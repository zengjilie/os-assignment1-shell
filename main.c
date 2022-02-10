#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

// fileDirection module
int redirect(char input[])
{
    // Seperate by whitespace
    char *args[1000]; //"string array"
    char *piece = strtok(input, " ");
    int i = 0;
    while (piece != NULL)
    {
        args[i] = piece;
        piece = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL; // where to stop

    // looping through the command piece
    for (int j = 0; j < sizeof args / sizeof args[0]; j++)
    {
        if (args[j] == NULL)
        {
            break;
        }
        // printf("%s\n", args[j]);
        // encounter >  or < -> check if it has stdin && stdout

        // if (strcmp(args[j], ">") == 0)
        // {
        //     printf("found >\n");
        // }
        // if (strcmp(args[j], "<") == 0)
        // {
        //     printf("found <\n");
        // }

    }

    return 0;
}

// pipe
// int pipe()
// {
// }

int main()
{
    while (1)
    {
        // yash shell
        printf("yash$ ");

        // take user input
        char input[100];
        fgets(input, 100, stdin);
        input[strlen(input) - 1] = '\0';

        // input parsing

        // Redirection
        int isRedirection = 0;
        for (int i = 0; i < strlen(input); i++)
        {
            if (input[i] == '>' || input[i] == '<')
            {
                isRedirection = 1;
            }
        }
        if (isRedirection == 1)
        {
            redirect(input);
        }

        // Pipe
    }

    return 0;
}
