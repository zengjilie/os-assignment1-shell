#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

int main()
{
    char *input;
    input = NULL;
    if(input == NULL){
        printf("good");
    }
    // input = readline("# ");

    // char *args[100]; //"string array"
    // char *piece = strtok(input, " ");
    // int argc = 0;
    // while (piece != NULL)
    // {
    //     args[argc] = piece;
    //     piece = strtok(NULL, " ");
    //     argc++;
    // }

    // char output[10];
    // strcpy(output,input);
    // printf("%s", output);
}