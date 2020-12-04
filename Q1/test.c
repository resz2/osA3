/* Name: Aryan GD Singh
   Roll_Number: 2019459 */

#define _GNU_SOURCE
#include<stdio.h>
#include<sys/time.h>
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
   pid = fork();
   if(pid<0)  {
      perror("fork() error");
      return -1;
   }
   if(pid>0)   {
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
   }
   if(pid>0)   {
      //with soft real time parameters
      printf("process with soft real time parameters : %d\n", getpid());
      double timeTaken;
      struct timeval start, end;
      int temp;
      gettimeofday(&start, NULL);
      // task
      for(int i=0;i<1000000000;i++)
         temp = i;
      gettimeofday(&end, NULL);
      timeTaken = (double)(end.tv_usec - start.tv_usec)/1000 + (double)(end.tv_sec-start.tv_sec)*1000;
      printf("Time taken with = %f\n", timeTaken/1000);
      wait(NULL);
   }
   else  {
      //without soft real time parameters
      printf("process w/o soft real time parameters : %d\n\n", getpid());
      double timeTaken;
      struct timeval start, end;
      int temp;
      gettimeofday(&start, NULL);
      // task
      for(int i=0;i<1000000000;i++)
         temp = i;
      gettimeofday(&end, NULL);
      timeTaken = (double)(end.tv_usec - start.tv_usec)/1000 + (double)(end.tv_sec-start.tv_sec)*1000;
      printf("Time taken w/o = %f\n", timeTaken/1000);
   }
   return 0;
}