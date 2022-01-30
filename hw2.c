#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
const char* file_name = "./F.txt";

void process()
{
    pid_t pid; //process ID
    FILE* file = fopen(file_name, "r"); //Open file
    int n =  getw(file);//Read number
    printf("%d\n", n);
    fclose(file);
    if ((pid = getpid()) < 0){
        printf("unable to get pid");
    } else{
        printf("N: %d Proccess ID: %d\n", n, pid);
    }
    file = fopen(file_name, "w+");
    n++;
    putw(n, file);
    fclose(file);
}

int main()
{  
    if (fork() == 0){
        printf("Starting Process P1\n");
        int i = 0;
        for (int i; i < 5; i++){
            process();
        }
    }
    if (fork() == 0){
        printf("Starting Process P2\n");
        int i = 0;
        for (int i; i < 5; i++){
            process();
        }    }
    if (fork() == 0){
        printf("Starting Process P3\n");
        int i = 0;
        for (int i; i < 5; i++){
            process();
        }
    }
    return 0;
}