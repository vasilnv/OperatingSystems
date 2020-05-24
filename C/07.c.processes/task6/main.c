#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(1, "wrong number of parameters");
	}

	int status;	
	int pid = fork();
	if (pid == -1)
	{
		err(2, "failed to fork");
	}
	else if (pid == 0)
	{
		if(execlp(argv[1], argv[1], (char*)NULL) == -1)
		{
			err(2, "failed to exec %s", argv[1]);
		}	
	}
	else 
	{
		wait(&status);
		if(status == 0)
		{
			printf("%s", argv[1]);
		}
	}
	
	exit(0);
}
