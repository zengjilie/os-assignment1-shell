#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    //Int pointers
    // int gege[3] = {1, 2, 3};
    // int length = sizeof gege;

    // int *gegep[] = {1,2,3, NULL};
    // int length2 = sizeof gegep;

    // printf("Length of gege is %d\n",length2);

    //char pointers
    char arr[] = "gege";
    char *arrp = "gege";


    int length = sizeof arrp;

    printf("Length of arr is %d\n",length);
}