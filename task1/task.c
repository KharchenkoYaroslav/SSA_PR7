#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = popen("more", "w");  
    if (fp == NULL) {
        perror("popen failed");
        return 1;
    }

    FILE *rwho_fp = popen("rwho", "r");
    if (rwho_fp == NULL) {
        perror("popen rwho failed");
        pclose(fp);
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), rwho_fp)) {
        fputs(buffer, fp);  
    }

    pclose(rwho_fp); 
    pclose(fp);       
    return 0;
}