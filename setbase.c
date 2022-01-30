#include <stdio.h>
#include <sys/types.h>

int main(){
    FILE* fp = fopen("./F.txt", "w+");
    putw(5, fp);
    fclose(fp);
}