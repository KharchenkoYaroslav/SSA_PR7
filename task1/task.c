#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp = popen("rwho | more", "r"); 
    if (fp == NULL)
    {
        perror("popen failed");
        return 1;
    }
    else
    {
        printf("popen succeeded\n");
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp))
    {
        fputs(buffer, stdout);
    }

    pclose(fp);
    return 0;
}
