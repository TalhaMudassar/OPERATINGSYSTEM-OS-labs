#include <stdio.h>
#include <sys/wait.h> /* contains prototype for wait*/
#include <stdlib.h>
#include <unistd.h> /* contains fork prototype */
int main(int argc , char * argv [])
{
pid_t pid;
int status=0;
printf("Hello World!\n");
pid = fork( );
if (pid <0) /* check for error in fork */
{
perror("bad fork");
exit(-1);
}
if (pid == 0)
{
printf("I am the child process.\n");
}
else
{
wait(&status); /* parent waits for child to finish */
printf("I am the parent process.\n");
}
}