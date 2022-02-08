#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

//fileDirection module
int fileDirection()
{
    printf("test\n");
    return 0;
}



//pipe
int pipe(){

}

int main()
{
    while (1)
    {
        // yash shell
        printf("yash$ ");

        // test run
        char text[100];
        fgets(text, 100, stdin);
        text[strlen(text) - 1] = '\0';

        // input parsing -> checkout what's the command you want to exec

        // Command is fileDirection?
        int isFileDir = 0;
        for (int i = 0; i < strlen(text); i++)
        {
            if (text[i] == '>')
            {
                isFileDir = 1;
            }
        }
        if(isFileDir == 0){
            printf("%s\n",text);
        }else{
            fileDirection();
        }


        // Command is pipe?
    }

    return 0;
}
