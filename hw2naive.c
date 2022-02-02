#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

const char* file_name = "./F.txt";


void process()
{
    int counter = 0;
    while(counter < 200){
        pid_t pid; //process ID
        int n;

        FILE* file = fopen(file_name, "r"); //Open file with read permissions
        fscanf(file, "%d", &n); //Read number
        fclose(file);

        if ((pid = getpid()) < 0){ //get pid
            printf("unable to get pid");
        } else{
            printf("N: %d Proccess ID: %d\n", n, pid);
        }
        n++;
        file = fopen(file_name, "r+");//Open file with write permissions
        fprintf(file, "%d", n);
        fclose(file);
        
        counter++;
    }
    
}

int main()
{  
    if (fork() == 0){
       printf("Starting Process 2\n");
       if (fork() == 0){
          printf("Starting Process 3\n");
       }
    }

    process();
    /*for (int i = 0; i < 3; i++){
        if (fork() == 0){
            printf("Starting Process %d\n", (i+1));
            process(0);
            exit(0);
        }
    }*/
    return 0;
}