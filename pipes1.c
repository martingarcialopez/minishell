#include <stdio.h>
  #include <memory.h>
  #include <unistd.h>
 
  int main( int argc, char ** argv )
  {
   /* create the pipe */
   int  pfd[2];
   if (pipe(pfd) == -1)
     {
       printf("pipe failed\n");
       return 1;
     }
 
   /* create the child */
   int  pid;
   if ((pid = fork()) < 0)
     {
       printf("fork failed\n");
       return 2;
     }
 
   if (pid == 0)
     {
       /* child */
       char buffer[BUFSIZ];
 
       close(pfd[1]); /* close write side */
 
       /* read some data and print the result on screen */
       while (read(pfd[0], buffer, BUFSIZ) != 0)
         printf("child reads %s", buffer);
 
       close(pfd[0]); /* close the pipe */
     }
   else
     {
       /* parent */
       char buffer[BUFSIZ];
 
       close(pfd[0]); /* close read side */
 
       /* send some data into the pipe */
       strcpy(buffer, "HelloWorld\n");
       write(pfd[1], buffer, strlen(buffer)+1);
 
       close(pfd[1]); /* close the pipe */
     }
 
   return 0;
  }
