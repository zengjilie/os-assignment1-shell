#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // fgets(input, 100, stdin);
    // input[strlen(input) - 1] = '\0';

    // char *strp[10];
    char string[100];
    fgets(string, 100, stdin);
    string[strlen(string)-1] = '\0';

    char *piece = strtok(string, " ");
    // int i = 0;
    while (piece != NULL)
    {
        // args[i] = piece;
        printf("%s\n", piece);
        piece = strtok(NULL, " ");
        // i++;
    }
    // for (int i = 0; i < sizeof strp / sizeof strp[0]; i++)
    // {
    //     if (strp[i] == NULL)
    //     {
    //         break;
    //     }
    //     printf("%s\n", strp[i]);
    // }
    return 0;
}