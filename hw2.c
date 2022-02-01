#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

const char* file_name = "./F.txt";

void process(int counter)
{
    pid_t pid; //process ID
    
    FILE* file = fopen(file_name, "r"); //Open file
    char st_n[5];
    fscanf(file, "%s", st_n);
    //printf("%d\n", n);
    fclose(file);
    int n =  atoi(st_n);//Read number

    if ((pid = getpid()) < 0){
        printf("unable to get pid");
    } else{
        printf("N: %d Proccess ID: %d\n", n, pid);
    }
    file = fopen(file_name, "w+");
    n++;
    sprintf(st_n, "%d", n);
    //itoa(n, st_n, 10);
    //putw(n, file);
    fprintf(file, "%s", st_n);
    fclose(file);
    counter++;
    if (counter<200){
        process(counter);
    }
}

int main()
{  
        for (int i = 0; i < 3; i++){
        if (fork() == 0){
        printf("Starting Process %d\n", (i+1));
        process(0);
        exit(0);
        }
    }
        return 0;
}