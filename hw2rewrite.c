#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sysexits.h>




const char* file_name = "./F.txt";
//sem_t mutex;
sem_t* mutex;




void process()
{
    int counter = 0;
    while(counter < 200){
        pid_t pid; //process ID
        int n;
        sem_wait(mutex);
        FILE* file = fopen(file_name, "r"); //Open file with read only permissions
        fscanf(file, "%d", &n); //Read number
        fclose(file);

        if ((pid = getpid()) < 0){ //get pid
            printf("unable to get pid");
        } else{
            printf("N: %d Proccess ID: %d\n", n, pid);
        }
        n++;
        file = fopen(file_name, "r+");//Open file with read and write permissions
        fprintf(file, "%d", n);
        fclose(file);
        sem_post(mutex);
        counter++;
    }
    
}

int main()
{  
    /*https://stackoverflow.com/questions/8707857/error-expected-declaration-or-statement-at-end-of-input-in-c
      user: PSkocik
      
      I am not sure if there is a simpler way to do the memory
      allocation for the semaphore, but if so, feedback appreciated.
      I was unable to get it to work correctly with:
      sem_init(&mutex, 1, 1);
      when I had initialized mutex as:
      sem_t mutex;*/
    mutex = (sem_t*)mmap(0, sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED, 0, 0 );
        if ((void*)mutex == MAP_FAILED) { perror("mmap");  exit(EX_OSERR);}

    sem_init(mutex, 1, 1);
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
    sem_destroy(mutex);
    return 0;
}