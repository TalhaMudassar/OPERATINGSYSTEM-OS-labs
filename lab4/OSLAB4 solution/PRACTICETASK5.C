#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* contains fork prototype */
int main ( )
{
pid_t pid ;
pid = fork();
if ( pid > 0 ) /* pid is non-zero, so I must be the parent */
{
while(1){
sleep(100);
}
}
else if(pid==0)
{
exit (0) ;
}
}