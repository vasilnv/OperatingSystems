#include <err.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	if (argc < 2 )
	{
		errx(1, "at least one arg expected");
	}
	
	int cerr = 0;
	int cfine = 0;
	for (int i = 1; i < argc; i++)
	{
		int p = fork();
		int status;
		if (p < 0)
		{
			err(2, "failed to fork");
		}	
		else if (p > 0)
		{	
			wait(&status);
			if (status == 0)
			{
				cfine ++;
			}
			else
			{
				cerr ++;
			}
		}
		else 
		{
			if (execlp(argv[i], argv[i], (char*)NULL) == -1)
			{
				err(3, "failed to exec");
			}
		}
		
	}

	printf ("num of errors: %d\n", cerr);	
	printf ("num of fine processes: %d\n", cfine);

	exit(0);

}
