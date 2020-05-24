#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main (int argc, char* argv[])
{
	if (argc != 3)
	{
		errx(1, "wrong number of parameters");
	}
	
	int p;
	for (int i = 1 ; i < argc ; i ++ )
	{
		p = fork();
		int status;
		if (p < 0)
		{
			err(2, "failed to fork");
		}
		else if (p > 0)
		{
			wait(&status);
		}
		else
		{
			if (execlp (argv[i], argv[i], (char*)NULL) == -1)
			{
				err(3, "failed to exec");	
			}	
		}
		if (status != 0)
		{
			exit (-1);
		}
	}

	exit(0);

}
