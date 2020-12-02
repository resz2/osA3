/* Name: Aryan GD Singh
   Roll_Number: 2019459 */

#define _GNU_SOURCE
#include<stdio.h>
#include<time.h>
#include<errno.h>
#include<unistd.h>
#include<wait.h>
#include <sys/syscall.h>

#define SYS_rtnice 441

int main()  {
   double timeTaken;
   pid_t pid;
   long res = syscall(441, getpid(), -1);
   printf("process %d has been modified\n\n", getpid());
   if(errno==EIO) {
      perror("invalid input");
      return -1;
   }
   if(errno==ESRCH)  {
      perror("no such process");
      return -1;
   }
   pid = fork();
   if(pid<0)  {
      perror("fork() error");
      return -1;
   }
   else if(pid>0)   {
      //with soft real time parameters
      printf("with %d\n", getpid());
      clock_t start, end;
      int temp;
      start = clock();
      // task
      for(int i=0;i<1000000000;i++)
         temp = i;
      end = clock();
      timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("Time taken with = %f\n", timeTaken);
   }
   else  {
      //without soft real time parameters
      printf("w/o %d\n", getpid());
      clock_t start, end;
      int temp;
      start = clock();
      // task
      for(int i=0;i<1000000000;i++)
         temp = i;
      end = clock();
      timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("Time taken w/o = %f\n", timeTaken);
      //wait(NULL);
   }
   return 0;
}