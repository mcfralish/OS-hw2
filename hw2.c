#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
const char* file_name = "./read.txt";

void process()
{
    pid_t pid; //process ID
    FILE* file = fopen(file_name, "r"); //Open file
    int N = 0;
    fscanf (file, "%d", &N); //Read number
    fclose(file);
    if ((pid = getpid()) < 0){
        printf("unable to get pid");
    } else{
        printf("N: %d Proccess ID: %d\n", N, pid);
    }
    file = fopen(file_name, "w");
    N++;
    putw(N, file);
    fflush(file);
    fclose(file);
}

int main()
{
    if (fork() == 0){
        printf("Starting Process P1\n");
        process();
    }
    if (fork() == 0){
        printf("Starting Process P2\n");
        process();
    }
    if (fork() == 0){
        printf("Starting Process P3\n");
        process();
    }
    return 0;
}