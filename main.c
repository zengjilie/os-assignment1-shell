#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// FORK
int main()
{
    char *str = "This is John";
    printf("%p\n", str);
    // printf("%p\n", p);

    return 0;
}
// int main(){
//     int cpid;
//     char * inString;

//     while(inString = readline("cmd:")){
//         cpid = fork();
//         if(cpid == 0){
//             execlp(inString, inString, (char*)NULL);
//         }else{
//             wait((int *)NULL);
//         }
//     }
// }