#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//FORMAT SPECIFIER
// int main(){
//     float price = 5.16;
//     printf("Your total price is $%.2f", price);
//     return 0;
// }

// FORK
int main(){
    pid_t pid;
    pid = fork();
    if(pid == 0){
        printf("I am a child %d\n", pid);
    }else{
        printf("I am a parent %d\n" , pid);
    }

    return 0;
}

// int main()
// {
//     int x = 3;
//     if (fork() == 0)
//     {
//         printf("C: x=%d;", --x);
//     }
//     printf("P: x=%d;", ++x);
//     exit(0);
// }

//
int main(){
    int cpid;
    char * inString;

    while(inString = readline("cmd:")){
        cpid = fork();
        if(cpid == 0){
            execlp(inString, inString, (char*)NULL);
        }else{
            wait((int *)NULL);
        }
    }
}