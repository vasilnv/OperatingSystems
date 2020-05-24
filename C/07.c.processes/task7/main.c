#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <err.h>
int main(int argc, char* argv[])
{
	if(argc != 4)
	{
		errx(1, "wrong number of parameters");
	}

	int status;
	for (int i = 1; i < argc; i++)
	{
	    int p = fork();
	    if (p < 0)
   		{
        	err(2, "failed to fork");
    	}	
    	else if (p > 0)
    	{
			wait(&status);
           	printf("pid: %d, status: %d\n", getpid(), status, argv[i]);
    	}
	    else
		{
        	if (execlp(argv[i], argv[i], (char*)NULL) == -1 )
			{
				err(4, "failed to exec");
			}
		}

	}	
}