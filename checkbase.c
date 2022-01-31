#include <stdio.h>
#include<sys/types.h>
#include <unistd.h>

int main(){
    FILE* fp = fopen("./F.txt", "r");
    int n = getw(fp);
    fclose(fp);
    printf("%d", n);
/*
    fp = fopen("./p.txt", "r");
    int n = getw(fp);
    printf("starting n: %d\n", n);

    fscanf(fp, "%d", &n);
    printf("starting n: %d\n", n);
    fclose(fp);
    n++;
    printf("n is now: %d", n);

    printf("writing new n");
    fp = fopen("./p.txt", "w+");
    putw(n, fp);
    fclose(fp);    */
}