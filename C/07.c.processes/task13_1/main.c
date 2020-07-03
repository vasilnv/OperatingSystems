#include <err.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		errx(1, "wrong number of parameters");
	}
	
	int p1 = fork();
	if (p1 == 0)
	{
		if (execlp(argv[1], argv[1], (char*)NULL) != 0)
		{
			exit(1);
		}
	}
	int p2 = fork();
	if (p2 == 0)
	{
		if (execlp(argv[2], argv[2], (char*)NULL) != 0)
		{
			exit (1);
		}
	}
	
	int status1;
	int status2;
	
	int pid1=wait(&status1);
	int pid2=wait(&status2);
	
	if(WIFEXITED(status1))
	{	
		printf("process id: %d\n", pid1);
		wait(&status2);
		exit(0);
	}
	else if (WIFEXITED(status2))
	{
		printf("process id: %d\n", pid2);
		exit(0);	
	}
	else
	{
		printf("-1\n");
		exit(0);
	}
}
