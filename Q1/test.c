/* Name: Aryan GD Singh
   Roll_Number: 2019459 */

#include<stdio.h>
#include<time.h>
#include<errno.h>
#include<unistd.h>

int main()  {
   clock_t start, end;
   double timeTaken;
   pid_t pid;
   pid = fork();
   if(pid<0)  {
      perror("fork() error");
   }
   else if(pid==0)   {
      printf("with soft real time parameters\n");
      int temp;
      start = clock();
      // task
      for(int i=0;i<1000000000;i++)
         temp = i;
      end = clock();
      timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("Time taken = %f\n", timeTaken);
   }
   else  {
      printf("without soft real time parameters\n");
      int temp;
      start = clock();
      // task
      for(int i=0;i<1000000000;i++)
         temp = i;
      end = clock();
      timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("Time taken = %f\n", timeTaken);
   }
   return 0;
}