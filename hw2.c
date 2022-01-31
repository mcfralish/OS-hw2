#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

const char* file_name = "./F.txt";
int nreaders = 0;
bool lock = false;

void process(int counter)
{
    pid_t pid; //process ID
    while (lock){
        sleep(1);
        printf("Locked: %d cannot enter ", pid);
    }
    lock = true;
    FILE* file = fopen(file_name, "r"); //Open file
    int n =  getw(file);//Read number
    //printf("%d\n", n);
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
    lock = false;
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