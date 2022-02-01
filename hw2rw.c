#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

const char* file_name = "./F.txt";
sem_t mutex;

void process()
{
    int counter = 0;
    while(counter < 200){
        pid_t pid; //process ID
        
        sem_wait(&mutex);
        FILE* file = fopen(file_name, "r"); //Open file with read permissions
        char st_n[5];
        fscanf(file, "%s", st_n); //Read number as string
        //printf("%d\n", n);
        fclose(file);
        int n =  atoi(st_n);//Cast to int

        if ((pid = getpid()) < 0){ //get pid
            printf("unable to get pid");
        } else{
            printf("N: %d Proccess ID: %d\n", n, pid);
        }
        n++;
        file = fopen(file_name, "w+");//Open file with write permissions
        sprintf(st_n, "%d", n);
        //itoa(n, st_n, 10);
        //putw(n, file);
        fprintf(file, "%s", st_n);
        fclose(file);
        sem_post(&mutex);
        counter++;
    }
    
}

int main()
{  

    sem_init(&mutex, 1, 1);
    for (int i = 0; i < 3; i++){
        if (fork() == 0){
        printf("Starting Process %d\n", (i+1));
        process(0);
        exit(0);
        }
    }
    sem_destroy(&mutex);
    return 0;
}