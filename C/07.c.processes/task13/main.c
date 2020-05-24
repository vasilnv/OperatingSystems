#include <sys/types.h>
#include <sys/wait.h>
#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		errx(1, "wrong number of parameters");
	}
	int p1 = fork();
	int p2 = fork();

	if (p1 == 0)
	{
		execlp(argv[1], argv[1], (char*)NULL);
	}	
	if (p2 == 0)
	{
		execlp(argv[2], argv[2], (char*)NULL);
	}
	
	int status1;
	int status2;
	pid_t pid1 = wait(&status1);
    pid_t pid2 = wait(&status2);
	
	if ( WIFEXITED(status1))
	{
		printf("%d, cmd: %s\n", pid1, argv[1]);
		wait(&status2);
	}	
	else if(WIFEXITED(status2))
	{
		printf("%d, cmd: %s\n", pid2, argv[2]);
		wait(&status1);
	}
	else
	{
		printf("-1\n");
	}
		
	exit(0);

}
