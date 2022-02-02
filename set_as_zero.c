#include <stdio.h>
#include <sys/types.h>

int main(){
    FILE* fp = fopen("./F.txt", "w+");
    fprintf(fp, "0");
    fclose(fp);
}