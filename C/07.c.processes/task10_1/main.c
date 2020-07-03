#include <unistd.h>
#include <sys/types.h>
#include <err.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		errx(1, "wrong number of parameters");
	}
	
	int p = fork();
	int status;
	if (p == 0)
	{
		if (execlp(argv[1], argv[1], (char*)NULL) != 0)
		{
			exit(1);
		}
	}
	wait(&status);
	if (status != 0)
	{
		exit(42);
	}
	execlp(argv[2], argv[2], (char*)NULL);
	exit(0);

}
