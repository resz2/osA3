/* Name: Aryan GD Singh
   Roll_Number: 2019459 */

#define _GNU_SOURCE
#include<stdio.h>
#include<time.h>
#include<errno.h>
#include<unistd.h>
#include<wait.h>
#include<linux/kernel.h>
#include<sys/syscall.h>

#define SYS_rtnice 441

int main()  {
   pid_t pid;
   long input;
   printf("Enter rt_nice value(input will be multiplied by 1000000) :\n");
   scanf("%ld", &input);
   long rtval = input*1000000l;
   long res = syscall(SYS_rtnice, getpid(), rtval);
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
      printf("process with soft real time parameters : %d\n", getpid());
      double timeTaken;
      clock_t start, end;
      int temp;
      start = clock();
      // task
      for(int i=0;i<1000000000;i++)
         temp = i;
      end = clock();
      timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("Time taken with = %f\n", timeTaken);
      wait(NULL);
   }
   else  {
      //without soft real time parameters
      printf("process w/o soft real time parameters : %d\n\n", getpid());
      double timeTaken;
      clock_t start, end;
      int temp;
      start = clock();
      // task
      for(int i=0;i<1000000000;i++)
         temp = i;
      end = clock();
      timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("Time taken w/o = %f\n", timeTaken);
   }
   return 0;
}