#include <stdio.h> 
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h> 
#include <time.h>
#include <stdlib.h>

// Parent process instructions

int main(){
    //Before forking, print out some initial message
    printf("Parent message: Before forking\n");

    int parent, child;

    //Forks off 2 child processes
    parent = fork();
    if(parent){
        parent = fork();
    }
    //After the fork, wait for any child to finish
    //Once a child has finished, print out the pid of the completed child as well as how many seconds it was asleep for.
    //Do not run any kind of timer, think about how the child could send this information back to the parent.
    //Print a message that the parent is done and then end the program
    //The other child might still be running, that’s ok.
    if(parent){
        int status;
        child = wait(&status);
        printf("Child with PID %d is finished and took %d seconds\n", child, status >> 8);
        printf("Parent is finished\n");

        return 0;
    }

    //Child process instructions:
    //At the start print its pid
    //Sleep for a random number of seconds in the range [2, 10]
    //Each child should sleep for a (potentially) different amount of seconds
    //At the end print a message that it is finished
    else{
        printf("Child with PID %d is running\n", getpid());

        srand(time(NULL));
        int sleep_time = rand() % 8 + 2;
        sleep(sleep_time);

        printf("Child with PID %d is finished\n", getpid());
 
        return sleep_time;
    }

}