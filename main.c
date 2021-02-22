// File: main.c (For CMSC 412 Homework 2)
// Author: John Kucera
// Date: January 22, 2021
// Purpose: This C Program is designed to create 3 processes using the fork() method, have them wait for child creation, and have each process print their PIDs.

// import necessary C libraries
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

// main() function
int main() {
  
  // Variable initialization
  int pid, status;
  pid = getpid(); // Process G

  // Process creation (P)
  switch(fork()) {

    // Error checking
    case -1:
      printf("Fork error: G/P"); 
      break;

    // Process P
    case 0:  
      // Process creation (C)
      switch(fork()) {

        // Error checking
        case -1: 
          printf("Fork error: P/C"); 
          break;

        // Process C
        case 0:  
          printf("I am the child process C and my pid is %d. My parent P has pid %d. My grandparent G has pid %d.\n", getpid(), getppid(), pid); 
          break;

        // Process P
        default:
          wait(&status); // wait for C to finish excecution
          printf("I am the parent process P and my pid is %d. My parent G has pid %d.\n", getpid(), pid);
          break;
      } // end of inner switch
      break;

    // Process G
    default: 
      wait(&status); // wait for P to finish execution
      printf("I am the grandparent process G and my pid is %d.\n", pid);
    } // end of outer switch
} // end of main() function
