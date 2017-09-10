#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char str[36] = {0};
    char *input;

    input = malloc(36);
    memset(input, 0, 36);

    printf("input str:");
    scanf("%s", input);

    sscanf(input, "%s", str);
    printf("======= %s =======\n",str);

    sscanf(input , "%3s" , str) ;
    printf("======= %s =======\n",str);

    sscanf(input , "%[a-z]" , str) ;
    printf("======= %s =======\n",str);

    sscanf(input , "%[^a-z]" , str) ;
    printf("======= %s =======\n",str);
    
    int a = INT_MAX;
    printf("%d", a + INT_MAX);

    free(input);
    return 0;
}