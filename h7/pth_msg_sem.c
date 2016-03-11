/* File:     pth_msg_sem1.c
 *
 * Purpose:  Illustrate a synchronization problem with pthreads:  create 
 *           some threads, each of which creates a message and "sends" it
 *           to another thread, by copying it into that thread's buffer.
 *           This version uses long ints to implement semaphores and
 *           x86 atomic xchg to solve the synchronization problem.
 *
 * Input:    none
 * Output:   message from each thread
 *
 * Compile:  gcc -g -Wall -o pth_msg_sem1 pth_msg_sem1.c msg_sem.s -lpthread
 * Usage:    pth_msg_sem1 <thread_count>
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const int MSG_MAX = 100;

/* Global variables:  accessible to all threads */
int thread_count;
char** messages;
long* sems;

void Usage(char* prog_name);
void *Send_msg(void* rank);  /* Thread function */

/* These should be written using x86 assembler */
void Sem_post(long* sem);
void Sem_wait(long* sem);

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles; 

   if (argc != 2) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   if (thread_count <= 0) Usage(argv[0]);

   thread_handles = malloc (thread_count*sizeof(pthread_t));
   messages = malloc(thread_count*sizeof(char*));
   sems = malloc(thread_count*sizeof(long));
   for (thread = 0; thread < thread_count; thread++) {
      messages[thread] = NULL;
      /* Initialize all semaphores to 0 -- i.e., locked */
      sems[thread] = 0;
   }

   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], (pthread_attr_t*) NULL,
          Send_msg, (void*) thread);

   for (thread = 0; thread < thread_count; thread++) {
      pthread_join(thread_handles[thread], NULL);
   }

   for (thread = 0; thread < thread_count; thread++) {
      free(messages[thread]);
   }
   free(messages);
   free(sems);
   free(thread_handles);

   return 0;
}  /* main */


/*--------------------------------------------------------------------
 * Function:    Usage
 * Purpose:     Print command line for function and terminate
 * In arg:      prog_name
 */
void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
}  /* Usage */


/*-------------------------------------------------------------------
 * Function:       Send_msg
 * Purpose:        Create a message and ``send'' it by copying it
 *                 into the global messages array.  Receive a message
 *                 and print it.
 * In arg:         rank
 * Global in:      thread_count
 * Global in/out:  messages, semaphores
 * Return val:     Ignored
 * Note:           The my_msg buffer is freed in main
 */
void *Send_msg(void* rank) {
   long my_rank = (long) rank;
   long dest = (my_rank + 1) % thread_count;
   char* my_msg = (char*) malloc(MSG_MAX*sizeof(char));

   sprintf(my_msg, "Hello to %ld from %ld", dest, my_rank);
   messages[dest] = my_msg;
   Sem_post(&sems[dest]);     /* "Unlock" the semaphore of dest */

   Sem_wait(&sems[my_rank]);  /* Wait for our semaphore to be unlocked */
   printf("Thread %ld > %s\n", my_rank, messages[my_rank]);

   return NULL;
}  /* Send_msg */