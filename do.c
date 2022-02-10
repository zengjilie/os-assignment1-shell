#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // fgets(input, 100, stdin);
    // input[strlen(input) - 1] = '\0';

    char *strp[10];
    strp[0] = "good";
    strp[1] = ">";
    // printf("%s", strp[0]);
    // printf("%s", strp[1]);
    for (int i = 0; i < sizeof strp / sizeof strp[0]; i++)
    {
        if (strp[i] == NULL)
        {
            break;
        }
        printf("%s\n", strp[i]);
        // printf("%d", i);
    }
    return 0;
}